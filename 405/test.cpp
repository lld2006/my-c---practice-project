#include "../lib/tools.h"
#include <map>
#include <cstdlib>
class rectangle
{
    public:
    rectangle(int llx, int lly,int urx, int ury)
    {
        ll = IntPair(llx, lly);
        ur = IntPair(urx, ury);
    }
    public: 
        IntPair ll;
        IntPair ur;
};
void push(int x1, int y1, int x2, int y2, vector<rectangle>& vec)
{
    int len = x2 - x1;
    int width = y2 - y1;
    assert(len > 0); 
    assert(width > 0);
    assert(len == 2 * width || width == 2* len);
    vec.push_back(rectangle(x1, y1, x2, y2));
}
int main(int argc, char* argv[])
{
    vector<rectangle> vrec, vrec2;
    vrec.push_back(rectangle(0,0,1024, 512));
    int nmax = 10;
    if(argc == 2)
        nmax = atol(argv[1]);
    for( int i = 0; i < nmax; ++i){
        vrec2.clear();
        for(unsigned int j = 0; j < vrec.size(); ++j){
            rectangle& rec = vrec[j];
            IntPair ll = rec.ll;
            IntPair ur = rec.ur;
            int length = ur.first - ll.first;
            int width = ur.second - ll.second;
            if(length > width){
                int x1 = ll.first + length/4;
                int x2 = ll.first + length/4*3;
                int y1 = ll.second + width/2;
                push(ll.first, ll.second,x1, ur.second, vrec2);
                push(x1, ll.second, x2, y1, vrec2);
                push(x1, y1, x2, ur.second, vrec2);
                push(x2, ll.second, ur.first, ur.second, vrec2);
            }else{
                int x1 = ll.first + length/2;
                int y1 = ll.second + width/4;
                int y2 = ll.second + width/4*3;
                push(ll.first, ll.second, ur.first, y1, vrec2);
                push(ll.first, y1, x1, y2, vrec2);
                push(x1, y1, ur.first, y2, vrec2);
                push(ll.first, y2, ur.first, ur.second, vrec2);
            }
        }
        vrec.swap(vrec2);
        map<IntPair, int> points;
        int cnt = 0;
        for(unsigned int i = 0; i < vrec.size(); ++i){
            IntPair ll = vrec[i].ll;
            IntPair ur = vrec[i].ur;
            IntPair p3 = IntPair(ll.first, ur.second);
            IntPair p4 = IntPair(ur.first, ll.second);
            IntPairVec vp = {ll, ur, p3, p4};
            //printf("ll %d %d ur %d %d\n", ll.first, ll.second, ur.first, ur.second);
            for(unsigned int j = 0; j < vp.size(); ++j){
                //printf("inserting %d %d\n", vp[j].first, vp[j].second);
                auto iter = points.find(vp[j]);
                if(iter == points.end())
                    points.insert(pair<IntPair, int>(vp[j], 1));
                else{
                    iter->second++;
                    if(iter->second == 4){
                        ++cnt;
                        //printf("points %d %d\n",iter->first.first, iter->first.second );
                    }
                }
            }
        }
        for(auto iter = points.begin(); iter != points.end(); ++iter){
            //printf("map points %d %d cnt=%d\n", iter->first.first, iter->first.second, iter->second);
        }
        printf("size %zu %d\n", vrec.size(), cnt);
    }
}
