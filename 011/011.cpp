#include <cstdio>
#include <cassert>
#include <vector>
using namespace std;
//lesson: variable must be initialized before use, 
//otherwise it is not safe;
//lesson, when make decision change(index, etc), it is important to
//check all codes to make sure boundary is intact


int main()
{
  int a[21][21], max = 0;
  FILE *pFile;
  pFile = fopen ("grid.txt","r");
  for(int i = 1; i<=20; ++i)
    for( int j = 1; j<=20; ++j)
        fscanf(pFile, "%d", &a[i][j]);
  fclose(pFile);
  int nbound= 100000000;
  // row search
  for (int i=1; i<=20; ++i)
  {
    for (int j = 1; j<= 17; ++j)
    {
        if(a[i][j] < a[i][j+4]) continue;
        int product=0;
        product = a[i][j]* a[i][j+1] * a[i][j+2]* a[i][j+3];
        assert(product < nbound && product >= 0);
        if(product > max)
          max = product;
    }
  }
  //column search
  for ( int j = 1; j <= 20 ; ++j)//col
  {
    for( int i = 1; i <= 17; ++i)
    {
        if(a[i][j] < a[i+4][j]) continue;
        int product = 0;
        product = a[i][j]*a[i+1][j]*a[i+2][j]*a[i+3][j];
        assert(product < nbound && product >= 0);
        if(product > max )
          max = product;
    }
  }
    
  //main diagonal
  for (int i = 0; i<17; ++i)
  {
    int jupper = 17 - i;
    for(int j=1; j <= jupper; ++j)
    {
        //if(a[i+j][j] <a[i+j + 4][j+4]) continue;
        int product = a[i+j][j]*a[i+j+1][j+1]*a[i+j+2][j+2]*a[i+j+3][j+3];
        assert(product < nbound && product >= 0);
        if(product > max)
          max = product;
    }
  }
  
  for (int i = 19;i >= 4; --i)
  {
    int jupper = i-3;
    for (int j =0; j<jupper;++j)
    {
        int product = a[20-j][i]*a[19-j][i-1]*a[18-j][i-2]*a[17-j][i-3];
        assert(product < nbound && product >= 0);
        if(product > max)
          max = product;
    }
  }
  //off diagonal
  for (int i = 4; i<=20; ++i)//top view
  {
    int jupper = i-3;
    for(int j=1; j <= jupper; ++j)
    {
        int product = a[j][i-j+1]*a[j+1][i-j]*a[j+2][i-j-1]*a[j+3][i-j-2];
        assert(product < nbound && product >= 0);
        if(product > max)
          max = product;
    }
  }
  
  for (int i = 2; i <= 17; ++i)
  {
    int jupper = 18-i;
    for (int j =0; j<jupper;++j)
    {
        int product = a[20-j][i+j]*a[19-j][i+j+1]*a[18-j][i+j+2]*a[17-j][i+j+3];
        assert(product < nbound && product >= 0);
        if(product > max)
          max = product;
    }
  }

  printf("max = %d\n", max);
  return 0;
}
