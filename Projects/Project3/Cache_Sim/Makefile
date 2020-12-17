all: main
main: main.c
	mpicc -o main main.c -lm
all: cache
cache: cache.c
	mpicc -o cache cache.c -lm
clean:
	rm -f main
