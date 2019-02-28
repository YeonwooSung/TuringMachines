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


void readInputTape(Alphabets *list, char *filePath) {
    FILE *f = fopen(filePath, "r");

    if (f == NULL) {
        printf("Error (File not found): \'%s\'\n", filePath);
        exit(2);
    }

    char *line = NULL;
    size_t len = 0;

    Tape *tape = (Tape *) malloc(sizeof(Tape));
    tape->prev = NULL;
    tape->next = NULL;

    while (getline(&line, &len, f) != -1) {
        int len = strlen(line);

        char *tmp = line;

        for (int i = 0; i < len; i++) {
            //TODO
            char c = *tmp;

            // check if the input symbol is whitespace character
            if (!isspace(c)) {
                char ret = validateInputSymbol(list, c);

                if (ret) {
                    printf("input error\n");
                    exit(2);
                }
            }

            tmp += 1;
        }

    } // end of the while loop

}
