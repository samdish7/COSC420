all: arXiv
arXiv: main.c
	mpicc -o arXiv main.c -lm
test1: test.c 
	mpicc -o test1 test.c -lm
test2: test2.c
	mpicc -o test2 test2.c -lm	
main.o: main.c
	mpicc -o main.o main.c -lm -g
clean:
	rm -r test1 test2
