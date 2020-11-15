# Lab 4; Calculating Eigenvectors & Parallelizing the Data

### Collaborators: Sam Disharoon

## Description

This lab increases our matrix library that we have been working on over the past 2 labs.  This time, we added functions to calculate an Eigenvector to correspond with the largest Eigenvalue of a given matrix.  The functions included are Normalize and Euclidean norm.

### How to run

*PLEASE ONLY RUN WITH 1 NODE* I was not able to parallelize it properly.

	- mpiexec -n 1 ./driver _matrix file_ _vector file_

### Data

Below is the data we have received.  I only record the output of the 20 x 20 matrix to show that the solution is correct. 

	- ** ALL FILE READING TOOK <= .01 seconds **
	- ** Everything is only run with one node**

## Output

A:
2.00 2.00 8.00 9.00 8.00 2.00 6.00 2.00 3.00 8.00 9.00 8.00 1.00 8.00 5.00 6.00 4.00 9.00 8.00 2.00
2.00 9.00 7.00 2.00 9.00 1.00 4.00 4.00 7.00 9.00 6.00 6.00 2.00 2.00 3.00 9.00 1.00 9.00 8.00 1.00
5.00 7.00 7.00 5.00 3.00 2.00 8.00 6.00 2.00 6.00 7.00 1.00 5.00 2.00 2.00 4.00 2.00 4.00 5.00 9.00
3.00 8.00 5.00 4.00 7.00 8.00 1.00 7.00 5.00 9.00 8.00 9.00 4.00 5.00 2.00 7.00 4.00 1.00 3.00 5.00
6.00 8.00 6.00 9.00 9.00 5.00 3.00 2.00 8.00 6.00 8.00 2.00 4.00 3.00 5.00 2.00 8.00 6.00 6.00 3.00
3.00 4.00 9.00 4.00 6.00 2.00 8.00 1.00 2.00 9.00 3.00 5.00 7.00 8.00 4.00 4.00 4.00 5.00 3.00 9.00
1.00 1.00 1.00 2.00 2.00 4.00 3.00 9.00 7.00 9.00 1.00 9.00 1.00 9.00 1.00 5.00 1.00 9.00 5.00 2.00
8.00 7.00 5.00 3.00 4.00 8.00 6.00 5.00 1.00 9.00 4.00 1.00 7.00 5.00 1.00 8.00 8.00 3.00 6.00 5.00
9.00 6.00 2.00 8.00 5.00 9.00 3.00 4.00 8.00 5.00 3.00 4.00 9.00 7.00 6.00 3.00 6.00 1.00 5.00 6.00
7.00 9.00 5.00 4.00 2.00 5.00 1.00 7.00 5.00 6.00 9.00 3.00 9.00 8.00 1.00 4.00 7.00 1.00 7.00 4.00
5.00 1.00 7.00 4.00 5.00 2.00 5.00 8.00 2.00 9.00 3.00 8.00 6.00 7.00 9.00 5.00 9.00 7.00 9.00 2.00
3.00 6.00 4.00 2.00 4.00 2.00 4.00 9.00 2.00 8.00 3.00 6.00 6.00 7.00 8.00 2.00 8.00 3.00 9.00 7.00
9.00 2.00 3.00 4.00 6.00 3.00 6.00 3.00 9.00 4.00 5.00 1.00 9.00 8.00 9.00 4.00 1.00 3.00 3.00 2.00
2.00 3.00 6.00 5.00 9.00 4.00 6.00 6.00 4.00 4.00 3.00 1.00 3.00 6.00 2.00 9.00 6.00 8.00 2.00 3.00
2.00 6.00 3.00 8.00 3.00 3.00 2.00 1.00 3.00 2.00 2.00 2.00 2.00 5.00 7.00 9.00 6.00 1.00 5.00 9.00
4.00 5.00 8.00 7.00 8.00 9.00 4.00 4.00 5.00 5.00 5.00 4.00 9.00 7.00 3.00 2.00 7.00 2.00 9.00 1.00
2.00 8.00 2.00 3.00 4.00 6.00 9.00 9.00 7.00 2.00 7.00 8.00 7.00 3.00 5.00 5.00 9.00 8.00 7.00 3.00
2.00 2.00 4.00 8.00 6.00 4.00 7.00 4.00 6.00 6.00 2.00 5.00 4.00 3.00 7.00 7.00 7.00 7.00 5.00 4.00
6.00 9.00 2.00 3.00 2.00 5.00 6.00 1.00 1.00 1.00 1.00 2.00 9.00 5.00 7.00 5.00 8.00 4.00 6.00 4.00
9.00 7.00 8.00 4.00 8.00 4.00 1.00 5.00 8.00 3.00 8.00 4.00 2.00 7.00 5.00 1.00 2.00 8.00 2.00 1.00
File reading took ~> 0.00 seconds
1 normaliztion took ~> 0.00 seconds
Largest Eigenvector of A:
0.24
0.23
0.20
0.24
0.25
0.22
0.18
0.23
0.24
0.23
0.25
0.23
0.21
0.21
0.18
0.24
0.25
0.22
0.19
0.22
19 normaliztions took ~> 0.00 seconds

## Timing

*20x20*

Very quick, on average took < 0.01 seconds

*100x100*

Very quick, on average took < 0.01 seconds

*1000x1000*

Still quick, on average took ~ 0.14 seconds


### Questions

_A)_ The theoretical time complexity is O(n^2/p) worst case and O(1) best case

_B)_ I don't know because I wasn't able to parallelize it

_C)_ PageRank algorithm for large databases. For this class, project 2 :)

_D)_ PARALLELIZE IT! I really need to sit down and get my stuff to work properly I don't think I have the parallelized functions working properly and wasn't able to get normalized to be in parallel.
