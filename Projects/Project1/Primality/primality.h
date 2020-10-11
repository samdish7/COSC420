#ifndef PRIMALITY_H
#define PRIMALITY_H
#include<math.h>

int isPrime(long long unsigned int num){
	long long unsigned int i = 2;
	while(i <= (long long unsigned int)sqrt(num)){
		if(num % i == 0){
			return 0; // Is not prime
		}
		i++;
	}
	return 1;
}

#endif
