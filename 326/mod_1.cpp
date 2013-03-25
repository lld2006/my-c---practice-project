#include <vector>
#include <cstdio>
#include <cassert>
#include "../lib/typedef.h"
#include "../lib/tools.h"
i64 range = 10000;
i64 sum = 1000;
//lesson #1, in the function compute_solution, I need negative solutions,
//lesson #2, the problem asks to start from 1, I started from 0, this may
//lesson #3, ax+by=gab is derived from extended euclidian, if ax+by= gab*c, then
//multiply the solution by c; BUT, the difference between solutions is still the 
//same!!!
//lesson #4, for two consecutive segs, the second one should be n+1 not n!!!
//
//introduce a lot of fake solutions, for example 0, 0. I need to change form 1
//but my function want to solve in the positive side;
//by + ax = c, y must be >= 0
//so x should be negative
i64 compute_solutions(i64 a, i64 b, i64 c, i64 rmax)
{
    assert(a > 0 && b > 0 && c>= 0);
    i64 xmin;
    if(c == 0){
        i64 gab = gcd(a, b);
        xmin = 0;
        if(xmin > rmax) return 0;
        else
            return (rmax-xmin)*gab/b + 1;
    }
    i64 x, y, gab;
    //extended euclid function solve ax+by=gab
    extended_euclid(a, b, x, y, gab);
    if(c % gab)
        return 0;
    // the key point here is the solution are spaced by
    // a', currently notated as a
    x *= (c/gab);//this is the real solution
    i64 q = x*gab/b;
    xmin = x - q*b/gab;
    if(xmin > 0)
        xmin -= b/gab;
    if(xmin +rmax < 0) return 0;
    return (rmax+xmin)*gab/b+1;
}
int main()
{
    vector<vector<int>> v6n;
    vector<vector<int>> v6r;
    v6r.resize(7);
    v6n.resize(7);
    v6n[1] = {-1,4,7,8,14,15,18};
    v6r[1] = {-1,1,2,2,5,5,8};
    v6n[2] = {-1,-1,3,4,10,11,14};
    v6r[2] = {-1,-1,1,1,4,4,7};
    v6n[3] = {-1,-1,-1,1,7,8,11};
    v6r[3] = {-1,-1,-1,0,3,3,6};
    v6n[4] = {-1,-1,-1,-1,6,7,10};
    v6r[4] = {-1,-1,-1,-1,3,3,6};
    v6n[5] = {-1,-1,-1,-1,-1,1,4};
    v6r[5] = {-1,-1,-1,-1,-1,0,3};
    v6n[6] = {-1,-1,-1,-1,-1,-1,3};
    v6r[6] = {-1,-1,-1,-1,-1,-1,3};
    //first consider one segment
    i64 total = 0;
    for(unsigned int start = 1; start < 7; ++start)
        for(unsigned int end = start; end < 7; ++end){
            i64 xmax = (range- end)/6;
            int tp= compute_solutions(v6n[start][end], sum, v6r[start][end],xmax );
            total += tp;
            if(tp)
                printf("%d %d %d\n",start, end, tp);
        }
    //now let us consider two segments;
    //this means two consecutive segments
    printf("phase 1 %lld\n", total);
    for(unsigned int start = 1; start <= 6; ++start)
        for(unsigned int end = 1; end <= 6; ++end){
            i64 xmax = (range - end)/6-1;
            int tp = compute_solutions(v6n[start][6]+v6n[1][end], sum, v6r[start][6] + v6r[1][end]+v6n[1][end], xmax);
            total += tp;
            if(tp)
                printf("%d %d %d\n",start, end, tp);
        }
    printf("phase 2 %lld\n", total);
    //now it is time to consider there are m whole pieces 
    i64 mmax = (range-2)/6+1;
    for(unsigned int m = 2; m <=mmax ; ++m){
        //one of the key in this problem, consider modulo
        for(unsigned int start = 1; start <= 6; ++start){
            for(unsigned int end = 1; end <= 6; ++end){
                i64 xmax = (range - end)/6-m;
                int tp = compute_solutions(v6n[start][6]+v6n[1][end]+18*(m-1),
                        sum, v6r[start][6] + v6r[1][end]+(9*m+8)*(m-1)+v6n[1][end]*m, xmax);
                total += tp;
                if(tp)
                    printf("%d %d %d %d\n",start, end, tp, m);
            }
        }
    }
    printf("phase 3 %lld\n", total);
}
