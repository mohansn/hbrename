#!/bin/bash

if [ "$1" == "-d" ]
then
    echo "Test name -name.ext "
    exit 0
fi

result=`../.rename -name.mp4`
if [ "$result" == "name.mp4" ]
then
#    echo success
    exit 0
else
#    echo problem
    echo "    Expected result : name.mp4 Actual result : $result"  > $error_log_file
    exit 1
fi
