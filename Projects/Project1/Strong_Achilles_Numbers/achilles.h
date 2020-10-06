#ifndef ACHILLES_H
#define ACHILLES_H
#include<math.h>
int isPrime(int num){
	int i = 2;
	while(i <= sqrt(num)){
		if(num % i == 0){
			return 0; // Is not prime
		}
		i++;
	}
	return 1;
}

int powerful(int p/*Factor*/, int n/*Number*/){
	int b = p * p; //p^2
	if(n % b == 0){
		return 1;
	}
	return 0;
}

#endif
