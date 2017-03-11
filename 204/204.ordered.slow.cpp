#include <cstdio>
#include "../lib/tools.h"
//vp store values for each prime number 
//this is a sorted list of hamming number, but it is not necessary.
int find_minimal_number_index(vector<i64>& vp)
{
    int nmin = 1e9+1;
    int minIndex = -1;
    for(unsigned int i = 0; i < vp.size(); ++i) {
        if(vp[i] < nmin){
            nmin = vp[i];
            minIndex = i;
        }
    }
    return minIndex;
}
int main()
{
    vector<int> primes;
    primeWithin(primes, 100);
    vector<int> vIndices;
    vIndices.resize(primes.size(), 0);
    vector<int> hamming;
    vector<i64> values(primes.size());
    for(unsigned int i = 0; i < values.size(); ++i){
        values[i] = primes[i];
    }
    hamming.push_back(1);
    while(true){
        int minIndex = find_minimal_number_index(values);
        if(minIndex == -1) break;
        hamming.push_back(values[minIndex]);
        int value = values[minIndex];
        for(unsigned int i = minIndex; i < primes.size(); ++i) {
            if(values[i] == value) 
                values[i] = (i64)hamming[++vIndices[i]] * primes[i];
        }
    }
    printf("%zu\n", hamming.size());
}
