#!/bin/bash

if [ $1 = 'master' ]
then
    /spark/sbin/start-master.sh
elif [ $1 = 'slave' ]
then
    if [ -n $2 ]
    then
        /spark/sbin/start-slave.sh $2
    fi
else
    echo "invalid argument"
fi

/bin/bash