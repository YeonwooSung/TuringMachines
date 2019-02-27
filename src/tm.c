#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "tm.h"


#define MAX_LENGTH 1000
#define STR_LENGTH 100
#define LIMIT 5
#define FILENAME_LENGTH 20

void print_head();
void print_message();
void print_line();
void update_string(char, char);


//TODO


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
 * The aim of this function is to read the description file.
 */
void readDescription(char *filePath, char isDeterministic, DState *d, NState *n) {
    FILE *f = fopen(filePath, "r");

    if (f == NULL) {
        printf("Error (File not found): \'%s\'\n", filePath);
        exit(2);
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
            num_of_states = atoi(splited[1]);
        }
    }

    DState *d_tmp = NULL;
    NState *n_tmp = NULL;

    //reads the file to get the name of states
    for (size_t i = 0; i < num_of_states; i++) {
        if (getline(&line, &len, f) != -1) {

            // check if this turing machine is deterministic
            if (isDeterministic) {

                // check if this is the initial state.
                if (d_tmp) {

                    d_tmp->next = (DState *) malloc(sizeof(DState));
                    d_tmp = d_tmp->next;

                    // use if-else statement to check if the new state is the accepted state or rejected state.
                    if (strchr(line, '+')) {
                        size_t counter = 0; //to count the number of splited strings
                        char **splited = splitStr(line, ' ', &counter);

                        d_tmp->accept = 'a';
                        d_tmp->name = strdup(splited[0]);

                        free(splited); //TODO

                    } else if (strchr(line, '-')) {
                        size_t counter = 0; //to count the number of splited strings
                        char **splited = splitStr(line, ' ', &counter);

                        d_tmp->accept = 'r';
                        d_tmp->name = strdup(splited[0]);

                        free(splited); //TODO

                    } else {
                        d_tmp->accept = 0;
                        d_tmp->name = strdup(line);

                        //remove the newline character from the state name
                        d_tmp->name[(strlen(d_tmp->name) - 1)] = '\0';
                    }

                    d_tmp->next = NULL; //set the next node as NULL

                } else {
                    d_tmp = d;

                    // use if-else statement to check if the new state is the accepted state or rejected state.
                    if (strchr(line, '+')) {
                        size_t counter = 0; //to count the number of splited strings
                        char **splited = splitStr(line, ' ', &counter);

                        d_tmp->accept = 'a';
                        d_tmp->name = strdup(splited[0]);

                        free(splited); //TODO
                    } else if (strchr(line, '-')) {
                        size_t counter = 0; //to count the number of splited strings
                        char **splited = splitStr(line, ' ', &counter);

                        d_tmp->accept = 'r';
                        d_tmp->name = strdup(splited[0]);

                        free(splited); //TODO
                    } else {
                        d_tmp->accept = 0;
                        d_tmp->name = strdup(line);

                        // remove the newline character from the state name
                        d_tmp->name[(strlen(d_tmp->name) - 1)] = '\0';
                    }

                    d_tmp->next = NULL; //set the next node as NULL

                }

            } else { //TODO need to test nondeterministic TM

                // check if this is the initial state.
                if (n_tmp) {

                    n_tmp->next = (NState *) malloc(sizeof(NState));
                    n_tmp = n_tmp->next;

                    // use if-else statement to check if the new state is the accepted state or rejected state.
                    if (strchr(line, '+')) {
                        size_t counter = 0; //to count the number of splited strings
                        char **splited = splitStr(line, ' ', &counter);

                        n_tmp->accept = 'a';
                        n_tmp->name = strdup(splited[0]);

                        free(splited); //TODO

                    } else if (strchr(line, '-')) {
                        size_t counter = 0; //to count the number of splited strings
                        char **splited = splitStr(line, ' ', &counter);

                        n_tmp->accept = 'r';
                        n_tmp->name = strdup(splited[0]);

                        free(splited); //TODO

                    } else {
                        n_tmp->accept = 0;
                        n_tmp->name = strdup(line);

                        //remove the newline character from the state name
                        n_tmp->name[(strlen(n_tmp->name) - 1)] = '\0';
                    }

                    n_tmp->next = NULL; //set the next node as NULL

                } else {
                    n_tmp = n;

                    // use if-else statement to check if the new state is the accepted state or rejected state.
                    if (strchr(line, '+')) {
                        size_t counter = 0; //to count the number of splited strings
                        char **splited = splitStr(line, ' ', &counter);

                        n_tmp->accept = 'a';
                        n_tmp->name = strdup(splited[0]);

                        free(splited); //TODO

                    } else if (strchr(line, '-')) {
                        size_t counter = 0; //to count the number of splited strings
                        char **splited = splitStr(line, ' ', &counter);

                        n_tmp->accept = 'r';
                        n_tmp->name = strdup(splited[0]);

                        free(splited); //TODO

                    } else {
                        n_tmp->accept = 0;
                        n_tmp->name = strdup(line);

                        //remove the newline character from the state name
                        n_tmp->name[(strlen(n_tmp->name) - 1)] = '\0';
                    }

                    n_tmp->next = NULL; //set the next node as NULL

                }

            }

        }

    } //for loop ends


    Alphabets *list = (Alphabets *) malloc(sizeof(Alphabets));

    //read line to get the number of states
    if (getline(&line, &len, f) != -1) {
        char *str = (char *) malloc(len + 1);

        strcpy(str, line);

        size_t counter = 0; //to count the number of splited strings
        char **splited = splitStr(str, ' ', &counter);

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
        printf("%s", line); //TODO debugging

        char *str = (char *)malloc(len + 1);

        strcpy(str, line);

        size_t counter = 0; //to count the number of splited strings
        char **splited = splitStr(str, ' ', &counter);

        //TODO store the transitions
        if (isDeterministic) {

            d_tmp = d;

            // iterate the linked list of states
            while (d_tmp) {
                printf("!%s!\n", d_tmp->name);
                if (strcmp(d_tmp->name, splited[0]) != 0) {
                    d_tmp = d_tmp->next;
                } else {

                    //
                    break;

                }
            }

        } else {
            //nondeterministic
            n_tmp = n;

            // iterate the linked list of states
            while (n_tmp) {
                if (strcmp(n_tmp->name, splited[0]) != 0) {
                    n_tmp = n_tmp->next;
                } else {

                    //TODO Add new transition to TList

                }
            }

        }
    }
}


/* Prints out the usage of this program */
void printUsage() {
    printf("Usage\n");
    printf("1. ./runTM <description file> <input tape file>\n");
    exit(0);
}


int main(int argc, char *argv[]) {
    if (argc > 1 && !strcmp(argv[1], "-help")) {
        printUsage();
    }

    /* Reading data from user input */

    /* Checks if file input as commandline argument is present */
    if (argc > 2) {

        //check if the number of command line arguments is 3
        if (argc  != 3) {
            DState *d = NULL;
            NState *n = (NState *)malloc(sizeof(NState));

            readDescription(argv[1], 0, d, n);

            //TODO nondeterministic TM
        } else {
            DState *d = (DState *)malloc(sizeof(DState));
            NState *n = NULL;

            readDescription(argv[1], 1, d, n);

            //TODO read input file
        }

    } else {
        printUsage();
    }

    return 0;
}
