#include <cmath>
#include <queue>
#include <cassert>
#include <cstdio>
using namespace std;
//for a harder question how about 44? I got bad alloc, how to speed up and take less memory?

struct prioritySquare{
    double x;
    double y;
    double len;
    int nx;
    int ny;
};

class squareLess {
public:
    bool operator() (prioritySquare& p1, prioritySquare& p2 ){
        return p1.len < p2.len;
    }
};

double next_square_len(double x0, double y0){
    return (sqrt((x0-y0)*(x0-y0)+4)-(x0+y0))/2.0;
}

void createNextSquares(prioritySquare& point, prioritySquare& psx, prioritySquare& psy){
    double sql = point.len;
    psx.x = point.x + sql;
    psx.y = point.y;
    psx.len = next_square_len(point.x+sql, point.y);
    psx.nx = point.nx + 1;
    psx.ny = point.ny;

    psy.x = point.x;
    psy.y = point.y + sql;
    psy.len = next_square_len(point.x, point.y+sql);
    psy.nx = point.nx;
    psy.ny = point.ny + 1;
}

int main(){
    int cnt = 0;
    int id_counter = 0;// 0 0 is the first, out of the flow
    int maxr = 3;
    int max_id = 0;
    priority_queue<prioritySquare, vector<prioritySquare>, squareLess > psq; //use this to get the next largest square
    struct prioritySquare ps0;

    ps0.x = 1.0;
    ps0.y = 0;
    ps0.nx = 0;
    ps0.ny = 0;
    ps0.len = next_square_len(ps0.x, ps0.y);
    psq.push(ps0);

    while(cnt != 20){//20 C_3^6
        prioritySquare point = psq.top();
        ++id_counter;
        psq.pop();
        if(point.nx == maxr && point.ny == maxr){
            ++cnt;
            max_id = id_counter;
            printf("%d %d\n", max_id, cnt);
        }
        prioritySquare psx, psy;
        createNextSquares(point, psx, psy);
        psq.push(psx);
        psq.push(psy);
    }
    printf("%d\n", max_id);
}
