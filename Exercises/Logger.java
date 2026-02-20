import java.io.BufferedWriter;
import java.io.IOException;
import java.nio.charset.StandardCharsets;
import java.nio.file.*;
import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;
import java.util.Objects;
import java.util.concurrent.BlockingQueue;
import java.util.concurrent.LinkedBlockingQueue;
import java.util.concurrent.atomic.AtomicBoolean;

public final class Logger {

    public enum Level {
        TRACE(0), DEBUG(1), INFO(2), WARN(3), ERROR(4);
        final int value;
        Level(int v) { this.value = v; }
    }

    private static final class Holder {
        private static final Logger INSTANCE = new Logger();
    }

    public static Logger getInstance() {
        return Holder.INSTANCE;
    }

    private static final ThreadLocal<String> CORRELATION_ID = new ThreadLocal<>();
    private static final DateTimeFormatter FORMATTER =
            DateTimeFormatter.ofPattern("yyyy-MM-dd HH:mm:ss");

    private final BlockingQueue<String> queue = new LinkedBlockingQueue<>(10000);
    private final AtomicBoolean running = new AtomicBoolean(true);

    private volatile Level level = Level.INFO;
    private volatile boolean logToConsole = true;
    private volatile boolean logToFile = true;
    private volatile Path filePath = Paths.get("logs/app.log");
    private volatile long maxBytes = 5 * 1024 * 1024;
    private volatile int maxBackups = 3;

    private BufferedWriter writer;
    private Thread worker;

    private Logger() {
        initFile();
        startWorker();
        Runtime.getRuntime().addShutdownHook(new Thread(this::shutdown));
    }

    public void configure(Level level,
                          boolean logToConsole,
                          boolean logToFile,
                          String filePath,
                          long maxBytes,
                          int maxBackups) {

        this.level = Objects.requireNonNull(level);
        this.logToConsole = logToConsole;
        this.logToFile = logToFile;
        this.filePath = Paths.get(filePath);
        this.maxBytes = maxBytes;
        this.maxBackups = maxBackups;

        initFile();
    }

    public static void setCorrelationId(String id) {
        if (id == null || id.isBlank()) CORRELATION_ID.remove();
        else CORRELATION_ID.set(id);
    }

    public static void clearCorrelationId() {
        CORRELATION_ID.remove();
    }

    public void trace(String msg, Object... args) { log(Level.TRACE, null, msg, args); }
    public void debug(String msg, Object... args) { log(Level.DEBUG, null, msg, args); }
    public void info(String msg, Object... args)  { log(Level.INFO, null, msg, args); }
    public void warn(String msg, Object... args)  { log(Level.WARN, null, msg, args); }
    public void error(String msg, Object... args) { log(Level.ERROR, null, msg, args); }

    public void error(Throwable t, String msg, Object... args) {
        log(Level.ERROR, t, msg, args);
    }

    private void log(Level lvl, Throwable t, String msg, Object... args) {
        if (lvl.value < level.value) return;

        String timestamp = LocalDateTime.now().format(FORMATTER);
        String thread = Thread.currentThread().getName();
        String correlation = CORRELATION_ID.get();
        String formatted = format(msg, args);

        StringBuilder sb = new StringBuilder();
        sb.append(timestamp)
          .append(" [").append(lvl).append("]")
          .append(" [").append(thread).append("]");

        if (correlation != null) {
            sb.append(" [").append(correlation).append("]");
        }

        sb.append(" ").append(formatted);

        if (t != null) {
            sb.append(" | ").append(t.getClass().getSimpleName())
              .append(": ").append(t.getMessage());
        }

        queue.offer(sb.toString());
    }

    private String format(String msg, Object... args) {
        if (args == null || args.length == 0) return msg;
        return String.format(msg.replace("{}", "%s"), args);
    }

    private void startWorker() {
        worker = new Thread(() -> {
            while (running.get() || !queue.isEmpty()) {
                try {
                    String message = queue.take();
                    write(message);
                } catch (InterruptedException ignored) {
                    Thread.currentThread().interrupt();
                }
            }
            closeWriter();
        });
        worker.setDaemon(true);
        worker.start();
    }

    private void write(String message) {
        try {
            if (logToConsole) {
                System.out.println(message);
            }

            if (logToFile && writer != null) {
                rotateIfNeeded();
                writer.write(message);
                writer.newLine();
                writer.flush();
            }
        } catch (IOException e) {
            System.err.println("Logger write failed: " + e.getMessage());
        }
    }

    private void initFile() {
        if (!logToFile) return;

        try {
            Files.createDirectories(filePath.getParent());
            writer = Files.newBufferedWriter(
                    filePath,
                    StandardCharsets.UTF_8,
                    StandardOpenOption.CREATE,
                    StandardOpenOption.APPEND
            );
        } catch (IOException e) {
            System.err.println("Logger init failed: " + e.getMessage());
        }
    }

    private void rotateIfNeeded() throws IOException {
        if (!Files.exists(filePath)) return;
        if (Files.size(filePath) < maxBytes) return;

        closeWriter();

        for (int i = maxBackups - 1; i >= 0; i--) {
            Path src = (i == 0) ? filePath :
                    Paths.get(filePath + "." + i);
            if (Files.exists(src)) {
                Path dest = Paths.get(filePath + "." + (i + 1));
                Files.move(src, dest, StandardCopyOption.REPLACE_EXISTING);
            }
        }

        initFile();
    }

    private void closeWriter() {
        if (writer != null) {
            try { writer.close(); } catch (IOException ignored) {}
        }
    }

    public void shutdown() {
        if (!running.compareAndSet(true, false)) return;
        worker.interrupt();
    }
}
