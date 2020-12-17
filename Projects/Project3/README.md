# Project 3; Cache Hit/Miss Simulation

### Collaborators; Sam Disharoon & Brock Forsythe

## Description

This project is meant to simulate how the cache in a CPU can affect how quickly data can be manipulated. 

### What we have so far; December 11th 2020

We have a serialized (working) version of matrix multiplication that demostrates the difference between how two algorithms work with the cache. 

We implemented a working parallel version of both cache examples, but the parallel doesn't work like it is supposed to. It gets slower as more nodes are added, plus it is slower than serial both. Which is not good. 

#### Let a and b be square matrices

The first algorithm is the standard multiplication algorithm that is typical taught in classes such as 320.

```
for (i = 0; i < n; i++)
	for(j = 0; j < n; j++)
		for(k = 0; k < n; k++)
```

The second algorithm is the same, but the last two for loops are switched. 

```
for (i = 0; i < n; i++)
	for(k = 0; k < n; k++)
		for(j = 0; j < n; j++)
```

Both ALGs access a[i,k] by the rows, but ALG 2 is invarient in the for loop, thus the data is kept in the registers, so a is only loaded once as opposed to n times.

In ALG 1, b[k,j] is accesed by columns, so only one element is used in the cache line. ALG 2 accesses b[k,j] in each row, which takes full advantage of the utilization of the cache lines.

This also is true for the parallel versions.  The column accessed function is much faster than the row access function. 

### Data; Each tested thoroughly (December 4th & 11th)

#### Serialized Multiplication

### 100 x 100 matrices

*ALG 1 Average Time:* 0.0023930s

*ALG 2 Average Time:* 0.0017116s

###1000 x 1000 matrices

*ALG 1 Average Time:* 1.6226671s

*ALG 2 Average Time:* 0.7889149s

###2000 x 2000 matrices

*ALG 1 Average Time:* 33.1050363s

*ALG 2 Average Time:* 7.9215698s

###5000 x 5000 matrices

*ALG 1 Average Time:* 1078.9809074s

*ALG 2 Average Time:* 129.8003666s

As you can tell, ALG 2 becomes much more efficient as n grows.

###Data; Each tested thoroughly

###Parallelized Multiplication on 5 nodes

###100 x 100 matrixes

*ALG 1 Average Time:* 0.0564578s

*ALG 2 Average Time:* 0.0460773

###1000 x 1000 matrixes

*ALG 1 Average Time:* 7.6908176s

*ALG 2 Average Time:* 6.6395664s
 
###2000 x 2000 matrixes

*ALG 1 Average Time:* 69.4638822s

*ALG 2 Average Time:* 39.0878732s
 
###5000 x 5000 matrixes

*ALG 1 Average Time:* 1663.9186044s

*ALG 2 Average Time:* 477.2144809s 

