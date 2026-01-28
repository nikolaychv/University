import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class Task1 {

    public static void main(String[] args) throws IOException {
        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
        int number = Integer.parseInt(reader.readLine().trim());

        if (number % 2 != 0) {
            System.out.println("Weird");
        } else if (number <= 5) {
            System.out.println("Not Weird");
        } else if (number <= 20) {
            System.out.println("Weird");
        } else {
            System.out.println("Not Weird");
        }

        reader.close();
    }
}
