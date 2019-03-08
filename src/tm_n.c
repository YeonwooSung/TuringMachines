#include "tm.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// set of states
typedef struct state_set {
    State *state;
    Tape *tape;
    struct state_set *next;
} Set;

/**
 * Rewind the tape.
 *
 * @param {tape} The linked list of tape.
 * @return The head node of the linked list.
 */
Tape *rewindTape(Tape *tape) {
    if (tape) {
        while (tape->prev) {
            tape = tape->prev;
        }

        return tape;
    } else {
        return NULL;
    }
}


/**
 * This function frees the allocated memory of the linked list of tape.
 */
void freeTape(Tape *tape) {
    Tape *t = rewindTape(tape);

    while (t) {
        free(t);
        t = t->next;
    }
}


/**
 * This function removes the rejected state from the set.
 *
 * @param {set} A node that should be removed from the set.
 * @return The next node.
 */
Set *removeRejectedStateFromSet(Set *set) {
    Set *next = set->next;

    freeTape(set->tape);
    free(set);

    return next;
}


/**
 * The aim of this function is to copy the linked list of tape.
 *
 * The nondeterministic turing machine could have a set of states.
 * And each state could have it's own tape to process.
 * The main aim of this function is to copy the linked list of tape, so that
 * all states in the set could have their own tape.
 *
 * @param {currentNode} a pointer that points to the linked list of tape that should be copied.
 */
Tape *copyTape(Tape *currentNode) {

    Tape *tape = rewindTape(currentNode); //rewind the tape to get the head node of the linked list of tape

    if (tape == currentNode) {
        printf("same!\n");
    }

    // check if the given list is null
    if (tape) {
        Tape *head = tape;
        Tape *newTape = (Tape *) malloc(sizeof(Tape));
        newTape->prev = NULL;
        newTape->c = tape->c;

        Tape *temp = newTape;
        tape = tape->next;


        //use while loop to iterate linked list of tape
        while (tape) {
            Tape *t = (Tape *) malloc(sizeof(Tape));
            t->c = tape->c;
            t->prev = temp;
            temp->next = t;

            temp = temp->next;
            tape = tape->next;
        }

        temp->next = NULL;

        tape = head; //set the pointer to the head node of the linked list

        while (tape != currentNode) {
            tape = tape->next;
            newTape = newTape->next;
        }

        //return the pointer that points to the copied linked list
        return newTape;
    } else {
        return NULL;
    }

}


/**
 * The aim of this function is to move the tape to corresponding direction, and add new node if required.
 *
 * @param {tape} A linked list of tape
 * @param {move} a move direction (L or R)
 * @return The next (or previous) tape node (depends on the move direction).
 */
Tape *moveTape_n(Tape *tape, char move) {
    Tape *movedNode;

    switch (move) {
        case 'L' :
            if (tape->prev) {
                movedNode = tape->prev;
            } else {
                movedNode = tape;
            }

            break;
        case 'R' : 
            if (tape->next) {
                movedNode = tape->next;
            } else {
                movedNode = (Tape *) malloc(sizeof(Tape));

                movedNode->c = '_';
                movedNode->next = NULL;
                tape->next = movedNode;
                movedNode->prev = tape;
            }

            break;
        default : 
            printf("input error\n");
            exit(2);
    }

    return movedNode;
}


/**
 * 
 */
char executeNondeterministicTM(Set *set, size_t *num_of_transitions) {
    Set *setHead = set; //to store the head node of the linked list of set of states

    // use the endless loop to run the turing machine until it gets the accepted (or rejected) state.
    while (1) {

        Set *newNode = NULL;
        Set *lastNewNode = NULL;
        Set *latestNode = NULL;

        size_t isFound = 0;

        //iterate the set of states
        while(set) {

            State *s = set->state;
            TList *list = s->list;

            char targetSymbol = set->tape->c;

            //iterate the transition list of current state
            while (list) {

                //check if there is any transition that takes the current state and tape symbol as input
                if (list->inputSymbol != targetSymbol) {
                    list = list->next;
                } else {

                    // check if the new state is an accepted state
                    if (list->newState->accept == 'a') {
                        //if it's an accepted state, then return 0, which is the exit code for the "accepted"
                        return 0;
                    } else if (list->newState->accept == 'r') {

                        //TODO

                    } else {

                        // check if there are more than one transitions that take same state and tape symbol as input
                        if (isFound) {

                            //add new state to the set
                            Tape *newTape = copyTape(set->tape);
                            newTape->c = list->outputSymbol;

                            // check if there are more than 2 transitions that take same state and tape symbol as input
                            if (newNode) {

                                Set *tempSet = (Set *) malloc(sizeof(Set));
                                tempSet->state = list->newState;
                                tempSet->tape = newTape;
                                tempSet->next = NULL;

                                lastNewNode->next = tempSet;
                                lastNewNode = tempSet;

                                //move the tape and add new tape node if required
                                tempSet->tape = moveTape_n(newTape, list->move);

                            } else {

                                newNode = (Set *) malloc(sizeof(Set));
                                newNode->state = list->newState;
                                newNode->tape = newTape;
                                newNode->next = NULL;

                                lastNewNode = newNode;

                                //move the tape and add new tape node if required
                                newNode->tape = moveTape_n(newTape, list->move);

                            }


                        } else {

                            set->tape->c = list->outputSymbol;
                            set->state = list->newState;

                            //move the tape and add new tape node if required
                            set->tape = moveTape_n(set->tape, list->move);

                        }

                        isFound += 1;

                        list = list->next;
                    }

                }
            }

            if (!isFound) {
                //when the virtual transition occurred, remove the node from the set of state
                set = removeRejectedStateFromSet(set);

                if (latestNode) {
                    latestNode->next = set;
                } else {
                    setHead = set;
                }
            } else {

                isFound = 0;

                latestNode = set;
                set = set->next; //move to next state

            }

        } //while loop ends


        //add new nodes to the set of states
        if (latestNode) {
            if (newNode) {
                latestNode->next = newNode; //expand the set
            }
        } else {
            if (newNode) {
                setHead = newNode;
            } else {
                //if there is no more nodes in the set, then that means all states are rejected
                return 1; //return 1, which is the exit code for not accepted
            }
        }

        *num_of_transitions += 1;

        set = setHead; //reset the pointer to the head node
    }
}


/**
 * This function runs the nondeterminant turing machine.
 *
 * @param {state} A pointer that points the head node of linked list of turing machine states.
 * @param {tape} A pointer that points the head node of the linked list of input tape.
 * @param {entirelyBlank} 1 if all input symbols are blank. Otherwise, 0.
 * @return Suitable exit code
 */
char run_n(State *state, Tape *tape, char entirelyBlank) {
    //this will be used to count the number of performed transitions
    size_t num_of_transitions = 0;

    //store the pointer that points to the head node of the linked list of tape
    Tape *tapeHead = tape;

    Set *set = (Set *) malloc(sizeof(Set));
    set->state = state;
    set->next = NULL;

    char ret;

    // Check if the linked list of tape is null
    if (tape) {
        set->tape = tape;

        ret = executeNondeterministicTM(set, &num_of_transitions);
    } else {
        tape = (Tape *) malloc(sizeof(Tape));

        tape->prev = NULL;
        tape->next = NULL;
        tape->c = '_';

        set->tape = tape;

        ret = executeNondeterministicTM(set, &num_of_transitions);
    }

    if (ret) {
        printf("not accepted\n");
    } else {
        printf("accepted\n");
    }

    printf("%lu\n", num_of_transitions);

    return ret;
}
