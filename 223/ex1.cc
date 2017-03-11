
#include <iostream>
using namespace std;
typedef long long LL;
#define L 25000000
int fac[L/3][7][2], fn[L/3];
bool b[L/3];
LL afac[14][2], an=0, A;
int cnt = (L-1)/2;
void getBC(LL depth, LL p){
    if(depth==an){
        LL q = (A-1)*(A+1)/p;
        if((p+q)%2==1) return;
        LL B = (-p+q)/2, C = (p+q)/2;
        if(A<=B && A+B+C<=L) cnt++;
    }
    else for(LL exp=0; exp<=afac[depth][1] && p<=A; exp++, p*=afac[depth][0]) getBC(depth+1, p);
}
int main(){
    for(LL i=2; i<L/3; i++) if(!b[i]){
        for(LL j=i; j<L/3; j+=i){
            int e=0;
            for(LL c=j; c%i==0; c/=i) e++;
            fac[j][fn[j]][0] = i, fac[j][fn[j]][1] = e;
            fn[j]++;
            b[j]=true;
        }
    }
    for(A=1; A<L/3-1; A++){
        an = 0;
        int start = 0;
        if(A%2==1){
            afac[0][0] = 2, afac[0][1] = fac[A-1][0][1] + fac[A+1][0][1];
            an = start = 1;
        }
        for(int i=start; i<fn[A-1]; i++, an++) 
            afac[an][0] = fac[A-1][i][0], afac[an][1] = fac[A-1][i][1];
        for(int i=start; i<fn[A+1]; i++, an++) 
            afac[an][0] = fac[A+1][i][0], afac[an][1] = fac[A+1][i][1];
        getBC(0,1);
    }
    cout << cnt;
}
