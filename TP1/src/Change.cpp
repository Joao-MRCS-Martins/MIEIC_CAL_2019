/*
 * Change.cpp
 */

#include "Change.h"

string calcChange(int m, int numCoins, int *coinValues)
{
    string res;
    bool flag = true;
    for(int i = numCoins-1;i>=0;) {
       cout << coinValues[i] << endl;
        if(m >= coinValues[i]) {
            res += to_string(coinValues[i]) + ";";
            //cout << res << endl;
            m-=coinValues[i];
            flag=false;
        }
        else {
            i--;
            continue;
        }
    }

    if(m>0 && flag)
        return "-";
    
    return res;
}


