#include <cstdio>
//#include <numeric>
#include <cstdlib>
using namespace std;

bool isBouncing(int i){
    int ix = i;
    int res1, dir1, dir = 0;
    int res = ix%10;
    ix = ix/10;
    while(ix){
          res1 = ix % 10; 
          if(res1 > res ) 
              dir1 = 1;
          else if (res1 == res) 
              dir1 = 0;
          else  
              dir1 = -1;

          ix = ix/10;
          res = res1;
          if(dir == 0) dir = dir1;
          if(dir1 == 0)continue;
          if(dir * dir1  < 0) return true;   
    }
    return false;
}

int main()
{
//    int bcount = 0;
//    for(int i = 1; i ; ++i){
//        if(isBouncing(i))++bcount;
//        if(bcount >0 && i%(i-bcount) == 0 && i/(i-bcount) == 100){
//            printf("%d %d\n",bcount, i);
//            break;
//        }
//    }
      int min = 100000;
      for(int i = 1; i<2100;++i){
        int xi = i*(i+1)/2;
        int jupper = 2.1e6/i/i;
          for(int j = i; j<jupper; ++j) {
              int diff = abs(2000000-xi*j*(j+1)/2);
              if(diff < min){
                  min = diff;
                  printf("%d %d %d %d\n", i, j,i*j, min);
              }
          }
      }
}
