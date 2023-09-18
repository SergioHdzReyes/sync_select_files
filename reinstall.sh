#!/bin/bash
# Script to rebuild and reinstall program

./bootstrap
./configure

make
sudo make install
