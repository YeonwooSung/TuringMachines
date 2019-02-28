CS3052 2018/19 Practical 1

************
UPDATE: This  version of the Tests has been adjusted to be consistent
with the more precise specification of tape output format given in the
updated specification issued on 21 Feb
*************

This folder contains a set of tests designed to be run by
stacscheck. They are organised as follows:

Tests of task 1:

SimpleTM:  Tests the student's simulator using a simple Turing machine
(in simple.tm) which sweeps right on the tape exchanging 1 and 2
until it reaches a space.

SyntaxErrors: Tests that the student's simulator correctly detects a
wide range of erroneous inputs and responds accordingly, and that it
can parse some extreme but valid inputs (such as very long state
names).

TestTMs: Tests the student's simulator with a range of more
interesting TMs, including a 5 state busy beaver candidate (slightly
adapted) which runs for about 50 million timesteps and a couple of
large random TMs

Tests of task 2:

TestBinAdd: Tests of the student's binary addition TM on a range of
inputs, run with both their simulator and the reference simulator
provided.

TestParen: Tests of the student's balanced parenthesis checker on a
range of inputs, run on both their simulator and mine

Tests of task 4:

TestNonDet: Tests of their simulator with the -n option, on both
deterministic and non-deterministic TMs, including one designed to
split non-deterministically into a lot of different states (1000 or
so).

TestRepeat: Tests of the student's repeated string detector, run with
both their simulator and the reference simulator.

