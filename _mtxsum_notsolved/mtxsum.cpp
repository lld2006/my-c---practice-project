//problem not solved. need to think about other algo, this simple one does not
//work
#include <cstdio>
#include <cassert>
int main()
{
  int a[16][16];
  FILE* fp;
  fp=fopen("mtx.txt", "r");
  for(int i=1; i<=15; ++i)
    for(int j=1; j<=15;++j)
      fscanf(fp, "%d", &a[i][j]);
  fclose(fp);

  int col[16], max=0;// each column picked;
  for(int i=1; i <=15; ++i)
  {
    col[i]=i;
    max += a[i][i];
  }

  bool switched=true;
  while (switched)
  {
    switched  = false;
    for(int i = 1; i <= 15; ++i)
      for(int j = 1; j <= 15; ++j)
      {
	if(i == j)continue;
        int sum0 = a[i][col[i]]+a[j][col[j]];
        int sum1 = a[i][col[j]]+a[j][col[i]]; 
        assert(sum0 > 0 && sum0 < 2000);
        assert(sum1 > 0 && sum1 < 2000);
        if(sum0 < sum1)
        {
          int temp = col[i];
          col[i] = col[j];
          col[j] = temp;
          switched = true;
          max +=  sum1 - sum0;
          printf("max now is %d\n", max);
        }
      } 
  }
    return 0;
}

