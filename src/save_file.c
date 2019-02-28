#include "tm.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

Tape *readTheInputTape(Alphabets *list, FILE *f)
{

    char *line = NULL;
    size_t len = 0;

    Tape *tape = (Tape *)malloc(sizeof(Tape));
    tape->c = 0;
    tape->prev = NULL;
    tape->next = NULL;

    Tape *tempTape = tape;

    while (getline(&line, &len, f) != -1)
    {
        int len = strlen(line);

        char *tmp = line;

        for (int i = 0; i < len; i++)
        {
            char c = *tmp;

            // check if the input symbol is whitespace character
            if (!isspace(c))
            {
                validateSymbolFromAlphabetList(list, c);

                // check if this is not the first input symbol
                if (tape->c)
                {
                    //add new tape to the linked list
                    tempTape->next = (Tape *)malloc(sizeof(Tape));
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

char isAllBlank(Tape *tape)
{
    while (tape)
    {
        if (tape->c != '_')
        {
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
char run_d(State *state, Tape *tape)
{
    size_t num_of_transitions = 0;
    char entirelyBlank = isAllBlank(tape);
    char virtual_transition = 0;
    Tape *tapeHead = tape;

    /* 
     * If the linked list of tape is null (no input file given), 
     * check if the initial state hass any transition that gets the '_' as input symbol.
     */
    if (!tape)
    {

        TList *list = state->list;
        virtual_transition = 1;

        while (list)
        {
            if (list->inputSymbol != '_')
            {
                list = list->next;
            }
            else
            {
                state = list->newState;
                virtual_transition = 0;
                break;
            }
        }
    }

    char allProcessedInputSymbolsAreBlank = 0;

    while (tape)
    {
        TList *list = state->list;

        char foundTransition = 0;

        while (list)
        {

            if (list->inputSymbol != tape->c)
            {
                list = list->next;
            }
            else
            {

                tape->c = list->outputSymbol;

                if (tape->c == '_')
                {
                    allProcessedInputSymbolsAreBlank = 1;
                }
                else
                {
                    allProcessedInputSymbolsAreBlank = 0;
                }

                switch (list->move)
                {
                case 'L':
                    tape = tape->prev;
                    break;
                case 'R':
                    tape = tape->next;
                    break;
                case 'S':
                    break;
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

        if (foundTransition != 1)
        { //TODO
            virtual_transition = 1;
            break;
        }

        //break the transition loop if the turing machine gets the accepted state.
        // if (state->accept == 'a') {
        //     break;
        // }
        //TODO not sure which one is correct..
        if (!tape)
        {

            if (entirelyBlank)
            {
                break;
            }

            if (num_of_transitions == 0 && allProcessedInputSymbolsAreBlank != 0)
            {
                break;
            }

            num_of_transitions += 1;
            break;
        }

        //increase the number of transitions
        num_of_transitions += 1;

    } //outer while loop ends

    //reset the pointer to the head node of the linked list
    tape = tapeHead;

    char ret = 0; // this will be used to pass the correct exit code to main() function

    // check if the virtual transition occurred
    if (virtual_transition)
    {
        printf("not accepted\n");

        ret = 1;
    }
    else
    {
        //check if the state is accepted state
        if (state->accept != 'r')
        {
            printf("accepted\n");
        }
        else
        {
            printf("not accepted\n");

            ret = 1;
        }
    }

    // print the number of transitions
    printf("%lu \n", num_of_transitions);

    if (entirelyBlank)
    { //check if the input tape is entirely blank (all blank characters).
        printf("_\n");
    }
    else
    {
        // check if the tape is null (no input file)
        if (tape)
        {
            while (tape)
            {
                printf("%c", tape->c);
                tape = tape->next;
            }
            printf("\n");
        }
        else
        {
            printf("_\n");
        }
    }

    return ret;
}
