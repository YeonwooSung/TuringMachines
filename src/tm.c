#include "tm.h"

#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <unistd.h>


#define MAX_LENGTH 1000
#define STR_LENGTH 100
#define LIMIT 5
#define FILENAME_LENGTH 20



/**
 * This function trims the string to remove the whitespaces at the right-side of the given string.
 *
 * @param (s) the pointer that points to the target string
 * @return trimmed string
 */
char *trimStr(char *s) {
    char t[300];
    char *end;

    strcpy(t, s);
    end = t + strlen(t) - 1;

    while (end != t && isspace(*end)) { //(*end < 33)
        end--;
    }

    *(end + 1) = '\0';

    char *newStr = (char *) malloc(strlen(t) + 1);
    strcpy(newStr, t);

    free(s); //free the given string

    return newStr;
}

/**
 * This function splits the string with the given delimiter.
 *
 * @param (str) The target string that should be splited
 * @param (del) The delimiter
 * @param (counter) To count the number of splited strings
 * @return The 2D pointer, which is a string array that stores the splited strings
 */
char **splitStr(char *str, const char del, size_t *counter) {
    char **strArr = 0;
    size_t count = 0;
    char *tmp = str;
    char *last_delimiter = 0;
    char delim[2];
    delim[0] = del;
    delim[1] = '\0';

    /* Count the number of elements that will be extracted. */
    while (*tmp) {
        if (del == *tmp) {
            count++;
            last_delimiter = tmp;
        }
        tmp++;
    }

    /* Add space for the trailing token. */
    count += last_delimiter < (str + strlen(str) - 1);

    /* Add space for terminating null string so caller knows where the list of returned strings ends. */
    count += 1;

    strArr = malloc(sizeof(char *) * count);

    size_t idx = 0;

    if (strArr) {
        char *token = strtok(str, delim);

        while (token) {
            *(strArr + idx++) = strdup(token); //use the trim() to remove the whitespaces in the token
            token = strtok(0, delim);
        }
        *(strArr + idx) = 0;
    }

    *counter = idx;

    return strArr;
}


/**
 * This function finds the particular state node from the linked list of states.
 *
 * @param {s} Linked list of states
 * @param {name} The name of the particular state
 * @return The pointer that points to the particular state node.
 *         If the node that we are looking for is not in the linked list, NULL will be returned.
 */
State *findState(State *s, char *name) {
    while (s) {
        if (strcmp(s->name, name) != 0) {
            s = s->next;
        } else {
            return s;
        }
    }

    return NULL;
}


/**
 * This function validates the tape symbol by iterating the alphabet list.
 *
 * @params {list} A linked list of alphabets
 * @params {symbol} The tape symbol that should be validated
 */
void validateSymbolFromAlphabetList(Alphabets *list, char symbol) {
    if (symbol == '_')
        return;

    while (list) {
        if (list->alphabet != symbol) {
            list = list->next;
        } else {
            return;
        }
    }

    printf("input error\n");
    exit(2);
}


/**
 * The aim of this function is to read the description file.
 *
 * @param {filePath} file path of the description file
 * @param {isDeterministic} 1 is the turing machine is deterministic. Otherwise, 0.
 * @param {s} The linked list of states
 */
