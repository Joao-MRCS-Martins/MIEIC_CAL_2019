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
    vector<int> values(k,1);
    for(int i =0; i < (n-k); i++) {
        for(int j =1; j < k; j++) {
            values[j] = values[j-1] + (j+1)*values[j];
        }
    }
    return values[k-1];
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
    int bell =0;
    for(int i = 1; i <= n; i++) {
        bell += s_dynamic(n, i);
    }
	return bell;
}


