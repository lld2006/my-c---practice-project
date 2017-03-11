#include <iostream> 
#include <cmath>
using namespace std; 
void xgcd(const int p, const int q, int& gcd, int& pcoeff, int& qcoeff)
{ int a[3]; a[0] = 1; a[1] = 0; a[2] = p; 
   int b[3]; b[0] = 0; b[1] = -1; b[2] = q; 
   while (a[2] != 0){ 
       int k = b[2]/a[2]; 
       b[0] -= k * a[0]; 
       b[1] -= k*a[1]; 
       b[2] -= k*a[2]; 
       if (b[2] == 0){ 
           b[0] = a[0]; a[0] = 0; b[1] = a[1]; a[1] = 0; b[2] = a[2]; a[2] = 0; 
       } else { 
           int k = a[2]/b[2]; a[0] -= k*b[0]; a[1] -= k*b[1]; a[2] -= k*b[2]; 
       } 
   } 
   gcd = b[2]; pcoeff = b[0]; qcoeff = b[1]; 
} 

int g(int n, int q, int r){ 
    int gcd; int coeff8r; int coeffqq; 
    int qsq = q*q; 
    xgcd(8*r,qsq,gcd,coeff8r,coeffqq); 
    if (gcd != 1) return 0; 
    int k = (coeffqq*3) / (8*r); 
    int p = coeff8r*3 - k*qsq; 
    int s = coeffqq*3 - k*8*r; 
    if (s < 0){ p += qsq; s += 8*r; } 
    long long lwr = ((long long)p)*q+((long long)s)*r*r+((long long)p)*3*r; 
    if (lwr > n+1) return 0; 
    long long stp = ((long long)q) * q * (q + (3*r)) + ((long long) r) * r * r * 8; 
    if (lwr+stp > n+1) 
        return 1; 
    return 1+(((n+1)-lwr)/stp); 
} 
//How it works: Let x be the cube root of a-b√c and y be the cube root of a+b√c. 
//Then 2a=x3+y3=(x+y)3-3xy(x+y). Thus if x+y=1, then 2a=1-3xy, so xy=(1-2a)/3. 
//However, (xy)3=a2-b2c. Thus if a,b,c are a Cardano Triplet, then (1-2a)3=27(a2-cb2). 
//Since the right hand side is a multiple of 3, the left hand side must also be a 
//multiple of 3. Thus 1-2a must be a multiple of 3, and so a must be of the form 
//3x+2. Then cb^2-a^2=((2a-1)/3)3=(2x+1)^3. Thus cb^2=(2x+1)^3+(3x+2)^2=
//8x^3+21x^2+18x+5=(x+1)^2(8x+5). 
//Now let p be the greatest common divisor of x+1 and b. Then write b=pr and x+1=pq. 
//Then dividing p2 form both sides, cr2=q2(8x+5). Since q and r are coprime, 
//there must be an integer s such that 8x+5=sr^2, and c=sq^2. Thus, we have b=pr, 
//c=sq^2, x+1=pq and 8x+5=sr^2. This shows that a,b,c are a Cardano Triplet iff 
//a,b,c can be written as a=3pq-1, b=pr, c=sq2 where p,q,r,s are positive numbers 
//for which q and r are coprime and 8pq=sr^2+3. Thus we are trying to enumerate 
//the numbers p,q,r,s>0 with q and r coprime, with: 8pq = sr2+3 and 3pq+pr+sq2 <= 10^8 + 1. 
//We then count these solutions by pairs (q,r). For all such pairs, r is odd and q is 
//coprime to r. Given q and r with r odd and q coprime to r, let P and S be the lowest 
//positive solution to 8Pq=Sr2+3. Then all solutions in (p,s) are of the form p=P+r^2k, 
//s=S+8qk. Then we want to find how many k>=0 have 3pq+pr+sq^2=P(3q+r)+Sq^2+k(r^2(3q+r)+8q^3) 
//<= 10^8 + 1.
int f(int n)
{ 
    int pr = (n+1)/3; 
    int uprQ = sqrt(((((long long)pr)*8)-3) / 5); 
    int uprR = sqrt((n+1) / 5); //assume s>= 5
    int tot = 0; 
    int q = 1; 
    while (q <= uprQ){ 
        int r = 1; 
        while (r <= uprR){ 
            tot += g(n,q,r); 
            r += 1; 
        } 
        q += 2; 
    } 
    return tot; 
} 
int main()
{ 
    cout << "Answer = " << f(110000000) << endl; 
}