Alphabets *readDescription(char *filePath, char isDeterministic, State *s) {
    FILE *f = fopen(filePath, "rb");

    if (f == NULL) {
        exit(3);
    }

    char *line = NULL;
    size_t len = 0;

    size_t num_of_states = 0;

    //read line to get the number of states
    if (getline(&line, &len, f) != -1) {
        if (strcmp(line, "") == 0) {
            printf("input error\n");
            exit(2);
        }

        char *str = (char *) malloc(len + 1);

        strcpy(str, line);

        size_t counter = 0; //to count the number of splited strings
        char **splited = splitStr(str, ' ', &counter);

        // check the input format
        if (counter != 2) {
            printf("input error\n");
            exit(2);
        }

        if (strcmp(splited[0], "states") == 0) {

            // check the number format
            if (!isdigit(*splited[1])) {
                printf("input error\n");
                exit(2);
            }

            num_of_states = atoi(splited[1]);

            // check if the number of states is 0
            if (num_of_states == 0) {
                printf("input error\n");
                exit(2);
            }
        }
    } else {
        printf("input error\n");
        exit(2);
    }

    State *s_tmp = NULL;

    register size_t i, j;

    //reads the file to get the name of states
    for (i = 0; i < num_of_states; i++) {
        if (getline(&line, &len, f) != -1) {
            char *tempLine = line;

            char isAllWhiteSpace = 1;

            // check if the all characters in the line is whitespace characters
            for (j = 0; j < len; j++) {
                if (!isspace(*tempLine)) {
                    isAllWhiteSpace = 0;
                    break;
                }
            }

            if (isAllWhiteSpace) {
                i -= 1;
                continue;
            }

            // check if this is the initial state.
            if (s_tmp) {

                s_tmp->next = (State *) malloc(sizeof(State));
                s_tmp = s_tmp->next;

                // use if-else statement to check if the new state is the accepted state or rejected state.
                if (strchr(line, '+')) {
                    size_t counter = 0; //to count the number of splited strings
                    char **splited = splitStr(line, ' ', &counter);

                    s_tmp->accept = 'a';
                    s_tmp->name = strdup(splited[0]);

                    free(splited);

                } else if (strchr(line, '-')) {
                    size_t counter = 0; //to count the number of splited strings
                    char **splited = splitStr(line, ' ', &counter);

                    s_tmp->accept = 'r';
                    s_tmp->name = strdup(splited[0]);

                    free(splited);

                } else {
                    size_t counter = 0;
                    char **splited = splitStr(line, ' ', &counter);

                    s_tmp->accept = 0;
                    s_tmp->name = strdup(splited[0]);

                    for (int a = 1; a < counter; a++) {
                        free(splited[a]);
                    }

                    free(splited);

                    if (counter == 1) {
                        //remove the newline character from the state name
                        s_tmp->name[(strlen(s_tmp->name) - 1)] = '\0';
                    }
                }

                s_tmp->next = NULL; //set the next node as NULL

            } else {
                s_tmp = s;

                // use if-else statement to check if the new state is the accepted state or rejected state.
                if (strchr(line, '+')) {
                    size_t counter = 0; //to count the number of splited strings
                    char **splited = splitStr(line, ' ', &counter);

                    s_tmp->accept = 'a';
                    s_tmp->name = strdup(splited[0]);

                    free(splited);
                } else if (strchr(line, '-')) {
                    size_t counter = 0; //to count the number of splited strings
                    char **splited = splitStr(line, ' ', &counter);

                    s_tmp->accept = 'r';
                    s_tmp->name = strdup(splited[0]);

                    free(splited);
                } else {
                    s_tmp->accept = 0;
                    s_tmp->name = strdup(line);

                    // remove the newline character from the state name
                    s_tmp->name[(strlen(s_tmp->name) - 1)] = '\0';
                }

                s_tmp->next = NULL; //set the next node as NULL

            }

        } else {
            printf("input error\n");
            exit(2);
        }

    } //for loop ends


    Alphabets *list;

    //read line to get the number of states
    if (getline(&line, &len, f) != -1) {

        // check if the input line contains the substing "alphabet"
        if (!strstr(line, "alphabet")) {
            printf("input error\n");
            exit(2);
        }

        char *str = (char *) malloc(len + 1);

        strcpy(str, line);

        size_t counter = 0; //to count the number of splited strings
        char **splited = splitStr(str, ' ', &counter);

        if (*splited[1] == '-' || *splited[1] == '0' || strcmp(splited[0], "alphabet")) {
            printf("input error\n");
            exit(2);
        }

        int a_len = strlen(splited[1]);


        register int i;

        for (i = 0; i < a_len; i++) {
            if (!isdigit(splited[1][i])) {
                printf("input error\n");
                exit(2);
            }
        }

        size_t alphabet_num = atoi(splited[1]);

        list = (Alphabets *) malloc(sizeof(Alphabets));
        list->alphabet = *splited[2];

        Alphabets *tmp = list;

        size_t count_while_loop = 0;


        register size_t j;

        // use the loop to store all symbol alphabets in the linked list
        for (j = 3; j < counter; j++) {
            if (!isspace(*splited[j])) {
                tmp->next = (Alphabets *) malloc(sizeof(Alphabets));
                tmp = tmp->next;
                tmp->alphabet = *splited[j];

                count_while_loop += 1; //count the number of non-whitespace characters
            }
        }

        // compare the counted number and the result of atoi(splited[1])
        if (count_while_loop + 1 != alphabet_num) {
            printf("input error\n");
            exit(2);
        }

        tmp->next = NULL;
    }

    /*
     * Use getline() to read a line from the description file
     * The read line will be used to make a new node for transition.
     */
    while (getline(&line, &len, f) != -1) {
        if (strcmp(line, "\n") == 0) {
            continue;
        } else if (strcmp(line, " \n") == 0) {
            continue;
        }

        char *str = (char *)malloc(len + 1);

        strcpy(str, line);

        size_t counter = 0; //to count the number of splited strings
        char **splited = splitStr(str, ' ', &counter);

        s_tmp = s;

        char stateIsNotFound = 1;

        // iterate the linked list of states
        while (s_tmp) {
            // use conditional statement to find the corresponding state node
            if (strcmp(s_tmp->name, splited[0]) != 0) {
                s_tmp = s_tmp->next;
            } else {
                //let the turing machine know that the state1 is found
                stateIsNotFound = 0;

                //check if splited[1] and splited[3] are valid alphabet
                validateSymbolFromAlphabetList(list, *splited[1]);
                validateSymbolFromAlphabetList(list, *splited[3]);

                TList *t = (TList *) malloc(sizeof(TList));

                t->inputSymbol = *splited[1];
                t->outputSymbol = *splited[3];

                // validate the move symbol
                if (*splited[4] != 'R') {
                    if (*splited[4] != 'L') {
                        printf("input error\n");
                        exit(2);
                    }
                }

                t->move = *splited[4]; 
                t->next = NULL;

                State *target = findState(s, splited[2]);

                // check if the given name of state exists
                if (target) {
                    t->newState = target;
                } else {
                    printf("input error\n");
                    exit(2);
                }

                //check wheter s_tmp->list is null or not
                if (s_tmp->list) {

                    if (isDeterministic) {
                        TList *tempList = s_tmp->list;

                        while (tempList->next) {
                            if (tempList->inputSymbol != t->inputSymbol) {
                                tempList = tempList->next;
                            } else {
                                //ERROR!
                                printf("input error\n");
                                exit(2);
                            }
                        }

                        if (tempList->inputSymbol != t->inputSymbol) {
                            tempList->next = t;
                        } else {
                            //ERROR!
                            printf("input error\n");
                            exit(2);
                        }

                    } else {

                        TList *tempList = s_tmp->list;

                        while (tempList->next) {
                            tempList = tempList->next;
                        }

                        tempList->next = t;

                    }

                } else {
                    s_tmp->list = t;
                }

                break; //stop iterating the linked list of states.

            }
        }

        // check if the state1 is found from the input line
        if (stateIsNotFound) {
            printf("input error\n");
            exit(2);
        }


        register size_t i;

        //use for loop to free the splited string tokens
        for (i = 0; i < counter; i++) {
            free(splited[i]);
        }

    }

    return list;
}


