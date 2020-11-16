#include<stdio.h>
#include<stdlib.h>
/*
 * Think about what happens when the CPU has to add 1.0e5
 * and 1.0e-5
 * Have to align the exponents (one way!)
 * 100000.00000
 * 000000.00001 +
 * ==============
 * 100000.00001		<~ not enough digits in the mantissa to hold this!
 *
 * Largest with base B and t digits of prec was 
 * B - B^(-(t-1))
 *
 * Closest to zero: B^(-(t+1)) * B^L
 *
 * Other situation ~> adding x1 and x2, each with error eps
 * Then x1 + x2 result will be (x1 + eps) + (x2 + eps)
 * 			      =- (x1 + x2) + 2 * eps
 *
*/

// returns how close we have to get to x to see
// no difference in the floating point representation
float epsilonEstimate(float x){
	// want to test: the rep of x has error: xtilde
	float tmp = x;
	while(x + tmp != x){
		tmp /= 2;
	}
	return tmp;
}
int main(int argc, char** argv){

	float x = 1.0;	
	printf("Estimate for %1.2f, eps = %7.7f\n", x, epsilonEstimate(x));

	x = 100000.0;
	printf("Estimate for %7.7f, eps = %7.7f\n", x, epsilonEstimate(x));
	
	x = 100.0;
	printf("Try %7.7f + %7.7f = %7.7f\n",
	x,
	epsilonEstimate(x), 
	100 + epsilonEstimate(x)
	);
	
	x = 10000000000000000000000000.0;
	float tiny = 0.000000000000000000000001;
	printf("Infinity ~> large / small ~> %7.7f\n", x / tiny);

return 0;
}
