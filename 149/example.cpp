#include <iostream>
#include <stdlib.h>
#include <time.h>
using namespace std;
typedef int ui;
double pauze;

const ui m=2000;
const ui M=m*m;
ui s[M];
ui a[m][m];

void make_s();
void make_a();

int main()
{
double time=clock();
make_s();
make_a();


long long X=0;

// horizontal
for(int i=0;i<m;i++)
   {
   long long S=0;
   for(int j=0;j<m;j++)
      {
      if(S<0) S=0;
      S+=a[i][j];
      if(S>X) X=S;
      }
   }

// vertical
for(int i=0;i<m;i++)
   {
   long long S=0;
   for(int j=0;j<m;j++)
      {
      if(S<0) S=0;
      S+=a[j][i];
      if(S>X) X=S;
      }
   }


cout<<X<<" in "<<clock()-time<<"ms"<<endl;
system("Pause");
return 0;
}


void make_s()
{
for(ui k=1;k<=55;k++) 
   {
   long long s_t=300007*k;
   s_t*=k*k;
   s_t+=100003; 
   s_t-=200003*k;
   s_t=s_t%1000000;
   s_t=s_t-500000;
   s[k]=s_t;
   }

for(ui k=56;k<=M;k++) 
   {
   long long s_t=(s[k-24] + s[k-55]);
   s_t+=1000000;
   s_t=s_t%1000000;
   s_t=s_t-500000;
   s[k]=s_t;
   }
}

void make_a()
{
for(int i=0;i<m;i++)
   {for(int j=0;j<m;j++) a[i][j]=s[i*m+j]; }
}
