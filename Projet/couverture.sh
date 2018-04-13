#!/bin/bash

#Ce script met à jour la couverture du programme affichée grâce à lcov

#Executable
EXEC=AllTests

#Chemin de lcov
LCOVPATH=~vandendt/semestre6/lcov-1.13/bin

gcov -b -c $EXEC
$LCOVPATH/lcov --base-directory . --directory . -c -o rap.info 
$LCOVPATH/genhtml rap.info --output-directory out
firefox out/index.html &
