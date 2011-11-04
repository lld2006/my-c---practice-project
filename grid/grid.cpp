#include <cstdio>
#include <cassert>
#include <vector>
using namespace std;
//lesson: variable must be initialized before use, 
//otherwise it is not safe to use;
//lesson, when make decision change(index, etc), it is important to
//check all codes to make sure boundary is intact


int main()
{
  int a[21][21], max = 0;
  vector<int> flag; 
  FILE *pFile;
  pFile = fopen ("grid.txt","r");
  for(int i = 1; i<=20; ++i)
    for( int j = 1; j<=20; ++j)
        fscanf(pFile, "%d", &a[i][j]);
  fclose(pFile);
  // row search
  for (int i=1; i<=20; ++i)
  {
    flag.clear();
    flag.resize(18, 1);
    for ( int j = 1; j <= 17; ++j)
    {
        if(a[i][j] >= a[i][j+4])  
          flag[j+1] = 0;
        else
          flag[j] = 0;
    }
    for (int j = 1; j<= 17; ++j)
    {
        int product=0;
        if( flag[j])
        {
            product = a[i][j]* a[i][j+1] * a[i][j+2]* a[i][j+3];
            assert(product < 100000000 && product >= 0);
        }
        if(product > max)
          max = product;
    }
  }
  //column search
  for ( int j = 1; j <= 20 ; ++j)//col
  {
    flag.clear();
    flag.resize(18, 1);
    for ( int i = 1; i <= 17; ++i)//row
    {
        if(a[i][j] >= a[i+4][j])
          flag[i+1] = 0;
        else 
          flag[i] = 0;
    }
    for( int i = 1; i <= 17; ++i)
    {
        int product = 0;
        if( flag[i] )
        {
            product = a[i][j]*a[i+1][j]*a[i+2][j]*a[i+3][j];
            assert(product < 100000000 && product >= 0);
        }
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
        int product = a[i+j][j]*a[i+j+1][j+1]*a[i+j+2][j+2]*a[i+j+3][j+3];
        assert(product < 100000000 && product >= 0);
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
        assert(product < 100000000 && product >= 0);
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
        if(product >100000000 || product <0) printf("%d %d %d", i,j, product);
        assert(product < 100000000 && product >= 0);
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
        assert(product < 100000000 && product >= 0);
        if(product > max)
          max = product;
    }
  }

  printf("max = %d\n", max);
  return 0;
}
