all: scat
scat: scatter_reduce.o
	mpicc scatter_reduce.o -o scat -lm
scatter_reduce.o: scatter_reduce.c
	mpicc -c scatter_reduce.c
clean:
	rm -f *o scat
