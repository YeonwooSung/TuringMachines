#ifndef TM_H
#define TM_H

struct state_nondeterministic;
struct state_deterministic;


// transition
typedef struct transition {
    char inputSymbol;   //character for the input tape symbol
    char outputSymbol;  //character for the output tape symbol
    char *newStateName; //name of the new state
} Transition;

// transition list
typedef struct transitionList {
    Transition *t;
    struct transitionList *next;
} TList;

// state for the deterministic turing machine
typedef struct state_deterministic {
    char accept; //'a' for accept 'r' for reject
    char *name;
    Transition t;
    struct state_deterministic *next;
} DState;

// state for the nondeterministic turing machine
typedef struct state_nondeterministic {
    char accept; //'a' for accept 'r' for reject
    char *name;  //name of the state
    TList *list; //list of the transitions
    struct state_nondeterministic *next;
} NState;

// A linked list of symbol alphabets
typedef struct alphabets {
    char alphabet;
    struct alphabets *next;
} Alphabets;

#endif //TM_H
