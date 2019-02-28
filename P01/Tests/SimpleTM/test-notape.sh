#!/bin/bash
export SCRATCHDIR=`mktemp -d`
    ./runtm "${TESTDIR}/simple.tm"  > "${SCRATCHDIR}/output"
    export RESULT=$?
if [[ x$RESULT != x0 ]]; then exit 1; fi
grep -ve '^[[:space:]]' < "${SCRATCHDIR}/output" > "${SCRATCHDIR}/output1"
diff -w "${SCRATCHDIR}/output1" "${TESTDIR}/notape.tmout"
export RESULT=$?
rm -rf $SCRATCHDIR
exit $RESULT
