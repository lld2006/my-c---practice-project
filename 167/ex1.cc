#include <cstdio>
#include <cstring>
unsigned long long ulam_diff(int v,int term)
{
   unsigned long long diff=0;
   const int size = 10*term;
   unsigned char *a = new unsigned char[size];
   memset(a,0,size);
   a[2]=a[2*v+2]=1;
   for(int i = v; i<=2*v+3; i+=2)
      a[i]=1;
   int n = v+2;
   for(int j = 0; j < term; j++)
      {
         //bn = 2n+1;
         //bn=d(bn-1-1)+d(bn-v-1-1)
         do
         {
         a[2*n+1]=a[2*(n-1)+1] ^ a[2*(n-v-1)+1];
         n++;
         diff+=2;
         }while(a[2*n-1]==0);
      }
   delete[]a;
   return diff;
}
//ulam sequences
void a167()
{
   int p[]={32,26,444,1628,5906,80,126960,380882,2097152};
   int d[]={126,126,1778,6510,23622,510,507842,1523526,8388606};

   unsigned long long sum=0;
   for(int i = 0; i <9; i++)
   {
      int v = 2*i+5;
      int first_term = 2*v+3;
      unsigned long long t1 = 1e11-7-i;
      unsigned long long reps = t1/p[i];
      unsigned long long num = d[i]*reps+first_term;
      unsigned long long rem = t1-reps*p[i];
      num+=ulam_diff(v,rem);
      sum+=num;
   }
   printf("%lf",(double)sum);
}

int main()
{
    a167();
}
