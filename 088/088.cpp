#include <cstdio>
#include <vector>
#include <cmath>
#include <cassert>
using namespace std;
void minimalSet(int orig, int num, int sum, int count, vector<int>& minFlag){
    if(num == 1) return;
    int thresh = sqrt((double)num);
    for(int i = 2; i <= thresh; ++i){
        if(num % i == 0){
            //first record current 
            int other = num/i;
            int sum1 = sum + i + other;
            int diff = orig - sum1;//padded with ones
            int count1 = count +2 + diff;
            if(minFlag[count1] > orig){
                minFlag[count1] = orig;
            }
            //record left
            minimalSet(orig, i, sum+ other, count + 1, minFlag);
            minimalSet(orig, other, sum+i, count+1, minFlag);
        }
    }
}
int main(){
    int error = 10000000;
    int limit = 12000;
    vector<int> minFlag;
    minFlag.resize( limit*2+1, error);
    for(int i =4; i <= limit*2; ++i){
        int sum = 0;
        int count = 0;
        minimalSet(i,i, sum, count, minFlag);
    }
    int sum = 0;
    int total = 0;
    vector<int> vset;
    vset.resize(2*limit+1, 0);
    for(int k = 2; k <= limit;  ++k){
        if(minFlag[k] == error){
            printf("%d not found\n", k);
        }else{
            vset[minFlag[k]] = 1;
            total += minFlag[k];
        }
    }
    for(int i=0 ; i< 2*limit +1; ++i){
        if(vset[i] == 1)
            sum += i;
    }
    printf("sum is %d\n", total);
}
