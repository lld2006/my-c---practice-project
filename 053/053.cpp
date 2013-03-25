//using pascal triangle to figure out the number
//should be simple and straight forward.
//lesson, I made a wrong assumption, I just want to keep all numbers
//below 1M, sometimes the result is wrong, I should keep 1 greater than 1M
#include <cstdio>
#include <vector>
#include <cassert>
using namespace std;
int main()
{
   int nmax = 1000000;
   vector<int> v0, v1; 
   v0.reserve(100);
   v1.reserve(100);
   v0.push_back(1);
   int level = 1;
   int total = 0;
   while(level < 100){
        ++level;
        v1.clear();
        v1.push_back(1);
        bool stop = false;
        for( int i = 0; i < (level-1)/2; ++i){
            //assert(v0.size() == level/2);
            int value = v0[i] + v0[i+1];
            v1.push_back(value);
            if(value > nmax){
                int start = v1.size()-1;
                assert(level>= 2*start);
                total += (level-start*2+1);
                stop = true;
                swap(v0, v1);
                break;
            }
        }
        if(stop) continue;
        if(level % 2 == 0 && static_cast<int>(v0.size()) == level/2){
            int value = 2* v0.back();
            v1.push_back(value);
        }
        swap(v0, v1);
   }
   printf("%d\n", total);
}
