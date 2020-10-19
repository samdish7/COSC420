# Lab 3; Gauss-Jordan Elimination

### Collaborators: Sam Disharoon & Jordan Welch

## Description

This lab was meant to expand our matrix library header file so we can have do more useful matrix operations.  We fixed up any functions that did not work during lab 2 and added the Gauss-Jordan Elimination method.  This method can calculate the inverse of a matrix as well as solving a certain set of linear equations.  

We used the MPI library to parallelize each function among varius nodes to test and time the results.

### How to run

### Key

*N* ~> Number of processors requested for use
*r1* ~> Number of rows for matrix 1
*c1* ~> Number of columns for matrix 1
*r2* ~> Number of rows for matrix 2
*c2* ~> Number of columns for matrix 2

Use one of the following commands:
	- mpiexec -n *N* ./gauss *r1* *c1* *r2* *c2*

## Testing

	- Note, we only programmed the gauss-jordan elmination in serial, couldn't figure out parallel.  We fixed matrix multiplication from lab 2 and that is parallelized. Number of processors used and size of matrices are included in testing.
	- All matrices are square.
	- All times are averaged.
	- Each test was run at least 10 times.

### N ~> 4

**Size:** 100 x 100

**Total Time:** 0.10s

**A * B Time:** 0.05s

**B * A Time:** 0.05s

**Gauss-Jordan Time:** 0.00s

===============================

**Size:** 500 x 500

**Total Time:** 2.63s

**A * B Time:** 1.32s

**B * A Time:** 1.21s

**Gauss-Jordan Time:** 0.10s

===============================

**Size:** 1000 x 1000

**Total Time:** 15.41s

**A * B Time:** 7.11s

**B * A Time:** 7.04s

**Gauss-Jordan Time:** 1.26s

===============================

### N ~> 8

**Size:** 500 x 500

**Total Time:** 4.08s

**A * B Time:** 2.00s

**B * A Time:** 1.98s

**Gauss-Jordan Time:** 0.10s

===============================

**Size:** 1000 x 1000

**Total Time:** 22.74s

**A * B Time:** 9.77s

**B * A Time:** 9.97s

**Gauss-Jordan Time:** 3.00s

===============================

**Size:** 2000 x 2000

**Total Time:** 127.45s

**A * B Time:** 51.38s

**B * A Time:** 51.93s

**Gauss-Jordan Time:** 24.14s

===============================

## Questions

A) The theoretical time complexity of our algorithm is **BEST** O(1) because we can have the same number of processors as there are total elements and **WORST** O(N^2 / p) because as N grows larger, the number of operations needed to be done grows as well.

B) Not at all, in fact, it seems to make it slower in some cases.  Very strange.

C) Data sheets, taking a linear algebra class, and data analysis are all examples of how the Gauss-jordan algorithm can be used in the real world.

D) Vastly improve hoe we use MPI and actually parallelize our gauss-jordan algorithm.
