/**
 * This class is for the transition of the Turing Machine.
 */
public class Transition {

    private State nextState;
    private Character newSymbol;
    private Move move;


    /**
     * The aim of this constructor is to initialise the attributes.
     *
     * @param nextState The next state.
     * @param newSymbol The new symbol.
     * @param move      One of L(move left), R(move right), or S(stay still).
     */
    public Transition(State nextState, Character newSymbol, Move move) {
        this.nextState = nextState;
        this.newSymbol = newSymbol;
        this.move = move;
    }

    /**
     * The getter for newSymbol.
     *
     * @return The new symbol, which is the output symbol of the transition.
     */
    public Character getNewSymbol() {
        return this.newSymbol;
    }

    /**
     * The getter for move.
     *
     * @return One of L, R, and S.
     */
    public Move getMove() {
        return this.move;
    }

    /**
     * The getter for the nextState.
     *
     * @return Returns the result state of the transition.
     */
    public State getNextState() {
        return this.nextState;
    }

}
