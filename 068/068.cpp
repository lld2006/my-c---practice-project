#include <cstdio>
#include <vector>
using namespace std;

void search_ring(vector<int>& inner, vector<int>& outer, vector<int>& flag, int cpos, int value)
{
    if(cpos == 4){
        int nleft = value - inner[0] -inner[4];
        if(flag[nleft]) return;
        if(nleft < inner[0] || nleft > 10) return;
        outer[4] = nleft;
        for(unsigned int i = 0; i < 5; ++i){
            int next  = i + 1;
            next %= 5;
            printf("%d%d%d", outer[i], inner[i], inner[next]);
        }
        printf("\n");
        return;
    }
    if(cpos == 0) {
        //initialization
        for( int i = 1; i < 7; ++i){
            flag[i] = 1;
            outer[0] = i;
            for(int j = 1; j<10; ++j){//inner can not be 10 , otherwise it is 17 digit
                if(i == j ) continue;
                int nleft = value - i - j;
                if(nleft == i || nleft == j) continue;
                if(nleft < 1 || nleft >= 10) continue;
                flag[j] = 1; 
                flag[nleft] = 1;

                inner[0] = j;
                inner[1] = nleft;

                search_ring(inner, outer, flag, cpos+1, value);
                flag[j] = 0;
                flag[nleft] = 0;
            }
            flag[i] = 0;
        }
    }else{
        for(int i = outer[0]+1; i <= 10; ++i){
            if(flag[i]) continue;
            int nleft = value - inner[cpos] - i;
            if(nleft <= 0 || nleft >= 10) continue;
            if(nleft == i) continue;
            if(flag[nleft]) continue;
            outer[cpos] = i;
            inner[cpos+1] = nleft;
            flag[i] = 1;
            flag[nleft] = 1;
            search_ring(inner, outer, flag, cpos+1, value);
            flag[i] = 0;
            flag[nleft] = 0;
        }
    }
}
int main(int argc, const char *argv[])
{
    vector<int> inner, outer, flag;
    inner.resize(5, -1);
    outer.resize(5, -1);
    flag.resize(11, 0);
    for(unsigned int value = 14; value<=27; ++value)
        search_ring(inner, outer, flag, 0, value);
    return 0;
}
