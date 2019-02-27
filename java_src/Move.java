/**
 * The enumeration to define the moves of Turing Machine.
 */
public enum Move {
    Left, Right, Stay;

    public static Move fromSymbol(String symbol) {

        // check if the given symbol is L (move left)
        if (symbol.equals("L")) {
            return Move.Left;
        } else if (symbol.equals("R")) { // check if the given symbol is R (move right)
            return Move.Right;
        } else if (symbol.equals("S")) { // check if the given symbol is S (stay still)
            return Move.Stay;
        }

        throw new IllegalArgumentException("Unknown move symbol :" + symbol);
    }

}
