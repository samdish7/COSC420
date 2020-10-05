# Project 1; Project Euler problems 125, 302, and 307

### Collaborators ~> Sam Disharoon & Jordan Welch

[Link to Github repo](https://github.com/samdish7/COSC420/tree/master/Projects/Project1)

Project Euler is a website that has numerous problems of a wide range of difficulty. Our task was to choose three of these problems, one of each of at least 10th, 40th, and 60th percentile, and solve them using what we have learned about MPI and to take advantage of the HPCL cluster.

## Problem 1; Palindromic Sums

### Description

The palindromic number 595 is interesting because it can be written as the sum of consecutive squares: 6^2 + 7^2 + 8^2 + 9^2 + 10^2 + 11^2 + 12^2.

There are exactly eleven palindromes below one-thousand that can be written as consecutive square sums, and the sum of these palindromes is 4164. Note that 1 = 0^2 + 1^2 has not been included as this problem is concerned with the squares of positive integers.

Find the sum of all the numbers less than 10^8 that are both palindromic and can be written as the sum of consecutive squares.

### Approach

Our approach to the problem was to first, solve it using a serial algorithm, then work to parallelize it.  We found this method the most useful because once we figured out the algorithms to solve the problem, we could then change the code around a bit so it can be parallelized.  This also allows us to compare the times between the serial and parallel versions.

In order to help with memory allocation, we first found out how many palindromes fit the conditions given above, and then we allocated that much memory in our arrays so we could then use **MPI Reduce** more effectively, rather than using another reduce to find the total number of palindromes. In other words, we were a tad lazy :).

## Data and results

Below is the data collected on the program.  Both the serial and parallel versions were tested. N refers to number of processors.

### Serial

**Number of Calculations:** 100020161
**Average Time (10 Tests):** 16.090s

### Parallel

**N ~> 2**
**Number of Calculations:** 100020329
**Average Time (10 Tests):** 9.067s

**N ~> 4**
**Number of Calculations:** 100020331
**Average Time (10 Tests):** 4.609s

**N ~> 8**
**Number of Calculations:** 100020335
**Average Time (10 Tests):** 2.385s


## Problem 2; Chip Defects
