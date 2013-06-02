#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

typedef struct rr {
    int p, q;
} rr;

/* For input of 1053779 stack size goes up to 1910, make sure you enlarge it for bigger inputs.
 * Stack high watermark seems to grow as the square root of the input.
 */
//this does not give correct result for rmax = 1e7, strange

#define MAX_STACK 400000
rr stack[MAX_STACK];
int last = 0;
void push(int p, int q) { stack[last].p = p; stack[last].q = q; ++last; }
void pop() { --last; }
rr* front() { return stack + last - 1; }
int empty() { return 0 == last; }

int main(int ac, char** av) {
    double Rd, Ru;
    rr* f;
    int n=1, m=1, N=1, M=0, m_, n_;
    long MN, cnt = 0;
    double start = clock();
    //double r = atoi(av[1]);
    double r = 1053779;
    r = 50;
    Rd = 2.0*r/sqrt(3.0d);
    Ru = 2.0*r*sqrt(3.0d);

    push(N, M);
    while (!empty()) {
        f = front();
        N = f->p; M = f->q;
        n_ = n + N; m_ = m + M;
        MN = m_*n_;
        if (MN <= Ru) {
            push(n_, m_);
            cnt += n_%3 != m_%3 ? Rd/MN : Ru/MN;
            continue;
        }
        n = N; m = M;
        pop();
    }

    printf("got %ld in %.3gs\n", cnt, (clock() - start)/CLOCKS_PER_SEC);
    return 0;
}
