# ⚡ Prime Detector (C Implementation)

A lightweight, highly optimized command-line utility for primality testing, written in C. This tool utilizes the **6k +/- 1 optimization method** to perform efficient trial division.

## 🧮 The Algorithm: 6k +/- 1 Optimization

Naive trial division checks every odd number up to the square root of N. This implementation improves upon that by observing the properties of integers modulo 6.

All integers n >= 5 can be expressed in the form 6k + i, where k is a non-negative integer and i is in {0, 1, 2, 3, 4, 5}.

* 6k + 0, 6k + 2, 6k + 4: These are divisible by 2.
* 6k + 3: This is divisible by 3.

Consequently, all prime numbers greater than 3 must take the form of either:
6k + 1 or 6k + 5 (which is equivalent to 6k - 1).

### Performance Implication
By implementing this logic, the algorithm skips multiples of 2 and 3 automatically. Instead of incrementing by 2 (checking all odd numbers), the loop increments by 6, checking only two candidates (i and i+2) per iteration. This reduces the number of necessary test operations by approximately **33%** compared to standard trial division.

## 🛠️ Compilation

The project follows standard Linux conventions. A Makefile is provided for ease of use.

Prerequisites
Ensure you have the following installed:
* gcc (GNU Compiler Collection)
* make (GNU Make)

Build Instructions
1. Navigate to the project directory.
2. Run the make command to compile the source code with -O3 optimizations.

make

3. An executable named main will be created in the current directory.

Cleaning Up
To remove the compiled executable and object files, run:

make clean

## 🚀 Usage

The program accepts a single positive integer as an argument.

./main 104729
Output: true

./main 104730
Output: false

### Exit Codes & Streams
* Success (Prime/Not Prime): Output is written to stdout. Exit code 0.
* Help (--help): Output is written to stdout. Exit code 0.
* Errors (Invalid Input/Overflow): Error details are written to stderr. Exit code 1.

## 📜 License

This software is distributed under the GPLv3 License.
