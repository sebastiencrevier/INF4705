#!/bin/bash

OPTIONS=""
while [[ $# -gt 0 ]]
do
key="$1"

case $key in
    -e|--ex_path)
    EX_PATH="-e $2"
    shift
    ;;
    -p|--print|-t|--time)
    OPTIONS="${OPTIONS}${1} "
    ;;
	-r)
    RUNTIME="-r $2"
    shift
    ;;
    *)
        echo "Argument inconnu: ${1}"
        exit
    ;;
esac
shift
done

./tp3 $EX_PATH $OPTIONS $RUNTIME
