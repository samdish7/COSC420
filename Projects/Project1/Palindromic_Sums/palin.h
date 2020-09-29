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

int conSquares(int num){
	int range = sqrt(num);
	//printf("Upper bound for %d ~> %d\n", num, range);
	
}
#endif
