#include "tm.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


Tape *readTheInputTape(Alphabets *list, FILE *f) {

    char *line = NULL;
    size_t len = 0;

    Tape *tape = (Tape *) malloc(sizeof(Tape));
    tape->c = 0;
    tape->prev = NULL;
    tape->next = NULL;

    Tape *tempTape = tape;

    while (getline(&line, &len, f) != -1) {
        int len = strlen(line);

        char *tmp = line;

        for (int i = 0; i < len; i++) {
            char c = *tmp;

            // check if the input symbol is whitespace character
            if (!isspace(c)) {
                validateSymbolFromAlphabetList(list, c);

                // check if this is not the first input symbol
                if (tape->c) {
                    //add new tape to the linked list
                    tempTape->next = (Tape *) malloc(sizeof(Tape));
                    tempTape->next->prev = tempTape;
                    tempTape = tempTape->next;
                    tempTape->next = NULL;
                }

                tempTape->c = c;

            }

            tmp += 1;
        }

    } // end of the while loop

    return tape;
}


char isAllBlank(Tape *tape) {
    while (tape) {
        if (tape->c != '_') {
            return 0;
        }
        tape = tape->next;
    }
    return 1;
}


/**
 * Runs the deterministic turing machine.
 *
 * @param {}
 */
char run_d(State *state, Tape *tape) {
    size_t num_of_transitions = 0;
    char entirelyBlank = isAllBlank(tape);
    char virtual_transition = 0;
    Tape *tapeHead = tape;

    if (!tape) { //TODO need to test

        TList *list = state->list;
        virtual_transition = 1;

        while (list) {
            if (list->inputSymbol != '_') {
                list = list->next;
            } else {
                state = list->newState;
                virtual_transition = 0;
                break;
            }
        }
    }

    while (tape) {
        TList *list = state->list;

        char foundTransition = 0;

        while (list) {

            if (list->inputSymbol != tape->c) {
                list = list->next;
            } else {

                tape->c = list->outputSymbol;

                switch (list->move) {
                    case 'L' : 
                        //TODO need to test
                        if (tape->prev)
                            tape = tape->prev;
                        break;
                    case 'R' : 
                        //TODO need to test
                        if (tape->next)
                            tape = tape->next;
                        break;
                    case 'S' : break;
                    default:
                        printf("input error");
                        exit(2);
                }

                state = list->newState;

                foundTransition = 1;

                break;
            }

        } //inner while loop ends

        //TODO reject state -> stop running??

        if (foundTransition != 1) { //TODO
            virtual_transition = 1;
            break;
        }

        if (state->accept == 'a') {
            break;
        } else if(state->accept == 'r') { //TODO need to test
            break;
        }

        //increase the number of transitions
        num_of_transitions += 1;

    } //outer while loop ends

    tape = tapeHead;

    char ret = 0;

    // check if the virtual transition occurred
    if (virtual_transition){
        printf("not accepted\n");

        ret = 1;
    } else {
        //check if the state is accepted state
        if (state->accept != 'r') {
            printf("accepted\n");
        } else {
            printf("not accepted\n");

            ret = 1;
        }
    }

    printf("%lu \n", num_of_transitions);

    if (entirelyBlank) {
        printf("_\n");
    } else {
        // check if the tape is null (no input file)
        if (tape) {
            while (tape) {
                printf("%c", tape->c);
                tape = tape->next;
            }
            printf("\n");
        } else {
            printf("_\n");
        }
    }

    return ret;
}
