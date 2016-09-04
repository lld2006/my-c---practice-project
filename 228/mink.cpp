#include "../lib/rational.h"
#include <algorithm>
#include <cstdio>
#include <set>
//vector<rational> create_polar_vector(int n)
//{
//    vector<rational> vpolar;
//    vpolar.reserve(n);
//    int n0 = n/4;
//    for(int i = -n0; i<n-n0; ++i){
//       vpolar.push_back(rational(90)+rational(i*180,n));
//    }
//    return vpolar;
//}
//int main()
//{
//    vector<rational> result, newresult;
//    for(int i = 1864; i<=1909; ++i){
//        newresult.clear();
//        vector<rational> vnr=create_polar_vector(i);
//        set_union(result.begin(), result.end(), vnr.begin(), vnr.end(), 
//                back_inserter(newresult));
//        swap(result, newresult);
//    }
//    printf("%d\n", static_cast<int>(result.size()));
//}
int main()
{
    set<rational> vr;
    for(unsigned int i = 1864; i<=1909; ++i){
        for(int j = 0; j < i; ++j){
            vr.insert(rational(j, i));
        }
    }
    printf("my test %zu\n", vr.size());
}
