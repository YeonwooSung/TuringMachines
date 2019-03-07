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

    char noInput = 1;

    while (getline(&line, &len, f) != -1) {
        // to check if there is no input data in the input file.
        if (noInput) {
            noInput = 0;
        }

        if (!strcmp(line, "\n")) {
            continue; //skip the empty input line
        }

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

    if (noInput) {
        tape->c = '_';
    }

    *check = entirelyBlanks;

    return tape;
}



Tape *moveTape(Tape *tape, TList *list) {
    switch (list->move) {
        case 'L' : 
            if (tape->prev)
                return tape->prev;
            else
                return tape;
        case 'R' : 
            return tape->next;
        default:
            printf("input error");
            exit(2);
    }

    return tape;
}


/**
 * This function checks if the current state is accepted or rejected.
 *
 * @param {state} The state that should be checked
 * @return If so, returns 1. Otherwise, returns 0.
 */
char isAcceptedOrRejected(State *state) {
    return (state->accept == 'a' || state->accept == 'r') ? 1 : 0;
}


/**
 * Runs the deterministic turing machine.
 *
 * @param {state} The linked list of states
 * @param {tape} The linked list of tape
 * @param {entirelyBlank} A boolean value to check if the input tape is entirelyBlank.
 * @return Suitable exit code.
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

            char targetSymbol = '_';

            if (tape) {
                targetSymbol = tape->c;
            }

            // check if the state has list of transitions (if not, just consider it as virtual transition)
            if (list) {

                //use while loop to iterate linked list of transitions
                while (list) {

                    if (list->inputSymbol != targetSymbol) {
                        list = list->next;
                    } else {

                        //convert the turing machine's state to the new state
                        state = list->newState;

                        isNotFound = 0;

                        //if output symbol is not blank, set the entierlyBlank to 0.
                        if (entirelyBlank && list->outputSymbol != '_') {
                            entirelyBlank = 0;
                        }

                        // check if tape is added
                        if (tapeHead) {

                            //replace the tape's symbol to the output symbol of the transition
                            tape->c = list->outputSymbol;

                            if (!isAcceptedOrRejected(state)) {
                                if (list->move == 'R') {

                                    // check if the next node is null
                                    if (!(tape->next)) {
                                        tape->next = (Tape *)malloc(sizeof(Tape));
                                        tape->next->prev = tape;
                                        tape->next->next = NULL;
                                        tape->next->c = '_';
                                    }

                                    tape = tape->next;
                                } else if (list->move == 'L') {

                                    /*
                                     * Check if the previous node is null.
                                     *
                                     * If the read/write head is at the left-most end, when a “move left” 
                                     * sinstruction results in staying put.
                                     */
                                    if (tape->prev) {
                                        tape = tape->prev;
                                    }

                                }
                            }

                        } else {
                            tape = (Tape *) malloc(sizeof(Tape));
                            tape->c = list->outputSymbol;

                            tapeHead = tape;

                            if (isAcceptedOrRejected(state)) {
                                tape->prev = NULL;
                                tape->next = NULL;
                            } else {

                                if (list->move == 'R') { //check if the move symbol is R

                                    tape->prev = NULL;
                                    tape->next = (Tape *) malloc(sizeof(Tape));
                                    tape->next->prev = tape;
                                    tape->next->next = NULL;

                                    tape = tape->next;
                                    tape->c = '_';

                                }
                            }

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

        while (1) {
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
                                }

                                state = list->newState;

                                tape = moveTape(tape, list); //move tape

                                if (state->accept != 'a' && state->accept != 'r' && !tape) {
                                    checker2 = 0;
                                }

                                num_of_transitions += 1;

                            }

                            break;

                        } //if-else ends

                    }

                    if (checker2) {
                        break;
                    }

                } //while(1) ends


                //check the virtual transition to the reject state.
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
