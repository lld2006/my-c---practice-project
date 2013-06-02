#include "../lib/typedef.h"
#include <cstdio>
void debug(i64 stat[31][5][3], int day)
{
    printf("----day %d -----\n", day);
    printf("A L C\n");
    for(int j = 0; j < 3; ++j){
        for(int k=0; k<2;++k){
            if(stat[day][j][k] > 0)
                printf("%d %d %lld\n", j, k, stat[day][j][k]);
        }
    }
}
int main()
{
    int dayx = 30;
    i64 stat[31][5][3];
    for(int i = 0; i<31; ++i){
        for(int j = 0; j<5; ++j){
            for(int k =0; k<3; ++k){
                stat[i][j][k] = 0;
            }
        }
    }
    stat[0][0][0] = 1; //zero state
    for(int day = 1; day <= dayx; ++day){
        //for(int dayn = 0; dayn<=day; ++dayn){
            for(int j= 0; j < 3; ++j){ //late
                for(int k = 0; k< 2; ++k){ //absent
                    stat[day][0][k] += stat[day-1][j][k]; //on time
                    stat[day][j+1][k] += stat[day-1][j][k]; //absent
                    stat[day][0][k+1] += stat[day-1][j][k]; //late
                }
            }
        //}
        //debug(stat, day);
    }
    i64 sum = 0;
    for(int i = 0; i < 3; ++i){
        for(int k = 0; k< 2; ++k){
            sum += stat[dayx][i][k];
        }
    }
    printf("%lld\n", sum);
}
