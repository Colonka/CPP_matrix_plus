# CPP_matrix_plus

Implementation of the s21_matrix_oop.h library using object-oriented approach.

## Introduction

In this project I've implemented the matrix library that I developed before, but in this project I was using the object-oriented approach. All detailed information about library you can find here: https://github.com/Colonka/s21_matrix

## Instructions for running

Being in s21_matrix/src folder run command `make` in terminal that create static library s21_matrix.
Include s21_matrix.h in your file and link libs21_matrix.a while compilation of your source files.

`#include "<Directory where the header resides>/s21_matrix_oop.h"`

`-L<Directory where the library resides> -l<library name>`

## Instruction for testing

Being in s21_matrix/src folder run command `make test`

*Note: you need installed `pkg-config` for choosing flags for check.h library linking 

## Instruction for gcovr test coverage

Being in s21_matrix/src folder run command `make gcovr_report`

