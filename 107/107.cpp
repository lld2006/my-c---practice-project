#include "../lib/typedef.h"
#include <cstdio>
#include <queue>
#include <limits>
using namespace std;

class keymore
{
public:
    bool operator() (const pair<int, int>& p1, const pair<int, int>& p2)
        {return p1.first > p2.first;}
};

int main()
{
    FILE* fp;
    fp=fopen("network.txt", "r");
    int ni;
    vector<int> edge;
    //read edge data
    int dim = 40;
    int total0 = 0;
    while(fscanf(fp, "%d", &ni)==1){
        if(ni==-1){
            edge.push_back(numeric_limits<int>::max());
        }else{
            edge.push_back(ni);
            total0 += ni;
        }
    }
    //stl is using max_heap, so less can not be used
    //first is the cost and second is node index;
    priority_queue<IntPair, IntPairVec, keymore> pq;
    vector<int> visited;
    vector<int> vcost;
    visited.resize(dim, 0);
    vcost.resize(dim, numeric_limits<int>::max());
    vcost[0] = 0;
    pq.push(IntPair(0, 0));
    int total = 0;
    while(!pq.empty()){
        const IntPair& px = pq.top();
        int cost = px.first;
        int node = px.second;
        pq.pop();
        if(visited[node])
            continue;
        total += cost;
        visited[node] = 1;
        for( int i = 0; i < dim; ++i){
            if(visited[i]) continue;
            int tcost = edge[node*dim+i];
            if( tcost == numeric_limits<int>::max())
                continue;
            if(tcost < vcost[i]){
                vcost[node] = tcost;
                pq.push(IntPair(tcost, i));
            }
        }
    }
    printf("%d %d %d\n", total0, total, total0/2-total);
}
