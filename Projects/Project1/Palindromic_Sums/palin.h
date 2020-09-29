//Project Euler Problem 125 header function
//Sam Disharoon & Jordan Welch
#ifndef PALIN_H
#define PALIN_H
#include<stdio.h>
#include<math.h>
int isPalin(int num){   
    int r,sum=0,temp;    
   
    temp=num;    
    while(num>0)    
    {    
    r=num%10;    
    sum=(sum*10)+r;    
    num=num/10;    
    }    
	if(temp==sum){
		return temp;
	} else{
		return 0;
	}
}

int conSquares(long unsigned int palin){
	int range = sqrt(palin); //Upper bound
	int lower = 1;	// Lower bound
	int i;
	unsigned long long int sumSquares;
	for(;lower < range; lower++){	// Keeps track of lower bound
		//while(sumSquares < palin){	// Keeps track of if palin is a sum of consecutive squares
		sumSquares = 0;
			for (i = lower; i <= range; i++){	// Adds the consecutive squares starting at lower bound and going until upper
				sumSquares += pow(i,2);
				if(sumSquares == palin){
					return palin;
				}
				if(sumSquares > palin){
					break;
				}
			}
		//}
	}
	
	//printf("Upper bound for %d ~> %d\n", num, range);
	return 0;	
}
#endif
