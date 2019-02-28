#!/bin/bash
export SCRATCHDIR=`mktemp -d`
./runtm "${TESTDIR}/does-not-exist.tm" > /dev/null
if [[ x$? != x3 ]]; then exit 1; fi
