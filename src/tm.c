#include "tm.h"

#include <string.h>
#include <stdlib.h>
#include <ctype.h>


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
        char *str = (char *) malloc(len + 1);

        strcpy(str, line);

        size_t counter = 0; //to count the number of splited strings
        char **splited = splitStr(str, ' ', &counter);

        if (strcmp(splited[0], "states") == 0) {

            if (!isdigit(*splited[1])) {
                printf("input error\n");
                exit(2);
            }

            num_of_states = atoi(splited[1]);

            if (num_of_states == 0) {
                printf("input error\n");
                exit(2);
            }
        }
    }

    State *s_tmp = NULL;

    //reads the file to get the name of states
    for (size_t i = 0; i < num_of_states; i++) {
        if (getline(&line, &len, f) != -1) {

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

                    free(splited); //TODO

                } else if (strchr(line, '-')) {
                    size_t counter = 0; //to count the number of splited strings
                    char **splited = splitStr(line, ' ', &counter);

                    s_tmp->accept = 'r';
                    s_tmp->name = strdup(splited[0]);

                    free(splited); //TODO

                } else {
                    s_tmp->accept = 0;
                    s_tmp->name = strdup(line);

                    //remove the newline character from the state name
                    s_tmp->name[(strlen(s_tmp->name) - 1)] = '\0';
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

                    free(splited); //TODO
                } else if (strchr(line, '-')) {
                    size_t counter = 0; //to count the number of splited strings
                    char **splited = splitStr(line, ' ', &counter);

                    s_tmp->accept = 'r';
                    s_tmp->name = strdup(splited[0]);

                    free(splited); //TODO
                } else {
                    s_tmp->accept = 0;
                    s_tmp->name = strdup(line);

                    // remove the newline character from the state name
                    s_tmp->name[(strlen(s_tmp->name) - 1)] = '\0';
                }

                s_tmp->next = NULL; //set the next node as NULL

            }

        }

    } //for loop ends


    Alphabets *list;

    //read line to get the number of states
    if (getline(&line, &len, f) != -1) {
        char *str = (char *) malloc(len + 1);

        strcpy(str, line);

        size_t counter = 0; //to count the number of splited strings
        char **splited = splitStr(str, ' ', &counter);

        if (*splited[1] == '-' || *splited[1] == '0' || strcmp(splited[0], "alphabet")) {
            printf("input error\n");
            exit(2);
        }

        int a_len = strlen(splited[1]);

        for (int i = 0; i < a_len; i++) {
            if (!isdigit(splited[1][i])) {
                printf("input error\n");
                exit(2);
            }
        }

        int alphabet_num = atoi(splited[1]);

        if (counter - 2 != alphabet_num) {
            printf("input error\n");
            exit(2);
        }


        list = (Alphabets *) malloc(sizeof(Alphabets));


        list->alphabet = *splited[2];

        Alphabets *tmp = list;

        // use the loop to store all symbol alphabets in the linked list
        for (int i = 3; i < counter; i++) {
            tmp->next = (Alphabets *)malloc(sizeof(Alphabets));
            tmp = tmp->next;
            tmp->alphabet = *splited[i];
        }

        tmp->next = NULL;
    }

    //use getline() to read a line from the description file
    while (getline(&line, &len, f) != -1) {
        char *str = (char *)malloc(len + 1);

        strcpy(str, line);

        size_t counter = 0; //to count the number of splited strings
        char **splited = splitStr(str, ' ', &counter);

        s_tmp = s;

        // iterate the linked list of states
        while (s_tmp) {
            // use conditional statement to find the corresponding state node
            if (strcmp(s_tmp->name, splited[0]) != 0) {
                s_tmp = s_tmp->next;
            } else {

                TList *t = (TList *) malloc(sizeof(TList));

                t->inputSymbol = *splited[1];
                t->outputSymbol = *splited[3];
                t->move = *splited[4];
                t->next = NULL;

                State *target = findState(s, splited[2]);

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
                                printf("Transition error: cannot have transitions that take same symbol and state\n");
                                exit(0);
                            }
                        }

                        if (tempList->inputSymbol != t->inputSymbol) {
                            tempList->next = t;
                        } else {
                            //ERROR!
                            printf("Transition error: cannot have transitions that take same symbol and state\n");
                            exit(0);
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

    }

    return list;
}


/* Prints out the usage of this program */
void printUsage() {
    printf("Usage\n");
    printf("1. ./runTM <description file> <input tape file>\n");
    exit(0);
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

            Alphabets *list = readDescription(argv[1], 0, s);

            //TODO nondeterministic TM
        } else {

            Alphabets *list = readDescription(argv[1], 1, s);

            FILE *f = fopen(argv[2], "rb");

            if (f == NULL) {
                exit(3);
            }

            Tape *tape = readTheInputTape(list, f);

            //TODO free the alphabet list

            char ret  = run_d(s, tape); //run the turing machine

            //TODO free state and transitions

            exit(ret);
        }

    } else if (argc != 1) {
        State *s = (State *)malloc(sizeof(State));

        Alphabets *list = readDescription(argv[1], 1, s);

        //TODO free the alphabet list

        char ret = run_d(s, NULL); //run the turing machine

        //TODO free state and transitions

        exit(ret);
    } else {
        printUsage();
    }

    return 0;
}
