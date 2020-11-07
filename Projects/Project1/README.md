# Project 1; Project Euler problems 125, 216, and 307

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

In order to help with memory allocation, we first found out how many palindromes fit the conditions given above, and then we allocated that much memory in our arrays so we could then use **MPI_Reduce** more effectively, rather than using another reduce to find the total number of palindromes. In other words, we were a tad lazy :).

## Data and results

Below is the data collected on the program.  Both the serial and parallel versions were tested. N refers to number of processors.

### Serial

==============================================

**Number of Calculations:** 100020161

**Average Time (10 Tests):** 16.090s

==============================================

### Parallel

==============================================

**N ~> 2**

**Number of Calculations:** 100020329

**Average Time (10 Tests):** 9.067s

==============================================

**N ~> 4**

**Number of Calculations:** 100020331

**Average Time (10 Tests):** 4.609s

==============================================

**N ~> 8**

**Number of Calculations:** 100020335

**Average Time (10 Tests):** 2.385s

==============================================

## Problem 2; Primality of numbers of the form 2n^2 -1

### Description

Consider numbers t(n) of the form t(n) = 2n^2-1 with n > 1.
The first such numbers are 7, 17, 31, 49, 71, 97, 127 and 161.
It turns out that only 49 = 7*7 and 161 = 7*23 are not prime.
For n ≤ 10000 there are 2202 numbers t(n) that are prime.

How many numbers t(n) are prime for n ≤ 50,000,000 ?

### Approach

Our approach to this problem was to first get an algorithm to test if the numbers are prime.  Once that occured, then we coded the algorithm in serial to make sure we got the correct output for n ≤ 10000.  Assuming as n grew, the time would also grow, we decided against running our code in serial for n ≤ 50000000 because we can assume it would take a very long time. 

For memory allocation, the only memory we used was an array to hold the value which was the number of primes each processor found, and another array that stored the total number of primes found.  These were used by **MPI_Reduce**

A big challenge was figuring out how to deal with the massive overhead of checking the numbers.  We used brute force because it worked, but one way we could have made this more efficient (especially for the large numbers) is maybe somehow keeping track of what certain numebrs are prime, and then going from there so it can reduce the number of calculations done.  We could have also found a way to parallize the prime function to make it more efficient.

## Data and Results

Both serial and parallel versions were tested below.  We didn't bother testing the serial for anything above 50k because we figured it would take way too much time. For the larger sets, we only ran one test because we didn't want to wait for it to finish more than once.

**Key:**

1. N is the upper bound
2. P is number of Processors

### Serial

==============================================

**N** ~> 10000

**Number of Calculations** ~> ~14,623,332

**Average Time (10 Tests)** ~> 0.263s

**Answer** ~> 2202

==============================================

**N** ~> 50000

**Number of Calculations** ~> ~306,713,714

**Average Time (10 Tests)** ~> 3.909s

**Answer** ~> 9175

==============================================

**N** ~> 50,000,000

**Average Time ** ~> A very long time

**Answer** ~> ???

==============================================

### Parallel

==============================================

**N** ~> 10,000

**P** ~> 4

**Number of Calculations per Proc** ~> ~3,650,000

**Average Time (10 Tests)** ~> 0.101s

**Answer** ~> 2,202

==============================================

**N** ~> 10,000

**P** ~> 24

**Number of Calculations per Proc ~> ~625,000

**Average Time (10 Tests)** ~> 0.155s

**Answer** ~> 2,202

==============================================

**N** ~> 50,000

**P** ~> 4

**Number of Calculations per Proc ~> ~75,000,000

**Average Time (10 Tests)** ~> 1.121s

**Answer** ~> 9,175

==============================================

**N** ~> 50,000

**P** ~> 24

**Number of Calculations per Proc ~> ~12,750,000

**Average Time (10 Tests)** ~> 0.760s

**Answer** ~> 9,175

==============================================

**N** ~> 500,000

**P** ~> 4

**Number of Calculations per Proc ~> ~6,320,000,000

