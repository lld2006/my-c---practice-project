#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <vector>
using namespace std;
typedef long long ui;

struct info
{
friend class Ulam;
private:
   int first_term;    // the first element after which U gets periodic (= h+3)
   int length;        // length
   ui difference;     // difference between 2 elements of 2 consecutive periods
   ui sum;            // sum of all elements 
};                      

class Ulam
{
private:
   int n;              // U(2,2*n+1) 
   int h;              // second even term = 4*n+1 =
                       // maximal difference between 2 consecutive terms
                       
   vector<int> U;
   vector<short> s;    // s[ i%h ] = number of ways that add up to i
   
   // info
   info pre_period;    // info about U before it gets periodic.
   info period;        // period info

public:
   // constructors
   Ulam () {};
   Ulam (int);
   Ulam (int,int);
   
   // other
   void determine_pre_period();
   void determine_period();
   void print_info();   
   
   // finding U(2,2*n+1)M = A
   ui A(ui);
   ui partial_period_A(ui);
};

ui sum(int*,int);
void empty_print(ui);


int main()
{
double time=clock();
ui M=100000000000ull;
ui sum=0;

for(int n=2;n<=10;n++)
    {
    Ulam U(2,2*n+1);
    
    U.determine_pre_period();
    U.determine_period();
    U.print_info();
    
    sum+=U.A(M);
    }

cout<<endl;
cout<<sum<<" in "<<(clock()-time)/1000<<" seconds"<<endl;
system("Pause");
return 0;
}


Ulam::Ulam (int k)
{
n=k;
h=4*(n+1);
U.push_back(2); U.push_back(2*n+1);
        
s.resize(h,0);
s[(U[0]+U[1])%h]=1;
}

Ulam::Ulam (int dummy, int k)
{
n=(k-1)/2;
h=4*(n+1);
U.push_back(2); U.push_back(2*n+1);
        
s.resize(h,0);
s[(U[0]+U[1])%h]=1;
}


void Ulam::determine_pre_period()
{
int i0=U.back();

while( i0<h+1 )
    {
    for(int i=U.back()+1;;i++) 
      {
      if(s[i%h ]==1)
        {
        s[i%h]=0;
        U.push_back(i);
        break;
        }
      s[i%h]=0;
      }
  
    i0=U.back();
    for(int j=0;j<U.size()-1;j++) s[(U[j]+i0)%h ]++;
    }
  
pre_period.length=U.size();
pre_period.sum=sum(&U[0],pre_period.length);
}

void Ulam::determine_period()
{
ui a=*(U.end()-1);
ui b=*(U.end()-2);

for(period.length=n+2, period.sum=0; a-b<h ; period.length++, period.sum+=a)
    {
    for(ui i=a+2;;i+=2)
        {
        if(s[i%h]==1)
           {
           b=a;
           a=i;
           break;
           }
        s[i%h]=0;
        }
   
    s[(2+a)%h]++;
    }

period.first_term=h+3;
period.sum+=(n+2)*(a+n+3);
period.difference=a-(1+2*n);
}


ui Ulam::A(ui k)
{
k-=pre_period.length;

ui q=k/period.length; // number of periods
k-=q*period.length;

ui a=period.difference*q+partial_period_A(k);

return a;
}

ui Ulam::partial_period_A(ui k)
{
ui a=*(U.end()-1);
ui b=*(U.end()-2);

for(int i=0;i<h;i++) s[i]=0;
for(int j=1;j<U.size()-2;j++) s[U[j]]++;
s[a%h]++;
s[(2+a)%h]++;

for(ui j=0; j<k ; j++ )
    {
    for(ui i=a+2;;i+=2)
        {
        if(s[i%h]==1)
           {
           b=a;
           a=i;
           break;
           }
        s[i%h]=0;
        }
   
    s[(2+a)%h]++;
    }

return a;
}


void Ulam::print_info() 
{
     cout<<"           U(2,"<<2*n+1<<")"<<endl;
     cout<<"* * * * * * * * * * * * * * *"<<endl;
     cout<<"*                           *"<<endl;
     cout<<"*   Non periodic part:      *"<<endl;
     cout<<"*    Length     : "<<pre_period.length; empty_print(pre_period.length);
     cout<<"*    Sum        : "<<pre_period.sum;    empty_print(pre_period.sum);
     cout<<"*                           *"<<endl;
     cout<<"*   Periodic part:          *"<<endl;
     cout<<"*    First Term : "<<period.first_term; empty_print(period.first_term);
     cout<<"*    Difference : "<<period.difference; empty_print(period.difference);
     cout<<"*    Length     : "<<period.length;     empty_print(period.length);
if( period.sum<1000000 ) {
     cout<<"*    Sum        : "<<period.sum;        empty_print(period.sum); }
     cout<<"*                           *"<<endl;
     cout<<"* * * * * * * * * * * * * * *"<<endl;
     cout<<endl;
     cout<<endl;
}


ui sum(int *U,int k)
{
int s=0;
for(int i=0;i<k;i++) s+=U[i];
return s;
}

void empty_print(ui k)
{
int x=10;

for(;k>0;k/=10) x--;

for(int i=0;i<x;i++) cout<<" ";
cout<<"*"<<endl;
}
