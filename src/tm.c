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

char string[STR_LENGTH];
int head, string_length;


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
void readDescription(char *filePath, char isDeterministic, DState **d, NState **n) {
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
        size_t counter = 0; //to count the number of splited strings
        char **splited = splitStr(line, ' ', &counter);

        free(splited); //TODO

        if (strcmp(splited[0], "states") == 0) {
            printf("number of states: %s", splited[1]); //TODO
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

                    printf("test2-1");

                    d_tmp->next = (DState *) malloc(sizeof(DState));
                    d_tmp = d_tmp->next;

                    // use if-else statement to check if the new state is the accepted state or rejected state.
                    if (strchr(line, '+')) {
                        printf("test2 +");
                        size_t counter = 0; //to count the number of splited strings
                        char **splited = splitStr(line, ' ', &counter);

                        d_tmp->accept = 'a';
                        d_tmp->name = strdup(splited[0]);

                        printf("test2 + (1)");

                        free(splited); //TODO
                        printf("test2 + (2)");
                    } else if (strchr(line, '-')) {
                        printf("test2 -");
                        size_t counter = 0; //to count the number of splited strings
                        char **splited = splitStr(line, ' ', &counter);
                        printf("test2 - (1)");

                        d_tmp->accept = 'r';
                        d_tmp->name = strdup(splited[0]);

                        printf("test2 - (2)");

                        free(splited); //TODO
                        printf("test2 - (3)");
                    } else {
                        d_tmp->accept = 0;
                        d_tmp->name = strdup(line);
                    }

                    d_tmp->next = NULL; //set the next node as NULL

                } else {
                    printf("test1-1");
                    *d = (DState *) malloc(sizeof(DState));

                    d_tmp = *d;

                    printf("test1-2");

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
                    }

                    printf("test1-3");

                    d_tmp->next = NULL; //set the next node as NULL

                }

            } else {

                // check if this is the initial state.
                if (n_tmp) {
                    //not first
                } else {
                    //
                }

            }

        }
    }

    //use getline() to read a line from the description file
    while (getline(&line, &len, f) != -1) {
        printf("%s", line); //TODO debugging

        //
    }
}


void print_message() {
    printf("Enter the Turing Machine input code\n");
    printf("Input format:\n");
    printf("\t<current state> <tapeinput> <new state> <tapeoutput> <move>\n");
    printf("A single transition should occupy a single line\n");
    printf("input symbol, new symbol and movement are single characters.\n");
    printf("current state and new state can be any combination of characters within a limit of 5\n");
    printf("First current state will be considered as your initial state\n");
    printf("Use \'_\' for blank\n");
    printf("Use \'$\' as current state to stop.\n\n");
}


int main(int argc, char *argv[]) {

    int limit, i, flag;
    char current_state[MAX_LENGTH][LIMIT], new_state[MAX_LENGTH][LIMIT];
    char input_symbol[MAX_LENGTH], write_symbol[MAX_LENGTH], move[MAX_LENGTH];
    char state[LIMIT], file_name[FILENAME_LENGTH];

    FILE *fin;

    if (argc > 1 && !strcmp(argv[1], "-help")) {
        printf("Usage\n");
        printf("1. ./runTM\n");
        printf("2. ./runTM <input file>\n");
        exit(0);
    }

    /* Reading data from user input */

    DState *d = NULL;
    NState *n = NULL;

    /* Checks if file input as commandline argument is present */
    if (argc > 2) {
        if (argc  != 3) {
            //TODO nondeterministic TM
        } else {

            readDescription(argv[1], 1, &d, &n);

            //TODO read description file and get states

            //TODO read input file
        }

    } else {
        //TODO
        /*
        print_message();
        fin = stdin; //use the stdin to get the user input
        for (limit = 0; limit < MAX_LENGTH; limit++) {
            scanf("%s %s", current_state[limit], current_state[limit]);
            if (!strcmp(current_state[limit], "$")) {
                break;
            }
            scanf(" %c %c %c %s", &input_symbol[limit], &write_symbol[limit], &move[limit], new_state[limit]);
        }
        printf("\n");
        */
    }

    printf("\n");
    printf("Output is stored as \'%s\' in the folder\n", file_name);
    return 0;
}
