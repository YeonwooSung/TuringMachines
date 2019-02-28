#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "tm.h"


/**
 * The aim of this function is to check if the given character is in the list of alphabets.
 *
 * @params {list} A linked list of alphabets
 * @params {c} An input symbol
 * @return Returns 0 if the input symbol is valid. Otherwise, returns 1.
 */
char validateInputSymbol(Alphabets *list, char c) {
    while (list) {
        if (list->alphabet != c) {
            list = list->next;
        } else {
            return 0;
        }
    }

    return 1;
}


Tape *readTheInputTape(Alphabets *list, char *filePath) {
    FILE *f = fopen(filePath, "r");

    if (f == NULL) {
        exit(3);
    }

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
                if (c != '_') {
                    char ret = validateInputSymbol(list, c);

                    if (ret) {
                        printf("input error\n");
                        exit(2);
                    }
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

    return tape;
}


/**
 * Runs the deterministic turing machine.
 *
 * @param {}
 */
void run_d(State *state, Tape *tape) {
    size_t num_of_transitions = 0;
    char entirelyBlank = 1;
    Tape *tapeHead = tape;

    while (tape) {
        TList *list = state->list;

        char foundTransition = 0;

        while (list) {

            if (list->inputSymbol != tape->c) {
                list = list->next;
            } else {

                tape->c = list->outputSymbol;

                if (tape->c != '_') {
                    entirelyBlank = entirelyBlank & 0;
                } else {
                    entirelyBlank = entirelyBlank & 1;
                }

                switch (list->move) {
                    case 'L' : tape = tape->prev;
                        break;
                    case 'R' : tape = tape->next;
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
            break;
        }

        //increase the number of transitions
        num_of_transitions += 1;

    } //outer while loop ends

    tape = tapeHead;

    //check if the state is accepted state
    if (state->accept != 'a') {
        printf("not accepted\n");
    } else {
        printf("accepted\n");
    }

    printf("%lu \n", num_of_transitions);

    if (entirelyBlank) {
        printf("_\n");
    } else {
        while (tape) {
            printf("%c", tape->c);
            tape = tape->next;
        }
        printf("\n");
    }

}
