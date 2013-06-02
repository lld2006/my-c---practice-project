#include <cstdio>
#include <queue>
#include <vector>
using namespace std;
int index0(int dim, int row, int col)
{
    return row*dim+col;
}
struct grid
{
    int row;
    int col;
    int cost;
    grid(int r, int c, int co):row(r), col(c), cost(co){};
};
class gridless
{
    public:
    bool operator()(const grid& g1, const grid& g2)
    {
        return g1.cost > g2.cost;
    }
};
int min(int a, int b)
{
    return a<b ? a:b;
}
int main()
{
    int dim = 80;
    vector<vector<int>> M;
    M.resize(dim);
    for(unsigned int i = 0; i < M.size(); ++i){
        M[i].resize(dim, 1000000);
    }
    FILE* pFile = fopen("matrix.txt", "r");
    for(int i = 0; i < dim; ++i ){
        for(int j = 0; j < dim; ++j){
            fscanf(pFile, "%d", &M[i][j]);
        }
    }
    fclose(pFile);
    //remember it is max priority queue
    priority_queue<grid, vector<grid>, gridless> pq;

    pq.push(grid(0,0, M[0][0]));
    vector<int> vcost;
    vcost.resize(dim*dim, 100000000);
    while(!pq.empty()){
        const grid& g1 = pq.top();
        int row = g1.row;
        int col = g1.col;
        int cost = g1.cost;
        if(vcost[index0(dim, row, col)] > cost){
            vcost[index0(dim, row, col)] = cost; //update the cost
            if(row > 0 && cost + M[row-1][col] < vcost[index0(dim, row-1, col)]) 
                pq.push(grid(row-1, col, cost+M[row-1][col]));
            if(col > 0 && cost + M[row][col-1] < vcost[index0(dim, row, col-1)])
                pq.push(grid(row, col-1, cost+M[row][col-1]));
            if(row < dim - 1 && cost+M[row+1][col] < vcost[index0(dim,row+1, col)])
                pq.push(grid(row+1, col, cost+M[row+1][col]));
            if(col < dim - 1 && cost+M[row][col+1] < vcost[index0(dim, row, col+1)])
                pq.push(grid(row, col+1, cost+M[row][col+1]));
        }
        pq.pop();
    }

    printf("%d\n",vcost[index0(dim, dim-1, dim-1)]); 
}
