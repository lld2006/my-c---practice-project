#include <cstdio>
#include <numeric>
#include <vector>
#include <cassert>
using namespace std;

//lesson learned, made assumption here.
//all numbers are greater than 0, but actually it could be 0

//bool pandigit(const GeneralInteger& f)
//{
//    if(f.numberDigit() < 9) return false; 
//    vector<int> vec;
//    vec.resize(9, 0);
//
//    for ( int i = f.numberDigit()-9; i < f.numberDigit(); ++i)
//    {
//        assert( f.getNthDigit(f.numberDigit() -1) != 0);
//        int n = f.getNthDigit(i);
//        if( n == 0) return false;
//        vec[n-1] = 1;
//    }
//    int sum = accumulate( vec.begin(), vec.end(),0);
//    if(sum != 9) return false;
//    //printf("last nine found\n");
//    vec.clear();
//    vec.resize(9,0);
//
//    for(int i = 0; i < 9; ++i)
//    {
//        int n = f.getNthDigit(i);
//        if( n == 0) return false;
//        vec[n-1] = 1;
//    }
//    sum = accumulate( vec.begin(), vec.end(), 0);
//    if( sum != 9) 
//        return false;
//    else
//        return true;
//}
//
void calcFib( const vector<int>& f1, const vector<int>& f2, vector<int>& f3)
{
    int size1 = f1.size();
    int size2 = f2.size();
    int size3 = f3.size();
    assert(size3 <= size1);
    assert(size3 <= size2);
    assert(size1 >= size2);
    f3.resize(size1, 0 );
    int res=0, num=0;
    for( int i = 0; i < size2; ++i)
    {
        num = f1[i] + f2[i] + num;
        res = num % 1000000000;
        num = num / 1000000000;
        f3[i] = res;
    }
    //num will be credited to the next level
    for( int i = size2; i < size1; ++i)
    {
        num = f1[i] + num;
        res = num % 1000000000;
        num = num / 1000000000;
        f3[i] = res;
    }
    if(num)
        f3.push_back(num);
}

bool pandigit(const vector<int>&  fi)
{
    int size = fi.size();
    if( size <= 1) return 0;

    int num = fi[0];
    int res=0, sum = 0;
    vector<int> vec;
    vec.resize(9,0);
    while(num){
        res = num % 10;
        num = num / 10;
        if(res == 0) return false;
        vec[res - 1] = 1;
    }
    sum = accumulate( vec.begin(), vec.end(),0);
    if( sum != 9) 
        return false;
    else
        printf("last found\n");

    num = fi[size - 1];
    int num1 = fi[size - 2]; 
    sum = 0;
    vec.clear();
    vec.resize(9, 0);
    while(num){
        res = num % 10;
        num = num / 10;
        num1 = num1 / 10;
        if(res == 0) return false;
        vec[res - 1] = 1;
    } 
    while(num1){
        res = num1 % 10;
        num1 = num1 / 10;
        if(res == 0) return false;
        vec[res - 1] = 1;
    } 
    
    sum = accumulate( vec.begin(), vec.end(),0);
    if( sum != 9) 
        return false;
    else
        return true;
}

int main()
{
   int kth =2;
   vector<vector<int> > fib(3); 
   fib[1].push_back(1);
   fib[2].push_back(0);
   fib[0].push_back(1);
   while(true ){
       calcFib(fib[(kth-1)%3], fib[(kth-2)%3], fib[kth%3]);
       if(pandigit(fib[kth%3])) 
           break;
           ++kth;
       if( kth % 10000 == 0)
           printf("%d\n", kth);
   }
   printf("pandigit fibonacci is found at %d\n", kth);
}
