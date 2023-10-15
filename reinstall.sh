#!/bin/bash
# Script to rebuild and reinstall program

validate_status_command() {
  if [[ $? -ne 0 ]]
  then
    echo "SSF - An error has occurred on $1!"
    exit
  fi
}

./bootstrap

validate_status_command "bootstrap"

./configure

validate_status_command "configure"

make

validate_status_command "make"

sudo make install
validate_status_command "make install"
