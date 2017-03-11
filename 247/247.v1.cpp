#include <cmath>
#include <queue>
#include <cassert>
#include <cstdio>
#include "../lib/typedef.h"
using namespace std;
//for a harder question how about 44? I got bad alloc, how to speed up and take less memory?
//the first thing to be noted is that, there are many possible (3, 3) or (4,4). The number
//of count is the same as how we reach 3,3 or 4,4. To reach (n, n), we need to move n steps in 
//x direction and n steps in y direction. So that is C_n^{2n}. 

struct prioritySquare
{
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

double next_square_len(double x0, double y0)
{
    return (sqrt((x0-y0)*(x0-y0)+4)-(x0+y0))/2.0;
}

void createNextSquares(prioritySquare& point, prioritySquare& psx, prioritySquare& psy)
{
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

double recursive_find_minimum_n(prioritySquare square, int max)
{
    double minlen=1e6, len1, len2;
    if(square.nx >= max+1 || square.ny >= max+1) return 1e10;
    if(square.nx==max && square.ny==max) return square.len;
    prioritySquare sq1, sq2;
    createNextSquares(square, sq1, sq2);
    len1 = recursive_find_minimum_n(sq1, max);
    len2 = recursive_find_minimum_n(sq2, max);
    if(len1 < minlen) minlen = len1;
    if(len2 < minlen) minlen = len2;
    return minlen;
}

int main()
{
    int maxr = 3;
    int maxcnt = 20; //for 4,4, need to be changed to 70

    int cnt = 0;
    int id_counter = 0;// 0 0 is the first, out of the flow
    int max_id = 0;
    priority_queue<prioritySquare, vector<prioritySquare>, squareLess > psq; //use this to get the next largest square
    struct prioritySquare ps0;

    ps0.x = 1.0;
    ps0.y = 0;
    ps0.nx = 0;
    ps0.ny = 0;
    ps0.len = next_square_len(ps0.x, ps0.y);
    psq.push(ps0);

    double length = recursive_find_minimum_n(ps0, maxr);
    length *= 0.998;
    printf("%20.10f\n", length);

    i64 nx = 0;

    while(cnt != maxcnt){
        prioritySquare point = psq.top();
        ++nx;
        ++id_counter;
        psq.pop();
        if(point.nx == maxr && point.ny == maxr){
            ++cnt;
            max_id = id_counter;
            printf("%d %d %20.10f\n", max_id, cnt, point.len);
        }
        prioritySquare psx, psy;
        createNextSquares(point, psx, psy);
        if(psx.len>= length)
            psq.push(psx);
        if(psy.len>= length)
            psq.push(psy);
    }
    printf("%d\n", max_id);
}
