#include <cstdio>
#include "../lib/typedef.h"
vector<i64> factorial;
i64 searchN3(int total, int cdig, i64 prod, const vector<int>& constraint){
    if(total == 0) return prod;
    if(cdig == 9){
        if(total <= 3)
            return prod/factorial[total];
        else
            return 0;
    }
    i64 sum = 0;
    int tmax = total < constraint[cdig]? total: constraint[cdig];
    for(int i = 0; i<= tmax; ++i){
        sum += searchN3(total - i, cdig+1, prod/factorial[i], constraint);
    }
    return sum;
}

int main(){
    int nl = 18;
    i64 prod = 1;
    i64 sum = 0;
    factorial.push_back(1);
    for(int i = 1; i <= 18; ++i){
        prod *= i;
        factorial.push_back(prod);
    }
    vector<int> constraint;
    constraint.resize(10, 3);//0--9 maximum 3
    --constraint[1];
    // let the first number to be 1, we just consider the other 17 digits,
    // finally, we just multiply everything by 9
    sum = searchN3(nl-1, 0, factorial[nl-1], constraint)*9; // total number unused, currently need to be processed
    printf("%lld\n", sum ); 
}
