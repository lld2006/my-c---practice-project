#include <vector>
#include <math.h>
#include <time.h>
#include <cstdio>
using namespace std;

// This program can find how many squarefree numbers are there below LIMIT
const long long int LIMIT =(long long int)1<<50; // 2^50

int primesize;
vector<int> prime;
vector<int> small_prime;
vector<char> sieve_table;

long long int count;

void Prime_Sieve(int);
void inclusion_exclusion(long long int, int, int);

int main(int argc, char* argv[])
{
    double time=clock();
    Prime_Sieve(sqrt(LIMIT));
    printf("Time = %.3f seconds\n\n", (clock()-time)/CLOCKS_PER_SEC);
    long long int upper_bound=LIMIT-1; // There are LIMT-1 numbers < LIMIT
    inclusion_exclusion(upper_bound, 0, 1);
    count=upper_bound-count;
    printf("count = %lld\n\n", count);
    return 0;
}

void inclusion_exclusion(long long int upper_bound, int nth, int level)
{
    long long int nextub;
    for(int i=nth;i<primesize;i++)
    {
        nextub=upper_bound/((long long int)prime[i]*prime[i]);
        if(nextub==0) break;

        count=(level & 0x01) ? count+nextub : count-nextub;

        if(nextub>=(long long int)prime[i+1]*prime[i+1]) {
            inclusion_exclusion(nextub, i+1, level+1);
        }
    }
}

void Prime_Sieve(int limit)
{
    int i, j, k, n=0;
    int segment=sqrt(limit);
    if(segment*segment!=limit)
    {
        segment++;
    }
    sieve_table.assign(segment, 0);    
    for(i=2;i<=segment;i++)
    {
        if(!sieve_table[i-1])
        {
            small_prime.push_back(i);
            prime.push_back(i);
            for(j=i+i;j<=segment;j=j+i)
            {
                sieve_table[j-1]=1;
            }
        }
    }
    int num=(limit%segment) ? limit/segment+1 : limit/segment;
    bool isRemainder=(limit%segment) ? true : false;

    int head, tail, start, end;
    for(i=1;i<num;i++)
    {
        for(j=0;j<segment;j++)
        {
            sieve_table[j]=0;
        }
        head=i*segment+1;
        tail= (isRemainder && i==num-1) ? limit : tail=(i+1)*segment;
        for(j=1;j<small_prime.size();j++)
        {
            int sp=small_prime[j];
            start=(head/sp)*sp;
            if(start < head) start+=sp;
            for(k=start;k<=tail;k=k+sp)
            {
                sieve_table[k-head]=1;
            }
        }
        end=tail-head;
        int s=(head & 1) ? 0: 1;
        for(j=s;j<=end;j=j+2)
        {
            if(sieve_table[j]==0)
            {
                prime.push_back(j+head);
            }
        }
    }
    primesize=prime.size();
}
/*
count = 684465067343069

Time = 1.781 seconds
*/
