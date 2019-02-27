// The import list
import java.util.HashMap;
import java.util.Map;
import java.util.List;
import java.util.LinkedList;
import java.util.Collections;

/**
 * The state that depicts the state of turing machine.
 */
public class State {

    private String stateName;
    private boolean isAccepted;

    // transitions takes input tape symbol as key, and a list of transition instances as value
    private Map<Character, List<Transition>> transitions;

    /**
     * The aim of this constructor is to initialise the attributes.
     *
     * @param stateName The state name.
     * @param isAccepted Boolean to check if this state is an accepted state.
     */
    public State(String stateName, boolean isAccepted) {
        this.stateName = stateName;
        this.isAccepted = isAccepted;

        this.transitions = new HashMap<>();
    }


    /**
     * Add a new transition function to the HashMap.
     *
     * @param symbol The symbol that will be used for the transition.
     * @param t      The transition instance.
     */
    public void addTransition(Character symbol, Transition t) {
        //add a new linked list object to the hash map if the given key is not stored in the hash map
        transitions.putIfAbsent(symbol, new LinkedList<>());

        //add the transition instance to the corresponding linked list
        transitions.get(symbol).add(t);
    }


    /**
     * The getter for name.
     *
     * @return name The name of the state
     */
    public String getStateName() {
        return stateName;
    }


    /**
     * The getter for the linked list of transitions.
     *
     * @return Returns empty list if the HashMap does not have the current symbol as a key.
     *         Otherwise,this method will return the linked list that is corresponding to the current symbol.
     */
    public List<Transition> getTransitionsFor(Character currentSymbol) {
        return transitions.getOrDefault(currentSymbol, Collections.emptyList());
    }


    /**
     * The getter for "isAccepted".
     *
     * @return isAccepted True if this state is an accepted state. Otherwise, returns false.
     */
    public boolean isAccepted() {
        return this.isAccepted;
    }

}
