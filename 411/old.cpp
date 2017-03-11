#include "../lib/tools.h"
#include <vector>
#include <algorithm>
//did not read the problem carefully, now need to redo it
//this will not work for large cases, since n*n needs too much memory
vector<vector<vector<int>>> grids; 
vector<i64> vpntcnts;
vector<IntPair> vpoints;
//vgridcnts is used for checking the number of maximum nodes within 
//grid range of (0, 0) to (x, y)
vector<vector<i64>> vgridcnts;
int ns = 1;
class pointLess
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

void processPointsInGrid(int x, int y)
{
    vector<int>& nodes = grids[x][y]; 

    //initialize the connection matrix
    vector<int>& nd2(nodes);
    //no need to sort, already sorted before
    //sort(nd2.begin(), nd2.end());
    //vp2 store the connection info inside this grid
    vector<int> vp2;
    vp2.resize(nd2.size(), 0);
    for(unsigned int i = 0; i < nd2.size(); ++i){
        int ni = nd2[i];
        IntPair& pi = vpoints[ni];
        for(unsigned int j = i+1; j < nd2.size(); ++j){
            int nj = nd2[j];
            IntPair& pj = vpoints[nj];
            if(pi.first <= pj.first && pi.second <=pj.second)
                vp2[j] = vp2[j]< vp2[i] + 1? vp2[i]+1:vp2[j];
        }
    }
    //see if it is better from a same-row(col) or from diagonal
    i64 nmax = 0;
    for(unsigned int i = 0; i < nd2.size(); ++i){
        i64 nt = -1;
        if(x > 0 && y > 0) //only in such kind of situation
            nt = vgridcnts[x-1][y-1];
            
        i64 vt = vp2[i]+1+nt;
        if(vpntcnts[nd2[i]] < vt){
            vpntcnts[nd2[i]] = vt;
        }
        if(nmax < vpntcnts[nd2[i]]) 
            nmax = vpntcnts[nd2[i]];
    }
    if(x > 0)
        nmax = std::max(nmax, vgridcnts[x-1][y]);
    if(y > 0)
        nmax = std::max(nmax, vgridcnts[x][y-1]);
    vgridcnts[x][y] = nmax;
}
void processPointsInSameRowcol(int x, int y)
{
    for(int yo = y + 1; yo <= ns; ++yo){
        vector<int>& vn0 = grids[x][y];
        vector<int>& vn1 = grids[x][yo];
        if(vn0.size() == 0 || vn1.size() == 0) continue;
        for(unsigned int i = 0; i< vn0.size(); ++i){
            for(unsigned int j = 0; j < vn1.size(); ++j){
                int ni=vn0[i];
                int nj=vn1[j];
                IntPair& pi = vpoints[ni];
                IntPair& pj = vpoints[nj];
                assert(pi.second < pj.second);
                if(pi.first <= pj.first && vpntcnts[ni]+1> vpntcnts[nj])
                    vpntcnts[nj] = vpntcnts[ni]+1;
            }
        }
    }
    for(int xo = x+1; xo <= ns; ++xo){
        vector<int>& vn0 = grids[x][y];
        vector<int>& vn1 = grids[xo][y];
        if(vn0.size() == 0 || vn1.size() == 0) continue;
        for(unsigned int i = 0; i< vn0.size(); ++i){
            for(unsigned int j = 0; j < vn1.size(); ++j){
                int ni=vn0[i];
                int nj=vn1[j];
                IntPair& pi = vpoints[ni];
                IntPair& pj = vpoints[nj];
                assert(pi.first < pj.first);
                if(pi.second <= pj.second && vpntcnts[ni]+1> vpntcnts[nj])
                    vpntcnts[nj] = vpntcnts[ni]+1;
            }
        }
    }
}
i64 upHillPath(int n)
{
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
    
    sort(vpoints.begin(), vpoints.end(), pointLess());
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
    //now put all the points into grids
    i64 unit = val / ns;
    grids.clear();
    grids.resize(ns+1);
    for(unsigned int i = 0; i< grids.size(); ++i)
        grids[i].resize(ns+1);
    for(unsigned int i = 0; i<vpoints.size(); ++i){
        int x = vpoints[i].first;
        int y = vpoints[i].second;
        x/=unit;  if(x > ns) x = ns;//if any points is on the boundary, put in ns
        y/=unit;  if(y > ns) y = ns;
        grids[x][y].push_back(i);
    }

    vpntcnts.clear();
    vpntcnts.resize(vpoints.size(), 0);

    vgridcnts.clear();
    vgridcnts.resize(ns+1);
    for(unsigned int i = 0; i < vgridcnts.size(); ++i)
        vgridcnts[i].resize(ns+1, 1LL); 
    //lower half
    //ns is number of segments, grid in each dimension
    for(int xy = 0; xy <= ns; ++xy){
        for(int x = 0; x<=xy; ++x){
            int y = xy -x;
            //0, handle grids that are in the upright corner
            //which do not need a point-to-point hand shake
            //processGridToGrid(x, y);
            //1, process the points in the grid
            processPointsInGrid(x,y);
            processPointsInSameRowcol(x, y);
        }
    }
    for(int xy = ns+1; xy<=2*ns;++xy){
        for(int xs =1; xs<=ns; ++xs){
            int x = ns+1-xs;
            int y = xy - x;
            if(y > ns) break; 
            processPointsInGrid(x, y);
            processPointsInSameRowcol(x, y);
        }
    }

    printf("number of points is %lld(%lld) cnt=%lld\n",val,(i64)vpoints.size(), vpntcnts.back()-1);
    return vpntcnts.back()-1;
}
int main(int argc, char* argv[])
{
    i64 sum = 0;
    if(argc == 3)
        ns = atol(argv[2]);
    if(argc >=2 )
        sum = upHillPath(atol(argv[1]));
    else
    for(int i = 1; i<= 10000; ++i){
        int val = i*i*i*i*i;
        val = i;
        sum += upHillPath(val);
        printf("%d %lld\n", i, sum);
    }
}