/* Prints out the usage of this program */
void printUsage() {
    printf("Usage\n");
    printf("1. ./runTM <description file> <input tape file>\n");
    exit(0);
}

/**
 * The aim of this function is to free the memory of linked list of alphabets.
 *
 * @param {list} The head node of the linked list.
 */
void freeAlphabets(Alphabets *list) {
    Alphabets *temp;

    while (list) {
        temp = list->next;
        free(list);
        list = temp;
    }
}


/**
 * The aim of this function is to free the linked list of transitions.
 *
 * @param {list} the head node of linked list.
 */
void freeTransitions(TList *list) {
    TList *next;

    while (list) {
        next = list->next;
        free(list);
        list = next;
    }
}


/**
 * The aim of this function is to free the linked list of states.
 *
 * @param {state} the head node of linked list.
 */
void freeStates(State *state) {
    State *next;

    while (state) {
        next = state->next;

        freeTransitions(state->list);
        free(state->name);
        free(state);

        state = next;
    }
}


/**
 * The aim of this function is to free the linked list of tapes.
 *
 * @param {tape} the head node of linked list.
 */
void freeTapes (Tape *tape) {
    Tape *next;

    while (tape) {
        next = tape->next;

        free(tape);
        tape = next;
    }
}


char checkOptionForNonDet(int argc, char *argv[]) {
    char c;
    while ((c = getopt (argc, argv, "n:")) != -1) {
        switch(c) {
            case 'n' : 
                return 0;
                break;
            default:
                printf("invalid option: %c\n", c);
        }
    }

    return 1;
}



/* The main function of the turing machine */
int main(int argc, char *argv[]) {
    if (argc > 1 && !strcmp(argv[1], "-help")) {
        printUsage();
    }

    /* Reading data from user input */

    /* Checks if file input as commandline argument is present */
    if (argc > 2) {

        State *s = (State *)malloc(sizeof(State));

        //check if the number of command line arguments is 3
        if (argc  != 3) {

            Alphabets *list = readDescription(argv[2], 0, s);

            char ret;

            // use for loop to read multiple input tape files.
            for (int i = 3; i < argc; i++) {
                FILE *f = fopen(argv[i], "rb");

                if (f == NULL) {
                    exit(3);
                }

                char entirelyBlanks;

                Tape *tape = readTheInputTape(list, f, &entirelyBlanks);

                fclose(f); //close the file pointer when the program finished reading the file

                ret = run_n(s, tape, entirelyBlanks);

            }

            //free the alphabet list
            freeAlphabets(list);

            exit(ret);

        } else {

            if (checkOptionForNonDet(argc, argv)) {
                Alphabets *list = readDescription(argv[1], 1, s);

                FILE *f = fopen(argv[2], "rb");

                if (f == NULL) {
                    exit(3);
                }

                char entirelyBlanks;

                Tape *tape = readTheInputTape(list, f, &entirelyBlanks);

                fclose(f); //close the file pointer when the program finished reading the file

                //free the alphabet list
                freeAlphabets(list);

                char ret  = run_d(s, tape, entirelyBlanks); //run the turing machine

                freeStates(s);
                freeTapes(tape);

                exit(ret);

            } else {
                //nondeterministic turing machine without having the input file.

                Alphabets *list = readDescription(argv[2], 0, s);

                //free the alphabet list
                freeAlphabets(list);

                char entirelyBlanks = 1;

                // run the nondeterministic TM
                char ret = run_n(s, NULL, entirelyBlanks);
                exit(ret);
            }

        }

    } else if (argc != 1) {
        State *s = (State *)malloc(sizeof(State));

        Alphabets *list = readDescription(argv[1], 1, s);

        //free the alphabet list
        freeAlphabets(list);

        char ret = run_d(s, NULL, 1); //run the turing machine

        freeStates(s);

        exit(ret);
    } else {
        printUsage();
    }

    return 0;
}
