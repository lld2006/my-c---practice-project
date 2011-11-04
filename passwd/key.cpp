#include <cstdio>
#include <string>
#include <vector>
#include <set>

using namespace std;
int main()
{
    char str[128];
    FILE* fp;
    vector<set<int> > vsetpost;
    vector<set<int> > vsetpre;
    vsetpost.resize(10);
    vsetpre.resize(10);
    fp = fopen("keylog.txt", "r");
    while(fscanf(fp, "%s", str) == 1){
       int i1 = str[0]-'0';
       int i2 = str[1]-'0';
       int i3 = str[2]-'0'; 
       printf("%d%d%d\n", i1, i2, i3);
       vsetpost[i1].insert(i2);
       vsetpost[i1].insert(i3);

       vsetpost[i2].insert(i3);
       vsetpre[i2].insert(i1);

       vsetpre[i3].insert(i1);
       vsetpre[i3].insert(i2);
    }
        bool found = true;
        while(found){
            found = false;
            for(unsigned int i = 0; i <= 9; ++i){
                if(vsetpre[i].size()==0 && vsetpost[i].size()>0){
                    printf("%d is the current first\n",i );
                    found = true;
                    for(set<int>::iterator iter = vsetpost[i].begin(); iter != vsetpost[i].end();++iter){
                        vsetpre[*iter].erase(i);
                    }
                    vsetpost[i].clear();
                }
                if(vsetpost[i].size()==0 && vsetpre[i].size() > 0){
                    printf("%d is the current last\n", i);
                    found = true;
                    for(set<int>::iterator iter = vsetpre[i].begin(); iter != vsetpre[i].end(); ++iter){
                        vsetpost[*iter].erase(i);
                    }
                    vsetpre[i].clear();
                }
            }
    }
}
