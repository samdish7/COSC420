#include<stdio.h>
int main(int argc, char** argv){
	int n=1000000,m=20000,a,b,i;
	long double s=0,x=1,y=1;
	
	for(i = 0; i < m; i++){ // First summation 
		x *= n - i;
		x /= n;
	}
	for(b = 0; 2 * b <= m; b++){
		s += x;
		a = m-2*b;
		x /= 2*(n-a-b+1)*(b+1);
		x *= a*(a-1);
	}
	printf("s=%.10llf\n",1-s);
return 0;
}
