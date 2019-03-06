#include "tm.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// set of states
typedef struct state_set {
    State *state;
    Tape *tape;
    state_set *next;
} Set;

/**
 * The aim of this function is to copy the linked list of tape.
 *
 * The nondeterministic turing machine could have a set of states.
 * And each state could have it's own tape to process.
 * The main aim of this function is to copy the linked list of tape, so that
 * all states in the set could have their own tape.
 *
 * @param {tape} a pointer that points to the linked list of tape that should be copied.
 */
Tape *copyTape(Tape *tape) {

    // check if the given list is null
    if (tape) {
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

            temp = t;
            tape = tape->next;
        }
        temp->next = NULL;

        //return the pointer that points to the copied linked list
        return newTape;
    } else {
        return NULL;
    }

}


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
