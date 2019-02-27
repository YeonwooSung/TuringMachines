import java.io.FileInputStream;
import java.util.Scanner;
import java.util.List;


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
        Scanner sc = null;
        Scanner sc_des = null;

        try {
            // Check if the user passed the suitable number of command line arguments (2).
            if (args.length < 1) {

                sc = new Scanner(System.in);
                sc_des = new Scanner(System.in);

            } else if (args.length < 2) {
                
                sc = new Scanner(System.in);
                sc_des = new Scanner(new FileInputStream(args[0]));

            } else if (args.length != 3) {
                sc = new Scanner(new FileInputStream(args[1]));
                sc_des = new Scanner(new FileInputStream(args[0]));
            } else {
                sc = new Scanner(new FileInputStream(args[2]));
                sc_des = new Scanner(new FileInputStream(args[1]));
            }

            // Read
            State startState = Util.readMachine(sc_des);

            String input = sc.nextLine(); //read a line

            TuringMachine tm = new TuringMachine(startState, input, true);

            TuringMachineState tms = tm.run();

            sc.close();
            sc_des.close();


            if (tms != null) {
                System.out.println("accepted");
            } else {
                System.out.println("not accepted");
            }

            System.out.println(tm.getTransitionCount() - 1);

            //System.out.println(tm.getFinalState_DTM());
            List<Character> list = tms.getListOfSymbols();

            for (int i = 0; i < list.size() - 1; i++) {
                System.out.print(list.get(i));
            }

            System.out.println();

        } catch (Exception e) {
            System.out.println("input error");

            System.exit(2);
        }

    }

}
