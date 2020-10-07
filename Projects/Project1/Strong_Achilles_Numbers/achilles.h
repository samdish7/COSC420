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
	//int b = p * p; //p^2
	if(n % (p*p) == 0){
		return 1;
	}
	return 0;
}

int perfectPower(int n) {
	int i;
	for(i = 2; i <= sqrt(n); i++) {
		//int m = log(n) / log(2); //roundabout way of finding log2(n)
		int j;
		for(j = 2; j <= (log(n) / log(2)); j++) {
			if(pow(i,j) == n) {
				return 1;
			}
		}
	}
	return 0;
}

int gcd(int i, int n) {
	if(i == 0) {
		return n;
	}
	return gcd(n % i, i);
}

int totient(int n) {
	int i, a = 1;
	for(i = 2; i < n; i++) {
		if(gcd(i, n) == 1) {
			a++;
		}
	}
	return a;
}

#endif
