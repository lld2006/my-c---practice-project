//basically, it is asking if 5 is a quadratic residue for p
#include "../lib/tools.h"
bool primitive_root_for_prime(int value, int prime, const vector<int>& vfac)
{
    //first get all factors of p-1
    vector<int> factors;
    int num = prime - 1;
    while(num > 1){
        int nfac = vfac[num];
        factors.push_back(nfac);
        while(vfac[num] == nfac) num/= nfac;
    }
    for(int ni = value; ni <= value; ++ni){
        bool is_primitive = true;
        for(unsigned int i = 0; i < factors.size(); ++i){
            int nmod = powermodule(ni, (prime-1)/factors[i], prime);
            if(nmod == 1){
                is_primitive = false;
                break;
            }
        }
        if(is_primitive)
            return is_primitive;
    }
    return 0;
}
int main()
{
    vector<int> vprimes;
    vector<int> vfac;
    int nmax = 100000000;
    primeWithin(vprimes, nmax);
    factor_table_min(nmax, vfac);
    printf("factor done\n");
    i64 sum = 5;
    int cnt = 1;
    for(unsigned int i = 3; i < vprimes.size(); ++i){
        int np = vprimes[i];          
        int tp = np % 5;
        if(tp == 1 || tp ==4){
            i64 sol = 0;
            bool ret = tonelli_shank(np, 5, sol);
            assert(ret);
            i64 tsol = sol;
            if(sol %2 == 0) 
                sol = (sol + np + 1)/2;
            else
                sol = (sol+1)/2;
            if(primitive_root_for_prime(sol, np, vfac)){
                sum += np;
                ++cnt;
                //printf("%d\n", np);
            }else{
                sol = np - tsol;
                if(sol %2 == 0) 
                    sol = (sol + np + 1)/2;
                else
                    sol = (sol+1)/2;
                if(primitive_root_for_prime(sol, np, vfac)){
                    sum += np;
                    ++cnt;
                    //printf("%d\n", np);
                }
            }
        }
    }
    printf("%d %lld\n",cnt, sum);
}
