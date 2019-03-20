# TuringMachines

## 0. Instruction

### How to compile?

Basically, there is a Makefile in the src directory.
Thus, all you need to do is go in to src directory, and type "make" to build the program.

### How to run the program?

Once you type "make", you would get executable file "runtm".
To run the executable file "runtm", you need to follow one of things on below.

    1) ./runtm <description_file_path> <input_tape_file_path>

        With this command, you would be able to run deterministic turing machine with the given input tape.

    2) ./runtm <description_file_path>

        With this command, you would be able to run deterministic turing machine with the blank tape.

    3) ./runtm -n <description_file_path> [<input_tape_file_path>]

        With this command, you would be able to run non-deterministic turing machine with multiple tape files.


### What is a description file?

A description file is a file that contains the line that describe the turing machine.
Basically, the desciption file should contain the number of states, name of each state, accepted and rejected state, and all transitions.

The format of each line for transition should be something like this:
    < state1 > < tapeinput > < state2 > < tapeoutput > < move >


## 1. What is a turing machine?

A Turing machine is a type of machine that is more powerful than a PDA: it
can can recognise languages that are not context-free, and in addition to accepting
and rejecting words it can also produce output. We shall see in the next chapter
that Turing machines can do anything that a real computer can do.
Slightly more formally, a Turing machine is like a deterministic finite state
automaton, but with a tape that it can read and write and move about on. The
tape has a left hand end, but is infinite in the other direction, and is divided up
into squares called cells. The blank symbol _ indicates that nothing is written in
that cell.


## 2. Differences with DFAs and PDAs

1) Unlike a DFA, a Turing machine can write on the tape, instead of just reading
input.
Unlike a PDA, the Turing machine can write anywhere on the tape, once it
has moved the read/write head to the desired cell. At each step the Turing
machine must move one cell left or one cell right, unless the read/write head
is at the left-most end, when a “move left” instruction results in staying put.

2) There is a single accept state, qa, and a single reject state, qr. Basically, the machine
stops as soon as one of these is entered.

