
# Matrix Equation Solver

This C++ program allows you to solve a system of linear equations represented as a matrix equation. Given a square coefficient matrix and a constant vector, the program finds the solutions for the variables in the system using Cramer's rule.

## Table of Contents
- [Matrix Equation Solver](#matrix-equation-solver)
  - [Table of Contents](#table-of-contents)
  - [Introduction](#introduction)
  - [How to Use](#how-to-use)
  - [Dependencies](#dependencies)
  - [Installation](#installation)
  - [Usage](#usage)
  - [Examples](#examples)
  - [Author](#author)

## Introduction

The program implements a matrix equation solver using Cramer's rule. The equation takes the form Ax = b, where A is the coefficient matrix, x is the vector of variables to be solved, and b is the constant vector. It checks if the coefficient matrix is invertible before proceeding to calculate the solutions for the variables.

The key functions of the program are:

- `get_input`: To input the coefficient matrix.
- `get_const`: To input the constant vector.
- `display`: To display a matrix.
- `minor`: To calculate the minor matrix of a given matrix.
- `det`: To calculate the determinant of a matrix.
- `invertible`: To check if a matrix is invertible.
- `check`: To check if the coefficient matrix is invertible and prompt for re-entry if necessary.
- `get_Dn`: To obtain the Dn matrix for Cramer's rule.
- `solve`: To solve the system of equations and return the values of the variables.
- `display_system`: To display the system of linear equations.

## How to Use

Follow the instructions below to use the matrix equation solver program:

1. Enter the dimension of the square matrix when prompted.
2. Input the elements of the coefficient matrix in row-major order.
3. Verify that the coefficient matrix is invertible (non-singular).
4. Input the elements of the constant vector.
5. The program will display the augmented matrix for the system of equations and the solutions for each variable.

## Dependencies

This program uses the C++ Standard Library, and no additional external libraries are required.

## Installation

To run the program, follow these steps:

1. Make sure you have a C++ compiler installed on your system (e.g., GCC, Clang).
2. Copy the code provided in the main.cpp file and save it to your local system as "matrix_equation_solver.cpp".
3. Compile the code using the following command:

```
g++ -o matrix_equation_solver matrix_equation_solver.cpp
```


## Usage

To execute the program, use the following command in your terminal:

```
./matrix_equation_solver
```


## Examples

Let's consider an example to demonstrate how the program works:

Suppose we have the following system of linear equations:

2x + 3y - 4z = 5 
3x - 2y + z = -3 
x + 4y - 2z = 6


Running the program and providing the necessary input will yield the solutions:

X1 = 1 
X2 = -1 
X3 = 2

## Author 
This Matrix Equation Solver is developed by Yaseen Ahmed.