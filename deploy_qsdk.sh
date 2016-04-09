#!/bin/bash 

function install {
    if grep -q "QSDK_LOC" $1
    then 
        echo "QSDK_LOC found in " $1
    else
        echo "Installing in " $1
        echo "export QSDK_LOC='$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )'" >> $1
    fi
}

install ~/.bashrc
install ~/.bash_profile