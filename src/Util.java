import java.io.FileInputStream;
import java.io.IOException;
import java.util.*;
import java.util.regex.Pattern;
import java.util.stream.Collectors;


public class Util {
    public static State readMachine(String path) throws IOException {

        // scanner to read the description file
        Scanner sc = new Scanner(new FileInputStream(path));

        sc.next("states");

        int noStates = sc.nextInt();

        Map<String, State> states = new HashMap<>();

        State startState = null;

        for (int i = 0; i < noStates; ++i) {
            String stateName = sc.next();
            boolean accept = false;

            if (sc.hasNext("\\+")) {
                sc.next("\\+");
                accept = true;
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

        // use for loop to read all alphabets from the description file
        for (int i = 0; i < alphabetSize; ++i) {
            String letter = sc.next("[^\\s]");

            assert letter.length() == 1; //TODO

            alphabet.add(letter);
        }

        String stateRegex = states.values().stream().map(State::getStateName).map(Pattern::quote).collect(Collectors.joining("|"));

        String alphabetRegex = alphabet.stream().map(Pattern::quote).collect(Collectors.joining());

        alphabetRegex = "[" + alphabetRegex + "_]";
        stateRegex = "(" + stateRegex + ")";

        String moveRegex = "[RSL]";

        // loop until the scanner reads all descriptions
        while (sc.hasNext()) {
            String currentStateSym;

            if (sc.hasNext(stateRegex)) {
                currentStateSym = sc.next(stateRegex);
            } else {
                throw new IOException("Unknown state: " + sc.next());
            }


            //TODO comment!!
            String currentSymbol = sc.next(alphabetRegex);


            String nextStateSym;

            if (sc.hasNext(stateRegex)) {
                nextStateSym = sc.next(stateRegex);
            } else {
                throw new IOException("Unknown state: " + sc.next());
            }

            String rewriteSymbol = sc.next(alphabetRegex);
            String moveSym = sc.next(moveRegex);

            State currentState = states.get(currentStateSym);

            State nextState = states.get(nextStateSym);

            Move move = Move.fromSymbol(moveSym);

            currentState.addTransition(currentSymbol.charAt(0), new Transition(nextState, rewriteSymbol.charAt(0), move));
        }

        return startState;
    }
}
