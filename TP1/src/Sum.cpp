/*
 * Sum.cpp
 */

#include "Sum.h"
#include <chrono>

string calcSum(int* sequence, int size)
{
	string res;
	for (int i = 1 ; i <= size; i++) {
		int idx = 0;
		int sum = -1;
		for(int j=0; j+i< size+1; j++) {
			int part_sum = 0;
			for(int k = 0 ; k < i ; k++) {
				part_sum += sequence[j + k];
			}
			if( sum > part_sum || sum == -1) {
				sum = part_sum;
				idx = j;
			}
		}
			res += to_string(sum) + "," + to_string(idx) + ";";

	}
	return res;
}

