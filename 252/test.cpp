//-215 -878
//863 -835
//720 -780
//-571 -847
//-920 -871
//-215 -878
#include <cstdio>
#include <vector>
using namespace std;
int triangleArea(int x1, int y1, int x2, int y2, int x3, int y3)
{
    int area = x1*(y2-y3) + x2*(y3-y1)+x3*(y1-y2);
    return area;
}
int main()
{
    vector<int> vx={-218, 863, 720, -571, -920};
    vector<int> vy={-878, -835, -780, -847, -871};
    int sum = 0;
    for(unsigned int i = 1;i<=3; ++i){
        sum +=triangleArea(vx[0], vy[0], vx[i], vy[i], vx[i+1], vy[i+1]); 
        printf("%f\n", sum/2.0);
    }
    printf("%f\n", sum/2.0);
    return 0;
}
