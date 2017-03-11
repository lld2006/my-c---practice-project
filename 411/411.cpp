#include "../lib/tools.h"
#include <vector>
#include <list>
#include <algorithm>
#include <set>
using namespace std;
//1, did not read the problem carefully, now need to redo it
//2, duplicate complicated code makes a lot of trouble
//3, keep a valid intermediate result instead of some mistakes to be
//   cleaned later on, it is hard to figure out what happens in between
//4, sigh, if keep everything clean, it is slow for 16 because there 
//   are so many numbers to be iterated!!!!
vector<IntPair> vpoints;
class pointRowLess
{
    public:
        bool operator()(const IntPair& p1, const IntPair& p2)
        {
            if(p1.first < p2.first) return true;
            if((p1.first == p2.first )&&(p1.second < p2. second) )
                return true;
            return false;
        }
};
class pointColLess
{
    public:
        bool operator()(const IntPair& p1, const IntPair& p2)
        {
            if(p1.second < p2.second) return true;
            if((p1.second == p2.second)&&(p1.first < p2.first) )
                return true;
            return false;
        }
};

//for row and col vector
void fastForward(int n, vector<IntPair>::iterator& it, bool isRow)
{
        if(isRow && it->first > n){
            return;
            assert(it->first == n );
        }else if( !isRow && it->second >n){
            return;
            assert(it->second == n );
        }
        if(isRow)
            while(it->second < n ) ++it;
        else
            while(it->first < n ) ++it;
}

int indexxy(IntPairVec::iterator& it)
{
    return it->first;
}

int valuexy(IntPairVec::iterator& it)
{
    return it->second;
}

int xrcvec(IntPairVec::iterator& it)
{
    return it->first;
}

int yrcvec(IntPairVec::iterator& it)
{
    return it->second;
}

void printList(int nx, const list<IntPair>& l)
{
    printf(" size=%d =====\n", (int)l.size());
    int count = 0;
    for(auto iter = l.begin(); iter != l.end(); ++iter)
        printf("%d (%d %d) %d\n", count++, nx, iter->first, iter->second);
}

