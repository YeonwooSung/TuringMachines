#!/bin/bash
export SCRATCHDIR=`mktemp -d`
    ./runtm "paren.tm" "${TESTDIR}/$1.tape"  > "${SCRATCHDIR}/output"
    export RESULT=$?
if [[ x$RESULT != x$2 ]]; then exit 1; fi
grep -e 'accepted' < "${SCRATCHDIR}/output" > "${SCRATCHDIR}/output1"
diff -w "${SCRATCHDIR}/output1" "${TESTDIR}/$1.tmout"
export RESULT=$?
rm -rf $SCRATCHDIR
exit $RESULT
