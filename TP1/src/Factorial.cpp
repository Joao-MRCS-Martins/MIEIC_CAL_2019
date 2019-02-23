/*
 * Factorial.cpp
 */

#include "Factorial.h"
#include <iostream>
int factorialRecurs(int n)
{
	if(n ==1)
		return 1;
	else
		return n*factorialRecurs(n-1);

}

int factorialDinam(int n)
{
	int a = 1;
	for(int i =0; i<n;i++) {
		a *= (n-i);
	}
	return a;
}
