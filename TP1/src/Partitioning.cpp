/*
 * Partioning.cpp
 */

#include "Partitioning.h"


int s_recursive(int n,int k)
{
	if (k == 1 || k == n)
		return 1;
	else
		return s_recursive(n-1,k-1) + k* s_recursive(n-1,k);
}

int s_dynamic(int n,int k)
{


}


int b_recursive(int n)
{
	int b =0;
	for(int i=1; i <= n; i++)
		b += s_recursive(n,i);
	return b;
}

int b_dynamic(int n)
{
	return 0;
}


