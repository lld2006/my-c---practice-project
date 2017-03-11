#include <cstdio>
#include <cassert>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <algorithm>
#include <ctime>
using namespace std;
//my method reshuffle and check minimum
vector<double> balls;
double dist(int i, int j )
{
    double r0 = 50;
    double val = balls[i]+balls[j]-r0;
    return sqrt(4*r0*(val));
}
double change(int i , int j){
    //assert( i < j && i>=1 && j <= 20);
    double t1, t2;
    if(i==0 && j==1){
            t1 = balls[i] + dist(j, j+1);
            t2 = balls[j] + dist(i, j+1);
    }else if(i==19 && j==20){
            t1 = balls[j] + dist(i, i-1);
            t2 = balls[i] + dist(j, i-1);
    }else if(i>0 && j< 20){
        if(j > i+1){
            t1 = dist(i, i-1) + dist(i, i+1) + dist(j, j-1)+dist(j, j+1);
            t2 = dist(j, i-1) + dist(j, i+1) + dist(i, j-1)+dist(i, j+1);
        }else{
            t1 = dist(i, i -1) + dist(j, j+1);
            t2 = dist(j, i -1) + dist(i, j+1);
        }
    }else if(i == 0){
        if(j == 20){
            if(balls[i]> balls[j] ) return -10000.0;
            t1 = dist(i, i +1) + dist(j, j-1);
            t2 = dist(j, i +1) + dist(i, j-1);
        }else{
            t1 = balls[i] + dist(i, i+1) + dist(j, j-1)+dist(j, j+1);
            t2 = balls[j] + dist(j, i+1) + dist(i, j-1)+dist(i, j+1);
        }
    }else{
        assert(j==20 && i > 0);
        t1 = balls[j] + dist(i, i+1) + dist(i, i-1)+dist(j, j-1);
        t2 = balls[i] + dist(j, i+1) + dist(j, i-1)+dist(i, j-1);
    } 
    return t1 - t2;
}
double total()
{
    double val = balls[0]+balls.back();
    for(unsigned int i = 1; i < balls.size(); ++i){
        val += dist(i, i-1);
    }
    return val;
}
int main()
{
    balls.resize(21, 0.0);
    for(unsigned int i = 0; i<balls.size(); ++i ){
        balls[i] = 30.0 + i;
    }
    //I think balls should have minimum radius
    //swap(balls[0], balls[20]);
    //swap(balls[20], balls[19]);
    //swap(balls[0], balls[20]);
    //for maximum
    //swap(balls[1], balls[20]);
    double adist = total();
    srand (time(NULL));

    bool found = true;
    int nsize = 21;
    int transit = 0;
    double dmin = adist;
    while(transit < 30){
        if(!found){
            //printf("reshuffle\n");
            random_shuffle(balls.begin()+1, balls.begin()+20);
            adist=total();
            ++transit;
        }
        found = false;
        for( int i = 0; i < nsize; ++i){
            for( int j = i+1; j< nsize; ++j){
                double t = change(i,j);
                if(t > 0.0){
                    swap(balls[i], balls[j]);
                    found = true;
                    adist -= t;
                    assert(fabs(adist-total()) < 1e-10);
                    if(adist < dmin) {
                        transit = 0;
                        printf("%d %d %20.10f %20.10f %f %d\n", i, j, dmin, adist, round(dmin*1000), transit);
                        dmin = adist;
                    }
                }
            }
        }
    }
    printf("%f\n", round(dmin*1000));
}
