#include "tm.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// set of states
typedef struct state_set {
    State *state;
    state_set *next;
} Set;


char run_n(State *state, Tape *tape, char entirelyBlank) {
    size_t num_of_transitions = 0;
    char virtual_transition = 0;
    Tape *tapeHead = tape;

    Set *set = (Set *) malloc(sizeof(Set));
    set->state = state;
    set->next = NULL;

    Set *setHead = set; //to store the head node of the linked list of set of states


    // Check if the linked list of tape is null
    if (tape) {
        while (1) {

            //iterate the set of states
            while(set) {

                State *s = set->state;
                TList *list = state->list;

                //iterate the transition list of current state
                while (list) {
                    if (list->inputSymbol != tape->c) {
                        list = list->next;
                    } else {

                        //TODO how does the nondeterministic TM process the tape??

                    }
                }

                set = set->next; //move to next state

            } //for loop ends

            set = setHead; //reset the pointer to the head node
        }

    } else {
        //
    }

    char ret = 0;

    return ret;
}
