/*
 * Change.cpp
 */

#include "Change.h"

string calcChange(int m, int numCoins, int *coinValues)
{
    int minCoins[m+1]={0};
    int lastCoin[m+1]={0};
    string res;
    for(int i=0;i<numCoins;i++) {
        for (int k = 0; k <= m; k++) {
            if ((coinValues[i] <= k) && (minCoins[k - coinValues[i]] + 1 < minCoins[k] || minCoins[k] == 0)) {
                minCoins[k] = minCoins[k - coinValues[i]] + 1;
                lastCoin[k] = coinValues[i];
            }
        }
    }

    while (m>0) {
        res += to_string(lastCoin[m]) + ";";

        if(lastCoin[m] ==0) {
            res = "-";
            break;
        }
        m -= lastCoin[m];
    }

    return res;
}


