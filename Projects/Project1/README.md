# Project 1; Project Euler problems 125, 302, and 307

### Collaborators ~> Sam Disharoon & Jordan Welch

https://github.com/samdish7/COSC420/tree/master/Projects/Project1

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

### Description

k defects are randomly distributed amongst n integrated-circuit chips produced by a factory (any number of defects may be found on a chip and each defect is independent of the other defects).

Let p(k,n) represent the probability that there is a chip with at least 3 defects.
For instance p(3,7) ≈ 0.0204081633.

Find p(20 000, 1 000 000) and give your answer rounded to 10 decimal places in the form 0.abcdefghij

### Approach

Our approach to this problem was to figure out the math surrounding the probabiltes worked, and then translate that into code. 



## Problem 3; Strong Achillies 

### Description


A positive integer n is powerful if p^2 is a divisor of n for every prime factor p in n.

A positive integer n is a perfect power if n can be expressed as a power of another positive integer.

A positive integer n is an Achilles number if n is powerful but not a perfect power. For example, 864 and 1800 are Achilles numbers: 864 = 2^5·3^3 and 1800 = 2^3·3^2·5^2.

We shall call a positive integer S a Strong Achilles number if both S and φ(S) are Achilles numbers.
For example, 864 is a Strong Achilles number: φ(864) = 288 = 2^5·3^2. However, 1800 isn't a Strong Achilles number because: φ(1800) = 480 = 2^5·3^1·5^1.

There are 7 Strong Achilles numbers below 104 and 656 below 108.

How many Strong Achilles numbers are there below 1018?

φ denotes Euler's totient function.

### Approach
