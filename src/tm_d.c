#include "tm.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


Tape *readTheInputTape(Alphabets *list, FILE *f, char *check) {

    char *line = NULL;
    size_t len = 0;
    char entirelyBlanks = 1;

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

                if (entirelyBlanks && c != '_') {
                    entirelyBlanks = 0;
                }

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

    *check = entirelyBlanks;

    return tape;
}



Tape *moveTape(Tape *tape, TList *list) {
    switch (list->move) {
        case 'L' : 
            return tape->prev;
        case 'R' : 
            return tape->next;
        case 'S' : break;
        default:
            printf("input error");
            exit(2);
    }

    return tape;
}


char isAcceptedOrRejected(State *state) {
    return (state->accept == 'a' || state->accept == 'r') ? 1 : 0;
}


/**
 * Runs the deterministic turing machine.
 *
 * @param {}
 */
char run_d(State *state, Tape *tape, char entirelyBlank) {
    size_t num_of_transitions = 0;
    char virtual_transition = 0;
    Tape *tapeHead = tape;


    /* 
     * If the linked list of tape is null (no input file given), consider the all blank input.
     */
    if (!tape) {
        while (1) {

            TList *list = state->list;

            char isNotFound = 1; //to check whether the state has particular transition or not

            if (list) {
                while (list) {
                    if (list->inputSymbol != '_') {
                        list = list->next;
                    } else {
                        state = list->newState;

                        isNotFound = 0;

                        //if output symbol is not blank, set the entierlyBlank to 0.
                        if (entirelyBlank && list->outputSymbol != '_') {
                            entirelyBlank = 0;
                        }

                        // check if tape is added
                        if (tape) {
                            //TODO list->move R, S and L check!!
                            tape->next = (Tape *)malloc(sizeof(Tape));
                            tape->next->prev = NULL;

                            tape = tape->next;
                            tape->next = NULL;
                            tape->c = list->outputSymbol;

                        } else {
                            //TODO list->move R, S and L check!!
                            tape = (Tape *) malloc(sizeof(Tape));
                            tape->prev = NULL;
                            tape->next = NULL;
                            tape->c = list->outputSymbol;

                            tapeHead = tape;
                        }

                        break;
                    }
                }

                // if the new state is accepted or rejected, break the loop
                if (isAcceptedOrRejected(state)) {
                    break;
                }

                // if the current symbol does not have transition, which takes '_' as input, it is a virtual transition
                if (isNotFound) {
                    virtual_transition = 1;
                    break;
                }

                num_of_transitions += 1; //increase the number of transitions

            } else {
                virtual_transition = 1;
                break;
            }

        } // while loop ends

    } else {

        Tape *previousTape = tape;

        while (tape) {
            TList *list = state->list;

            char foundTransition = 0;

            while (list) {

                if (list->inputSymbol != tape->c) {
                    list = list->next;
                } else {

                    tape->c = list->outputSymbol;

                    previousTape = tape;

                    tape = moveTape(tape, list); //move tape

                    state = list->newState;

                    foundTransition = 1;

                    break;
                }

            } //inner while loop ends


            if (foundTransition != 1) { //TODO
                virtual_transition = 1;
                break;
            }

            //break the transition loop if the turing machine gets the accepted state (or rejected state).
            if (isAcceptedOrRejected(state)) {
                break;
            }


            //increase the number of transitions
            num_of_transitions += 1;

            /* 
             * If the TM read all input tape, however, the TM is not in the accepted state, or reject state,
             * add a blank symbol at the end of the
             */
            if (!tape) {
                char checker;

                while (1){
                    TList *list = state->list;
                    checker = 0;
                    char checker2 = 1;

                    while (list) {
                        if (list->inputSymbol != '_') {
                            list = list->next;
                        } else {
                            checker = 1;

                            //check if the output symbol of current transition is '_', and the new state is accepted or rejected state
                            if (list->outputSymbol == '_' && isAcceptedOrRejected(list->newState)) {
                                state = list->newState;
                            } else {

                                tape = (Tape *) malloc(sizeof(Tape));
                                tape->c = list->outputSymbol;

                                if (!tapeHead) {
                                    tapeHead = tape;
                                }

                                if (!(previousTape->next)) {
                                    previousTape->next = tape;
                                    tape->prev = previousTape;
                                    tape->next = NULL;
                                    previousTape = tape;
                                } else if (!(previousTape->prev)) {
                                    previousTape->prev = tape;
                                    tape->next = previousTape;
                                    tape->prev = NULL;
                                    previousTape = tape;
                                }

                                state = list->newState;

                                tape = moveTape(tape, list); //move tape

                                if (state->accept != 'a' && state->accept != 'r' && !tape) {
                                    checker2 = 0;
                                }

                                num_of_transitions += 1; //TODO

                            }

                            break;

                        } //if-else ends

                    }

                    //TODO how to break while??
                    if (checker2) {
                        break;
                    }

                } //while(1) ends

                if (!checker) {
                    virtual_transition = 1;
                    break;
                }

                if (isAcceptedOrRejected(state)) {
                    break;
                }

            }

        } //outer while loop ends

    }

    tape = tapeHead; //reset the pointer to the head node of the linked list

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
