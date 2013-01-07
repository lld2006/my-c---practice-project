#include <cstdio>
#include <cmath>
#include <cassert>
#include "../lib/typedef.h"
//let me try this, since we are only concerned about the expectation
//to some extent of accuracy, and in each region, the value are monotonus
//let us try to find where the difference comes from. This should be
//the key point
i64 iroot = 7000000;
int findRoot(i64 n)
{
    i64 root = iroot;
    i64 quote = n/root;
    if(quote*root != n)
        ++quote;
    i64 newroot = (quote+root)/2;
    int cnt = 1;
    while(newroot != root){
        ++cnt;
        root = newroot;
        quote = n/newroot;
        if(quote*root != n) 
            ++quote;
        newroot = (root+quote)/2;
    }
    return cnt;
}
i64 binary_search(i64 nstart, i64 nend, int iters, int itere)
{
    i64 ne;
    int iterm;
    while(nend-nstart > 1){
        ne = (nstart+nend)/2;
        iterm = findRoot(ne);
        assert(iterm== iters||iterm==itere);
        if(iterm==iters)
            nstart = ne;
        else
            nend = ne;
    }
    return nstart;
}
i64 find_iterations_in_region(i64 n)
{
    i64 nstart = n*(n-1)+1;
    i64 nend = n*(n+1);
    i64 nstart0 = nstart;
    i64 ne = 0; 
    int iters = findRoot(nstart);
    int itere = findRoot(nend);
    int iterm;
    assert(itere-iters>=0);
    if(itere==iters){
        return (nend-nstart+1)*iters;
    }else if(itere-iters>1){
        assert(itere-iters==2); 
        bool notFound = true;
        while(notFound){
            ne = (nstart+nend)/2;
            iterm = findRoot(ne);
            if(iterm == iters+1){
                i64 ms = binary_search(nstart, ne, iters, iterm)+1;
                i64 me = binary_search(ne, nend, iterm, itere);
                return (ms-nstart0)*iters+(me-ms+1)*(iters+1) + (nend-me)*itere;
            }else{
                if(iterm == iters){
                    nstart = ne;
                }else{
                    assert(iterm == itere);
                    nend = ne;
                }
            }
        }
    }else{
        i64 ns = binary_search(nstart, nend, iters, itere);
        return (ns-nstart+1) * iters + (nend-ns)*itere;
    }
    assert(0);
    return 0;
}
int main()
{
   i64 total = 0;
   i64 start = sqrt(1e13)+2;
   i64 final = 10000000;
   //two boundaries
   i64 s1 = 10000000000000LL;
   i64 e1 = start*(start-1);
   int it1 = findRoot(s1);
   int it2 = findRoot(e1);
   assert(it2 -it1 <=1);
   if(it2 ==it1){
        total += it1*(e1-s1+1);
   }else{
       i64 ns =  binary_search(s1, e1, it1, it2);
       total += (ns-s1+1)*it1 +(e1-ns)*it2;
   }
   s1 = final*(final-1)+1;
   e1 = 100000000000000LL-1;
   it1 = findRoot(s1);
   it2 = findRoot(e1);
   assert(it2 -it1 <=1);
   if(it2 ==it1){
        total += it1*(e1-s1+1);
   }else{
       i64 ns =  binary_search(s1, e1, it1, it2);
       total += (ns-s1+1)*it1 +(e1-ns)*it2;
   }
   for(unsigned int i = start; i<final;++i){
       total += find_iterations_in_region(i);
   }
   printf("%30.15f\n", (double)total/(9LL*10000000000000LL));
}
