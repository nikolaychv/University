import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.FileWriter;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.List;
import java.util.stream.Stream;

import static java.util.stream.Collectors.toList;

class Result {

    public static int calculateSum(List<Integer> numbers) {
        return numbers.stream().mapToInt(Integer::intValue).sum();
    }
}

public class ArraySum {

    public static void main(String[] args) throws IOException {
        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
        BufferedWriter writer = new BufferedWriter(new FileWriter(System.getenv("OUTPUT_PATH")));

        reader.readLine();

        List<Integer> numbers = Stream.of(reader.readLine().trim().split("\\s+"))
                .map(Integer::parseInt)
                .collect(toList());

        writer.write(String.valueOf(Result.calculateSum(numbers)));
        writer.newLine();

        reader.close();
        writer.close();
    }
}
