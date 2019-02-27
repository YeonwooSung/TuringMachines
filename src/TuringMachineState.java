import java.util.HashMap;
import java.util.LinkedList;
import java.util.List;
import java.util.Map;
import static java.lang.Integer.max;


public class TuringMachineState {
    private State currentState;
    private int position;
    private int transitionCount;
    private Map<Integer, Character> tape = new HashMap<>();


    TuringMachineState(State startState, String tape) {
        this.currentState = startState;
        this.position = 0;
        this.transitionCount = 0;

        for (int i = 0; i < tape.length(); ++i) {
            this.tape.put(i, tape.charAt(i));
        }
    }

    /**
     * Create a copy of a pre-existing machine state
     * 
     * @param state The source state
     */
    TuringMachineState(TuringMachineState state) {
        this.currentState = state.currentState;
        this.position = state.position;
        this.transitionCount = state.transitionCount;
        for (Map.Entry<Integer, Character> entry : state.tape.entrySet()) {
            tape.put(entry.getKey(), entry.getValue());
        }
    }

    /**
     * Write a symbol to the tape
     * 
     * @param rewriteSymbol The symbol to write
     */
    private void writeAtHead(Character rewriteSymbol) {
        tape.put(position, rewriteSymbol);
    }

    private Character readAtHead() {
        return tape.getOrDefault(position, '_');
    }

    private void apply(Transition trans) {
        writeAtHead(trans.getNewSymbol());
        moveHead(trans.getMove());
        currentState = trans.getNextState();
        this.transitionCount++;
    }

    public List<TuringMachineState> step() {
        Character symbolAtHead = readAtHead();

        List<TuringMachineState> reachedStates = new LinkedList<>();

        List<Transition> possibleTransitions = currentState.getTransitionsFor(symbolAtHead);

        if (possibleTransitions.size() == 1) {
            // No need to create a new machine, just keep using the current one.
            this.apply(possibleTransitions.get(0));
            reachedStates.add(this);
        } else {
            for (Transition trans : possibleTransitions) {
                TuringMachineState fork = new TuringMachineState(this);
                fork.apply(trans);
                reachedStates.add(fork);
            }
        }

        return reachedStates;
    }

    private void moveHead(Move move) {
        switch (move) {
        case Left:
            position -= 1;
            break;
        case Right:
            position += 1;
            break;
        case Stay:
            break;
        }
    }

    public boolean isAccepted() {
        return this.currentState.isAccepted();
    }


    void printState() {
        System.out.println(currentState.getStateName());

        LinkedList<Integer> positions = new LinkedList<>(tape.keySet());
        positions.sort(Integer::compareTo);

        int startPos = Math.min(position, positions.getFirst());
        int endPos = Math.max(positions.getLast(), position);

        for (int i = startPos; i <= endPos; ++i) {
            if (i == position) {
                System.out.println(tape.getOrDefault(i, '_'));
            } else {
                System.out.println(tape.getOrDefault(i, '_'));
            }
        }
    }

    public int getTransitionCount() {
        return transitionCount;
    }
}
