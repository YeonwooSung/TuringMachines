import java.util.List;
import java.util.Collection;
import java.util.LinkedList;
import java.util.stream.Collectors;


public class TuringMachine {

    private int transitionCount = 0;
    private List<TuringMachineState> quantumStates;
    private List<Character> alphabets;


    public TuringMachine(State startState, String tapeInput, List<Character> alphabets) {
        this.quantumStates = new LinkedList<>();
        quantumStates.add(new TuringMachineState(startState, tapeInput));

        for (int i = 0; i < tapeInput.length(); i++) {
            //TODO read all tape input characters and check if there is invalid symbol
        }

        this.alphabets = alphabets;
    }


    private List<TuringMachineState> step() {
        return quantumStates.stream().map(TuringMachineState::step).flatMap(Collection::stream).collect(Collectors.toList());
    }


    /**
     * Check if the list of quantum states contains the accepted state.
     *
     * @return Returns true if the list contains an accepted state. Otherwise, returns false.
     */
    private boolean hasAcceptingState() {

        for (TuringMachineState state : quantumStates) {
            // check if the current state is accepted.
            if (state.isAccepted()) {
                return true;
            }
        }

        return false;
    }


    /**
     * This method runs the turing machine.
     *
     * @throws Exception The exception might be thrown if the
     */
    public TuringMachineState run() throws Exception {
        this.transitionCount = 0;

        while (!hasAcceptingState()) {
            this.quantumStates = step();

            // TODO need to test
            if (transitionCount == this.totalNumOfSymb) {
                break;
            }

            if (this.quantumStates.isEmpty()) {
                //return null;
                throw new Exception();
            }

            this.transitionCount += 1;
        }

        return getAcceptingMachine();
    }

    public void printResultSymbols() {
        for (int i = 0; i < quantumStates.size(); i++) {
            quantumStates.get(i).printUntilPosition();
        }
    }

    private TuringMachineState getAcceptingMachine() {
        for (TuringMachineState state : quantumStates) {
            if (state.isAccepted())
                return state;
        }
        return null;
    }

    public int getTransitionCount() {
        return transitionCount;
    }

}
