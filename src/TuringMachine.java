import java.util.List;
import java.util.Collection;
import java.util.LinkedList;
import java.util.stream.Collectors;


public class TuringMachine {

    private int transitionCount = 0;
    private List<TuringMachineState> quantumStates;
    private boolean printTransitions;


    public TuringMachine(State startState, String tapeInput) {
        this(startState, tapeInput, false);
    }


    public TuringMachine(State startState, String tapeInput, boolean printTransitions) {
        this.printTransitions = printTransitions;

        this.quantumStates = new LinkedList<>();
        quantumStates.add(new TuringMachineState(startState, tapeInput));
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
     * 
     */
    public TuringMachineState run() throws Exception { //TODO add exception
        this.transitionCount = 0;

        while (!hasAcceptingState()) {
            this.quantumStates = step();
            this.transitionCount += 1;

            if (this.quantumStates.isEmpty()) {
                //return null;
                throw new Exception();
            }
        }
        return getAcceptingMachine();
    }


    /**
     * This method gets the final state of the deterministic turing machine.
     *
     * @return the string of the final state
     */
    String getFinalState_DTM() {
        TuringMachineState state = this.quantumStates.get(0);

        return state.getStateName();
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
