#!/bin/bash
export SCRATCHDIR=`mktemp -d`
if [ -f ${TESTDIR}/$1.tape ]; then
    ./runtm -n "${TESTDIR}/$1.tm" "${TESTDIR}/$1.tape"  > "${SCRATCHDIR}/output"
    export RESULT=$?
else
    ./runtm -n "${TESTDIR}/$1.tm" > "${SCRATCHDIR}/output"
    export RESULT=$?
fi
if [[ x$RESULT != x$2 ]]; then exit 1; fi
grep -ve '^[[:space:]]' < "${SCRATCHDIR}/output" > "${SCRATCHDIR}/output1"
diff -w "${SCRATCHDIR}/output1" "${TESTDIR}/$1.tmout"
export RESULT=$?
rm -rf $SCRATCHDIR
exit $RESULT
