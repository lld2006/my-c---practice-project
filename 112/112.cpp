#include <cstdio>
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
    int count = 0;
    for(unsigned int i = 100; i; ++i){
        if(isBouncing(i))
            ++count;
        if(((i%100)==0) && (count ==i/100*99 )) {
            printf("%d\n", i);
            break;
        }
    }
}
