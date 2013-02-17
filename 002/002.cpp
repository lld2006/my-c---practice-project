#include <cstdio>
#include <cstdlib>
#include <vector>
using namespace std;
int main(int argc, char** argv)
{
    if(argc < 2){ 
        printf("please provide the limit required for this problem\n");
        exit(1);
    }
    int nmax = atoi(argv[1]);
    vector<int> vn;
    vn.resize(2);
    vn.reserve(200);
    vn[0] = 1;
    vn[1] = 1;
    int i = 1;
    int sum = 0.0;
    do{
        sum = vn[i] + vn[i-1];
        vn.push_back(sum);
        ++i;
    }while(sum <= nmax);
    sum = 0;
    for(unsigned int i = 1; i < vn.size();++i) {
        if((vn[i] & 1)==0 )
            sum += vn[i];
    }
    printf("%d\n", sum);
}
