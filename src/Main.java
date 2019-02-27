import java.io.FileInputStream;
import java.io.IOException;
import java.util.Scanner;


/**
 * The main class of the turing machine.
 */
public class Main {

    /**
     * This method prints out the usage message.
     */
    public static void printUsage() {
        System.out.println("Usage: ");
        System.out.println("\truntm <desription-file> <input>");
    }


    /**
     * The main method of the RunTM class, which is the starting point of the Turing Machine.
     */
    public static void main(String[] args) {
        try {
            String descriptionPath, inputPath;

            for (int i = 0; i < args.length; i++) {
                System.out.println(args[i]);
            }

            Scanner sc;
            Scanner sc_des;

            // Check if the user passed the suitable number of command line arguments (2).
            if (args.length == 2) {

                // The first command line argument should be the file path to the description file.
                descriptionPath = args[0];
                // The second command line argument should be the file path to the input file.
                inputPath = args[1];

                sc = new Scanner(new FileInputStream(inputPath));
                sc_des = new Scanner(new FileInputStream(descriptionPath));

            } else {

                sc = new Scanner(System.in);
                sc_des = new Scanner(System.in);

                descriptionPath = null;
            }

            // Read
            State startState = Util.readMachine(descriptionPath, sc_des);

            String input = sc.nextLine(); //read a line

            TuringMachine tm = new TuringMachine(startState, input, true);

            TuringMachineState tms = tm.run();

            if (tms != null) {
                System.out.println("The machine accepted the input.");
            } else {
                System.out.println("The machine did not accept the input.");
            }

            System.out.println("Number of transitions necessary: " + tm.getTransitionCount());

            sc.close();
            sc_des.close();
        } catch (Exception e) {
            System.out.println("input error");

            System.exit(2);
        }
    }


}
