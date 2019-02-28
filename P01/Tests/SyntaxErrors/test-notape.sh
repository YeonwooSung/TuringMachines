#!/bin/bash
./runtm "${TESTDIR}/statenames3.tm" does-not-exist.tape >  /dev/null
if [[ x$? != x3 ]]; then exit 1; fi
