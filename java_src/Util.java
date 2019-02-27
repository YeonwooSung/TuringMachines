import java.io.IOException;
import java.util.*;
import java.util.regex.Pattern;
import java.util.stream.Collectors;


public class Util {
    public static State readMachine(Scanner sc, List<Character> alphabets) throws IOException, NoSuchElementException {
        sc.next("states");

        int noStates = sc.nextInt();

        Map<String, State> states = new HashMap<>();

        State startState = null;

        for (int i = 0; i < noStates; ++i) {
            String stateName = sc.next();
            boolean accept = false;

            if (sc.hasNext("\\+")) {
                sc.next("\\+"); //TODO need to test
                accept = true;
            } else if (sc.hasNext("\\-")) {
                sc.next("\\-"); //TODO need to test
            }

            State state = new State(stateName, accept);
            states.put(stateName, state);

            // check if the startState instance is null.
            if (startState == null) {
                startState = state;
            }
        }

        sc.next("alphabet");

        // get the number of alphabets
        int alphabetSize = sc.nextInt();

        // A linked list to store alphabets
        List<String> alphabet = new LinkedList<>();
        alphabets = new LinkedList<>();

        // use for loop to read all alphabets from the description file
        for (int i = 0; i < alphabetSize; ++i) {
            String letter = sc.next("[^\\s]");

            // use the assert to make sure that the length of the symbol alphabet is 1
            assert letter.length() == 1;

            alphabet.add(letter);
            alphabets.add(letter.charAt(0));
        }


        // generate the regular expression strings, which will be used to check the input

        String stateRegex = states.values().stream().map(State::getStateName).map(Pattern::quote).collect(Collectors.joining("|"));

        String alphabetRegex = alphabet.stream().map(Pattern::quote).collect(Collectors.joining());

        alphabetRegex = "[" + alphabetRegex + "_]";
        stateRegex = "(" + stateRegex + ")";

        String moveRegex = "[RSL]";


        // loop until the scanner reads all descriptions
        while (sc.hasNext()) {
            String currentStateStr;

            if (sc.hasNext(stateRegex)) {
                currentStateStr = sc.next(stateRegex);
            } else {
                //TODO for testing
                System.out.println("Unknown state: " + sc.next());

                throw new IOException("Unknown state: " + sc.next());
            }


            //get the input symbol
            String input = sc.next(alphabetRegex);

            String nextStateStr;

            if (sc.hasNext(stateRegex)) {
                nextStateStr = sc.next(stateRegex);
            } else {
                //TODO for testing
                System.out.println("Unknown state: " + sc.next());

                throw new IOException("Unknown state: " + sc.next());
            }

            String output = sc.next(alphabetRegex);
            String moveSym = sc.next(moveRegex);

            State currentState = states.get(currentStateStr);

            State nextState = states.get(nextStateStr);

            Move move = Move.fromSymbol(moveSym);

            currentState.addTransition(input.charAt(0), new Transition(nextState, output.charAt(0), move));
        }

        return startState;
    }
}