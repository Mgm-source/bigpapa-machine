import java.util.Scanner;

public class App {
    public static void main(String[] args) throws Exception {
// declarations 
        stringverif check = new stringverif();
        Scanner input = new Scanner(System.in);
// main program
        check.takeString(input.nextLine());
        input.close();
        check.sorter();
        System.out.println(check.getterString());
    }
}
