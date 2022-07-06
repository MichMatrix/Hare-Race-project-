# Race of Hares Project


## Introduction

This project is a hare race using processes and threads. The first thread/process
whoever reaches the entered distance wins.

After being in the c file folder, to start the program you must insert 3 parameters during the execution:
- use -p for processes or -t for threads;
- how many instances (hares) will be created for the race;
- and an integer value, which represents the length of the race track in meters.

Execution example:

    $ ./race -t 2 100 (2 hares/threads, 100m track)
    hare 0 jumped 30cm (total: 30)
    hare 2 jumped 42cm (total: 42)
        ...
    hare 2 jumped 31cm (total: 1002)
    hare 2 won!

## Requirements
A computer or notebook/macbook with the use of a linux terminal using a linux virtual machine is required, AWS with linux system installed or in windows/mac system using linux command terminal WSL.

## Installation

In the windows store you can download WSL Ubuntu to use the terminal, download the program and access it through the terminal.For more information about the download click [here](https://ubuntu.com/wsl).

A C compiler must also be installed. For more information click [here](https://terminaldeinformacao.com/2015/10/08/como-instalar-e-configurar-o-gcc-no-windows-mingw/).

## Running the tests

You should compile the program as follows: gcc rice.c -o rice -pthread

It's runned the tests on defined parameters.

## Development

It was developed using a virtual machine with a linux operating system, and the VS code program was installed in order to develop the code.

## Author

Michel Adelino