**Average Time (5 Tests)** ~> 1m 20.456s

**Answer** ~> 74810

==============================================

**N** ~> 500,000

**P** ~> 24

**Number of Calculations per Proc ~> ~1,050,000,000

**Average Time (5 Tests)** ~> 29.150s

**Answer** ~> 74810

==============================================

**N** ~> 50,000,000

**P** ~> 144

**Number of Calculations per Proc ~> ~9,000,000,000,000 (~1.296 * 10^15 total)

**Time** ~> ~ 19 hours

**Answer** ~> 5,437,849

==============================================

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

Our approach was similar to the previous two problems, however, this was much more complicated in the sense that there were many many more conditions and operations that needed to be checked/done. We struggled heavily with this problem because like above, we tried to brute force the algorithm with no success for even 10^8.  We ran 360 processors at it for an entire day, and still didn't give us the answer to 10^8, so 10^18 would take an unbelievable amount of time.

We tried to optimize it by letting all the processors create a table of prime numbers to check because you didn't have to check any prime < 630000. Which left for each number, AT MOST 51341 numbers to check rather than our first apporach (which is seen in our serial code) which was to check all factors of N.  The only factors that matter were the prime ones however, so we thought that reducing that number of checks for both n and totient of n would speed up the result.  But it didn't seem to make any difference unfortunately.  
The problem is the workload is not split evenly among the processors.  We noticed that the group is usually split in four phases. The first phase found most of the primes and therefore got done very quickly.  The second and thrid phases found some primes and had to do more work because they also found some Strong Achilles Numbers.  The last group gets the "worst" numbers and least amount of primes, so therefore their workload is absolutely absurd and takes a crazy long time to finish.

If we understood the math more, maybe we could find a way to work around the brute force method, but we didn't figure anything out. Therefore, we originally started to do number of operations, but since we couldn't even get the answer to be displayed, we didn't bother. 

## Data and Results

We didn't do much higher number testing for reasons stated above, but we were able to do some of the lower value testing.

**Key:**

1. N is upper bound
2. P is number of processors

### Serial

==============================================

**N** ~> 10,000

**Average Time (10 Tests)** ~> 0.244s

**Answer** ~> 7

==============================================

**N** ~> 50,000

**Average Time (10 Tests)** ~> 0.648s

**Answer** ~> 21

==============================================

**N** ~> 10^18

**Average Time** ~> Unimaginable length of time

**Answer** ~> ???

==============================================

### Parallel

==============================================

**N** ~> 10,000

**P** ~> 4

**Average Time (10 Tests)** ~> 0.270s

**Answer** ~> 7

==============================================

**N** ~> 10,000

**P** ~> 24

**Average Time (10 Tests)** ~> 0.818s

**Answer** ~> 7

==============================================

**N** ~> 50,000

**P** ~> 4

**Average Time (10 Tests)** ~> 0.584s

**Answer** ~> 21

==============================================

**N** ~> 50,000

**P** ~> 24

**Average Time (10 Tests)** ~> 1.076s

**Answer** ~> 21

==============================================

**N** ~> 1,000,000

**P** ~> 4

**Average Time (10 Tests)** ~> 32.975s

**Answer** ~> 99

==============================================

**N** ~> 1,000,000

**P** ~> 24

**Average Time (10 Tests)** ~> 12.878s

**Answer** ~> 99

==============================================

**N** ~> 100,000,000

**P** ~> 360

**Average Time** ~> > 24 hours... not sure exactly how long

**Answer** ~> 656 (It is given to us)

==============================================

**N** ~> 10^18

**P** ~> 360

**Average Time** ~> Slightly less time than serial, but still absurd

**Answer** ~> ???

==============================================

## What this project taught us

Brute force is a really bad method to solve large problems, even when splitting th work among many processors. As strong achilles shows us, the work load may not be split evenly amongst the processors. This means that the time taken is more affected by the heavy workloads some of the processors may experience.  So learning more effecient algorithms and understanding better how the math works can go miles into solving the problem. 
