# Lab 2; Scatter/Reduce MPI Functions & Matrix Library

### Collaborators: Sam Disharoon and Jordan Welch

## Task 1 ~> Introduction to Scatter and Reduce functions in MPI

The first task of this lab is write a program that demostrates the Scatter and Reduce functions that MPI gives us. The goal is to create two (preferably large) vectors and display their inner product. 

### How to run

To execute the code, enter the following command:
- mpiexec -n *N* ./scat *size*

### Key:

*N*: Number of processors requested for use
*size*: Size of vectors passed

## Testing:

Time, number of processors, and vector size is recorded below on numberous tests.

### N ~> 1

**Vector Size** ~> 10

**Time:**
	
	1. .027s
	2. .029s
	3. .027s
	4. .026s
	5. .028s
**Average:** .0274s

**Vector Size** ~> 100

**Time:**

	1. .030s
	2. .031s
	3. .026s
	4. .032s
	5. .033s
**Average:** ~> .0304s

**Vector Size** ~> 1000

**Time:**

	1. .027s
	2. .026s
	3. .026s
	4. .025s
	5. .026s
**Average:** ~> .026s

**Vector Size** ~> 100000

**Time:**

	1. .035s
	2. .033s
	3. .031s
	4. .029s
	5. .031s
**Average:** ~> .0318s


### N ~> 2

**Vector Size** ~> 10

**Time:**

	1. .027s
	2. .028s
	3. .028s
	4. .027s
	5. .028s
**Average:** ~> .0275s

**Vector Size** ~> 100

**Time:**

	1. .027s
	2. .027s
	3. .025s
	4. .026s
	5. .027s
**Average:** ~> .0264s

**Vector Size** ~> 1000

**Time:**

	1. .030s
	2. .026s
	3. .024s
	4. .027s
	5. .027s
**Average:** ~> .0268s

**Vector Size** ~> 100000

**Time:**

	1. .031s
	2. .034s
	3. .032s
	4. .035s
	5. .032s
**Average:** ~> .0328s

### N ~> 4

**Vector Size** ~> 10

**Time:**

	1. .031s
	2. .029s
	3. .026s
	4. .028s
	5. .029s
**Average:** ~> .0286s

**Vector Size** ~> 100

**Time:**

	1. .033s
	2. .028s
	3. .032s
	4. .028s
	5. .030s
**Average:** ~> .0302s

**Vector Size** ~> 1000

**Time:**

	1. .030s
	2. .029s
	3. .025s
	4. .027s
	5. .026s
**Average:** ~> .0274s

**Vector Size** ~> 100000

**Time:**

	1. .032s
	2. .034s
	3. .034s
	4. .034s
	5. .036s
**Average:** ~> .0340s

### N ~> 8

**Vector Size** ~> 10

**Time:**

	1. .035s
	2. .031s
	3. .032s
	4. .032s
	5. .032s
**Average:** ~> .0324s

**Vector Size** ~> 10

**Time:**

	1. .033s
	2. .033s
	3. .033s
	4. .034s
	5. .033s
**Average:** ~> .0332s

**Vector Size** ~> 1000

**Time:**

	1. .031s
	2. .033s
	3. .032s
	4. .032s
	5. .029s
**Average:** ~> .0314s

**Vector Size** ~> 100000

**Time:**

	1. .038s
	2. .037s
	3. .036s
	4. .037s
	5. .038s
**Average:** ~> .0372s

## Questions

**A)** The theoretical time complexity of this algorithm is: 
**BEST** ~> O(1) because if you have the same amount of processors as computations, then you can finish in a single step.

**WORST** ~> O(N/p) because if you have very large vector sizes, then the time is shortened (theoretically) by the number of processors you have.

**B)** No, It actually tends to take longer in some cases according to the data shown above.

**C)** This could be used in a linear algebra class to describe how to calculate the inner product of two very large vectors rather than trying to do it by hand.

**D)** We could find a way to make the increased nodes actually speed up the process instead of being inconsistent with time speeds.

## Task 2 ~> Implement a Matrix Library

This part of the lab was to create an importable matrix library.  The functions included are addition, subtraction, multiplication, and transpose and will be displayed in a sample output below

### How to run

To execute code, enter the following command:
	- mpiexec -n *N* ./matrix *A* *B* *C* *D*

### Key: 

*N*: Number of processors desired
*A*: Matrix 1 number of rows
*B*: Matrix 1 number of columns
*C*: Matrix 2 number of rows
*D*: Matrix 2 number of columns

## Testing

Time, number of processors, and size of matrices is recorded below with various sizes. 

*Note:* I'm only using matrices that are the same dimensions as the other.

*Note2:* I only did the cases where you couldn't multiply the matrices on the N = 1 phase because it is redundant to do them with the others and I wanted to save time.

### N ~> 1

**Matrix Sizes** ~> 100x100

**Time:**

	1. 0.118s
	2. 0.124s
	3. 0.115s
	4. 0.120s
	5. 0.118s
**Average:** 0.1190s

**Matrix Sizes** ~> 100x1000

**Time:**

	1. 0.040s
	2. 0.041s
	3. 0.041s
	4. 0.039s
	5. 0.040s
**Average:** 0.0402s

**Matrix Sizes** ~> 500x500

**Time:**

	1. 6.818s
	2. 6.913s
	3. 6.789s
	4. 6.606s
	5. 6.679s
**Average:** 6.7610s

**Matrix Sizes** ~> 500x1000

**Time:**

	1. 0.083s
	2. 0.071s
	3. 0.086s
	4. 0.081s
	5. 0.081s
**Average:** 0.0804s

**Matrix Sizes** ~> 1000x1000

**Time:**

	1. N/A
	2. N/A
	3. N/A
	4. N/A
	5. N/A
**Average:** N/A

### N ~> 4

**Matrix Sizes** ~> 100x100

**Time:**

	1. 0.296s
	2. 0.304s
	3. 0.305s
	4. 0.295s
	5. 0.295s
**Average:** 0.299s

**Matrix Sizes** ~> 500x500

**Time:**

	1. 10.239s
	2. 10.300s
	3. 10.375s
	4. 10.318s
	5. 10.430s
**Average:** 10.3324s

**Matrix Sizes** ~> 1000x1000

**Time:**

	1. 1m, 8.413s
	2. 1m, 2.893s
	3. 1m, 2.712s
	4. 1m, 2.351s
	5. 1m, 2.332s
**Average:** 

### N ~> 8

**Matrix Sizes** ~> 100x100

**Time:**

	1. 0.376s
	2. 0.365s
	3. 0.352s
	4. 0.348s
	5. 0.358s
**Average:** 0.3598s

**Matrix Sizes** ~> 500x500

**Time:**

	1. 12.137s
	2. 12.269s
	3. 12.218s
	4. 12.295s
	5. 12.104s
**Average:** 12.2046s

**Matrix Sizes** ~> 1000x1000

**Time:**

	1. 1m, 10.380s
	2. 1m, 10.084s
	3. 1m, 9.752s
	4. 1m, 10.033s
	5. 1m, 9.862s
**Average:** 1m, 10.0222s

## Questions

**A)** The theoretical time complexity is as follows:
**Best:** O(1)  **Worst:** O(N^2/p)

**B)** It can't compute a 1000x1000 matrix with just 1 node, it segfaults.  It also seems to get slower as the number of processors goes up. This seems weird.

**C)** Matrix operations have many uses, including spreadsheets, data analysis, and teaching. 

**D)** Figure out how to properly distribute the data to increase time-saving ability
