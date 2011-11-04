#include <cstdio>
#include <vector>
//#include <algorithm>
#include <numeric>
#include <limits>
#include <cassert>

//lesson be very careful about boundary. for example, for a minheap, even we are careful 
//about extraction set some constrains on i,  still need to be very careful about 
//that the right child may not exist;
using namespace std;

class keyless
{
public:
    bool operator() (const pair<int, int>& p1, const pair<int, int>& p2)
    {return p1.second < p2.second;}
};
int index0(int dim, int i, int j)
{ return i*dim+j;}

void decreasekey(vector<pair<int,int> >& pq, int k, int cost)
{
    int parent = (k-1)/2;
    pq[k].second = cost;
    while( k ){
        if(pq[k].second < pq[parent].second){
            swap(pq[k], pq[parent]);
            k = parent;
            parent = (k-1)/2;
        }else{
            k = 0;
        }
    }
}
//for min heap 
void mypop_heap(vector<pair<int, int> >& pq)
{
    swap(pq[0], pq[pq.size()-1]);
    pq.pop_back();
    bool flag = true;
    unsigned int i = 0;
    while(flag && i < pq.size()/2){
        flag = false;
        unsigned int left = 2* i+1;
        unsigned int right = left + 1;
        unsigned int next=i;
        assert(left < pq.size());
        if(pq[i].second > pq[left].second)
            next = left;
        if(right < pq.size() && pq[right].second < pq[left].second)
            next = right;
        if(next > i){
            swap(pq[i], pq[next]);
            flag = true;
            i = next;
        }
    }
}
int main()
{
    FILE* fp;
    fp=fopen("network.txt", "r");
    int ni;
    vector<int> edge;
    //read edge data
    int dim = 40;
    while(fscanf(fp, "%d", &ni)==1){
        if(ni==-1){
            edge.push_back(numeric_limits<int>::max());
        }else{
            edge.push_back(ni);
        }
    }
    assert(static_cast<int>(edge.size()) == dim * dim);
    vector<int> key;
    vector<int> pred;
    key.resize(dim , numeric_limits<int>::max());
    pred.resize(dim, -1);
    vector<pair<int, int> > pq;
    key[0] = 0;
    pq.push_back(pair<int, int>(0, 0));
    for(int j=1; j<dim; ++j){
        pq.push_back(pair<int,int>(j, numeric_limits<int>::max()));
    }
    while(!pq.empty()){
        pair<int, int> vertex = pq[0];
        mypop_heap(pq);
        int curr = vertex.first; //current minimum vertex
        for(unsigned int k=0; k<pq.size(); ++k) {
            int vnode = pq[k].first;
            int cost = edge[index0(dim, curr, vnode)];
            if( cost < key[vnode]){
                key[vnode] = cost;
                pred[vnode] = curr;
                decreasekey(pq, k, cost);
            }
        }
    }
    int min = accumulate(key.begin(), key.end(), 0);
    int sum = 0; 
    for(unsigned int i =0; i< edge.size(); ++i)
        if( edge[i] <numeric_limits<int>::max())
            sum += edge[i];
    printf("%d %d\n", min, sum);
}
