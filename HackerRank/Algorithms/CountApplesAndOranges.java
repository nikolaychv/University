import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.StringTokenizer;

public class CountApplesAndOranges {

    private static void countApplesAndOranges(
            int houseStart,
            int houseEnd,
            int appleTree,
            int orangeTree,
            int appleCount,
            int orangeCount,
            BufferedReader reader
    ) throws IOException {

        int applesOnHouse = 0;
        int orangesOnHouse = 0;

        StringTokenizer tokenizer = new StringTokenizer(reader.readLine());
        for (int i = 0; i < appleCount; i++) {
            int landingPosition = appleTree + Integer.parseInt(tokenizer.nextToken());
            if (landingPosition >= houseStart && landingPosition <= houseEnd) {
                applesOnHouse++;
            }
        }

        tokenizer = new StringTokenizer(reader.readLine());
        for (int i = 0; i < orangeCount; i++) {
            int landingPosition = orangeTree + Integer.parseInt(tokenizer.nextToken());
            if (landingPosition >= houseStart && landingPosition <= houseEnd) {
                orangesOnHouse++;
            }
        }

        System.out.println(applesOnHouse);
        System.out.println(orangesOnHouse);
    }

    public static void main(String[] args) throws IOException {
        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));

        StringTokenizer tokenizer = new StringTokenizer(reader.readLine());
        int houseStart = Integer.parseInt(tokenizer.nextToken());
        int houseEnd = Integer.parseInt(tokenizer.nextToken());

        tokenizer = new StringTokenizer(reader.readLine());
        int appleTree = Integer.parseInt(tokenizer.nextToken());
        int orangeTree = Integer.parseInt(tokenizer.nextToken());

        tokenizer = new StringTokenizer(reader.readLine());
        int appleCount = Integer.parseInt(tokenizer.nextToken());
        int orangeCount = Integer.parseInt(tokenizer.nextToken());

        countApplesAndOranges(
                houseStart,
                houseEnd,
                appleTree,
                orangeTree,
                appleCount,
                orangeCount,
                reader
        );

        reader.close();
    }
}