i64 upHillPath(int n)
{
    int debug = true;
    debug = false;
    i64 val =  n ;
    vpoints.clear();
    vpoints.reserve(2*val+1);
    int x = 1, y = 1;
    for(int i = 0; i <= 2*val; ++i ){
        vpoints.push_back(IntPair(x,y));
        x *= 2; x %= val;
        y *= 3; y %= val; //the first version of here is using
        //power module, which is too costly for large number of points
    }
    //remove duplicate points
    unsigned int nwrite, nread;
    nwrite = nread = 1;
    //start point and destination must be added
    vpoints.push_back(IntPair(0, 0));
    vpoints.push_back(IntPair(val, val));
    set<IntPair, pointRowLess> pset(vpoints.begin(), vpoints.end());
    sort(vpoints.begin(), vpoints.end(), pointRowLess());
    for( nread= 1; nread< vpoints.size(); ++nread){
        if(vpoints[nread] == vpoints[nread - 1])
            continue;
        else{
           if (nwrite < nread)
                vpoints[nwrite] = vpoints[nread];
           ++nwrite;
        }
    }
    vpoints.resize(nwrite);
    assert(pset.size() == nwrite);
    pset.clear();
    //row by row and col by col
    vector<IntPair>& vprow = vpoints;
    vector<IntPair> vpcol(vpoints);
    sort(vpcol.begin(), vpcol.end(), pointColLess());
    if(debug){
        printf("row\n");
        for(unsigned int i = 0; i<vprow.size(); ++i)
            printf("%d %d\n", vprow[i].first, vprow[i].second);
        printf("col\n");
        for(unsigned int i = 0; i<vpcol.size(); ++i)
            printf("%d %d\n", vpcol[i].first, vpcol[i].second);
    }
    list<IntPair> vxmax, vymax;
    vector<IntPair>::iterator itrow = vprow.begin();
    vector<IntPair>::iterator itcol = vpcol.begin();
    list<IntPair>::iterator itx, ity, itt;
    //init the 0th row and 0th col 
    int nt = 0;
    for(;itrow->first == 0; ++itrow)
        vxmax.push_back(IntPair(itrow->second, nt++));
    nt = 0;
    for(;itcol->second == 0; ++itcol)
        vymax.push_back(IntPair(itcol->first, nt++));

    for(int nx = 1; nx <= n; ++nx){
        int mt = 0;
        if(debug){
            printf("===== vx nx=%d ", nx);
            printList(nx-1, vxmax);
            printf("===== vy nx=%d ", nx);
            printList(nx-1, vymax);
        }
        //remove the void old value
        //cannot find a reason that the list is empty
        assert(!vxmax.empty() && vxmax.begin()->first == nx - 1);
        itx = vxmax.begin();
        mt = itx->second; //initial mt
        ++itx;
        if(itx == vxmax.end() || itx->first > nx){
            vxmax.begin()->first = nx; //reduce the vector size by 1
        }else{
            assert(itx->first == nx);
            if(itx->second< mt) itx->second = mt;
            vxmax.pop_front();
        }
        assert(!vymax.empty() && vymax.begin()->first == nx-1 );
        ity = vymax.begin();
        mt = ity->second;
        ++ity;
        if(ity == vymax.end() || ity->first > nx){
            vymax.begin()->first = nx;
        }else{
            assert(ity->first == nx);
            if(ity->second< mt) ity->second = mt;
            vymax.pop_front();
        }
        assert(vxmax.begin()->first == nx);
        assert(vymax.begin()->first == nx);
        int nmax = std::max(vxmax.begin()->second, vymax.begin()->second);
        vxmax.begin()->second = nmax;
        vymax.begin()->second = nmax;
        itx = vxmax.begin();
        assert(!vxmax.empty() && itx->first==nx); 
        fastForward(nx, itrow,true);
        //corner in the xy plane
        //row along y direction, change in y, first fixed
        itt = itx;
        mt = itt->second; //previous valid value
        for( ; itrow != vprow.end() && itrow->first == nx; ++itrow ){
            assert(itrow->second >= itx->first);
            //remove invalid values, as going along the way
            while(itt != vxmax.end() && itt->first < itrow->second){
                if(itt == vxmax.begin()){ //this must be kept 
                    assert(itt->second == mt);//otherwise this need to be updated
                    ++itt;
                }else if(itt->second <= mt)
                    itt = vxmax.erase(itt); //erase the invalid value
                    //and move to the next position
                else{
                    mt = itt->second;
                    ++itt;
                }
            }
            if(itt == vxmax.end() || itrow->second < itt->first){
                vxmax.insert(itt, IntPair(itrow->second, ++mt));
            }else{
                //previous row has a value
                assert(itt->first == itrow->second);
                if(itt->second < mt){
                    itt->second = ++mt;
                    ++itt;//itt has been handled, need to be incremented
                }else{
                    ++(itt->second);
                    mt = itt->second;
                    ++itt;
                }
            }
        }
        //col along x direction change in x, second fixed
        ity = vymax.begin();
        assert(!vymax.empty() && ity->first==nx); 
        fastForward(nx, itcol, false);
        itt = ity;
        mt = itt->second; //previous valid value
        for( ; itcol != vpcol.end() && itcol->second == nx; ++itcol){
            assert(itcol ->first >= ity->first);
            //remove invalid values, as going along the way
            while(itt != vymax.end() && itt->first < itcol->first){
                if(itt == vymax.begin()){
                    assert(itt->second == mt);//otherwise this need to be updated
                    ++itt;
                }else if(itt->second <= mt) //!!!!<= is too aggressive
                    itt = vymax.erase(itt);
                else{
                    mt = itt->second;
                    ++itt;
                }
            }
            if(itt == vymax.end() || itcol->first < itt->first)
                vymax.insert(itt, IntPair(itcol->first, ++mt));
            else{
                //previous col has a value
                assert(itt->first == itcol->first);
                if(itt->second <= mt){
                    itt->second = ++mt;
                    ++itt;
                }else{
                    ++(itt->second);
                    mt=itt->second; 
                    ++itt;
                }
            }
        }
    }
    printf("number of points is %lld(%lld) cnt=%d\n",val,(i64)vpoints.size(), vxmax.begin()->second-1);
    return vxmax.begin()->second-1;
}
int main(int argc, char* argv[])
{
    i64 sum = 0;
    if(argc >=2 )
        sum = upHillPath(atol(argv[1]));
    else
    for(int i = 1; i<= 30; ++i){
        int val = i*i*i*i*i;
        //val = i;
        sum += upHillPath(val);
        printf("%d %lld\n", i, sum);
    }
}
