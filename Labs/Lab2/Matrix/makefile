all: matrix
matrix: matrix_test.o
	mpicc matrix_test.o -o matrix -lm
matrix_test.o: matrix_test.c matrix_lib.h
	mpicc -c matrix_test.c matrix_lib.h
clean:
	rm -f *.o matrix
