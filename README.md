## Smart Calculator v1.0

### Introduction

In this project you will implement an extended version of the usual calculator, which can be found in the standard applications of each operating system in the C programming language using structured programming. In addition to basic arithmetic operations such as add/subtract and multiply/divide, you need to supplement the calculator with the ability to calculate arithmetic expressions by following the order, as well as some mathematical functions (sine, cosine, logarithm, etc.).
Besides calculating expressions, it should also support the use of the x variable and the graphing of the corresponding function.

![SmartCalc](/screenshots/screenshot1.png)

### Install

Installation is done with a Makefile using the ***make install*** command. The application is built in the folder ***s21_calc***.

### Testing

For tests, use the ***make test*** and ***make gcov_report*** command to find out the coverage of the functional part.


### Other

the project is also archived with the make dist command and creates documentation with the make dvi command (example documentation is in the screenshots folder).