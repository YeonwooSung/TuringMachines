#ifndef TM_H
#define TM_H

#include <stdio.h>

struct state;


// linked list of transition
typedef struct transition {
    char inputSymbol;       //character for the input tape symbol
    char outputSymbol;      //character for the output tape symbol
    struct state *newState; //name of the new state
    char move;              //L, R, or S
    struct transition *next;
} TList;


// state for the turing machine
typedef struct state {
    char accept; //'a' for accept 'r' for reject
    char *name;  //name of the state
    TList *list; //list of the transitions
    struct state *next;
} State;


// A linked list of symbol alphabets
typedef struct alphabets {
    char alphabet;
    struct alphabets *next;
} Alphabets;


typedef struct tape {
    char c;
    struct tape *prev;
    struct tape *next;
} Tape;



/* function prototypes */

//functions in the tm_d.c
Tape *readTheInputTape(Alphabets *list, FILE *f, char *check);
char run_d(State *state, Tape *tape, char entirelyBlank);

//functions in the tm.c
void validateSymbolFromAlphabetList(Alphabets *list, char symbol);

//functions in the tm_n.c
char run_n(State *state, Tape *tape, char entirelyBlank);

#endif //TM_H
