#include <iostream>
#include <stdlib.h>
#include <time.h>
using namespace std;
typedef long long ui;

const int M=33554432;
const ui M2=1125899906842624ll;

bool f[M+1];
int p[2200000];

int main()
  {
  double time=clock();
  
  // prime sieve in f. saving individual primes in p
  f[0]=f[1]=0;
  for(int i=2;i<=M;i++) f[i]=1;
  
  int am=0;
  for(int i=2;i<=M;i++)
     {
     if(f[i]==1)
       {
       p[am]=i;
       am++;
       for(int j=i+i;j<=M;j+=i) f[j]=0;
       }
     }
  
  // inclusion exclusion principle
  ui S=M2;
  
  long pp[9];
  for(int j0=0;j0<am;j0++) {pp[0]=p[j0];                           S-=M2/pp[0]/pp[0];
  for(int j1=0;j1<j0;j1++) {pp[1]=pp[0]*p[j1]; if(pp[1]>=M) break; S+=M2/pp[1]/pp[1]; 
  for(int j2=0;j2<j1;j2++) {pp[2]=pp[1]*p[j2]; if(pp[2]>=M) break; S-=M2/pp[2]/pp[2];
  for(int j3=0;j3<j2;j3++) {pp[3]=pp[2]*p[j3]; if(pp[3]>=M) break; S+=M2/pp[3]/pp[3];
  for(int j4=0;j4<j3;j4++) {pp[4]=pp[3]*p[j4]; if(pp[4]>=M) break; S-=M2/pp[4]/pp[4];
  for(int j5=0;j5<j4;j5++) {pp[5]=pp[4]*p[j5]; if(pp[5]>=M) break; S+=M2/pp[5]/pp[5];
  for(int j6=0;j6<j5;j6++) {pp[6]=pp[5]*p[j6]; if(pp[6]>=M) break; S-=M2/pp[6]/pp[6];
  for(int j7=0;j7<j6;j7++) {pp[7]=pp[6]*p[j7]; if(pp[7]>=M) break; S+=M2/pp[7]/pp[7];
  }}}}}}}}
  
  
  cout<<S<<" in "<<(clock()-time)/1000<<" seconds"<<endl;
  system("Pause");
  return 0;
  }
