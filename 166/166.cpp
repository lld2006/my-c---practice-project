#include <cstdio>
#include <cassert>
void triple_min_max(int x1, int x2, int total, int& xmin, int& xmax )
{
    xmax = total - x1 -x2;
    xmin = xmax-9;
    if(xmin < 0) xmin = 0;
    if(xmax > 9) xmax = 9;
    return;
}
int search_grids(int total)
{
    int cnt = 0;
    int a3min, a3max, a9min, a9max, a6min, a6max, a11min, a11max;
    int aimax = total < 9? total:9;
    for(int a1 = 0; a1<=aimax; ++a1){
        int a2max = total-a1> 9? 9: total -a1;
        for(int a2 = 0; a2<=a2max; ++a2){
            triple_min_max(a1, a2, total, a3min, a3max);
            for(int a3 = a3min; a3<=a3max; ++a3 ){
                int a4 = total - a1 -a2 -a3; // 4 implied checked the first row
                assert(a4 >= 0 && a4 <= 9);
                int a5max = total-a1> 9? 9: total -a1;
                if(a5max > a2) a5max=a2;
                for(int a5= 0; a5<=a5max; ++a5){
                    triple_min_max(a1, a5, total, a9min, a9max);
                    for(int a9 = a9min; a9<=a9max; ++a9){
                        int a13 = total - a9-a5-a1; //13 implied checked first column
                        assert(a13>=0 && a13<=9);
                        int a10max = total-a9> 9? 9: total -a9;
                        for(int a10=0;a10<=a10max; ++a10){//now we can find out a7
                            int a7 = total - a4 - a13 - a10;//this checks the off diagonal
                            if(a7 < 0 || a7> 9) continue;
                            triple_min_max(a5, a7, total, a6min, a6max);
                            for(int a6 = a6min; a6<=a6max; ++a6){
                                int a8 = total-a5-a6-a7; //second row checked
                                assert(a8>=0 && a8<=9);
                                int a14 = total -a2-a6-a10;//this check the second column
                                if(a14>9 ||a14 <0) continue;
                                triple_min_max(a1,a6,total, a11min, a11max);
                                for(int a11 = a11min; a11<=a11max; ++a11){
                                    int a16 = total - a1 - a6 - a11; //this checked the main diagonal
                                    assert(a16>=0 && a16<=9);
                                    int a15 = total - a13- a14 - a16;//this checked the 4th row
                                    if(a15 <0 || a15 > 9) continue;
                                    int a12 = total - a9 - a10-a11;//this checked the third row
                                    if(a12 <0 || a12 > 9) continue;
                                    if(a3+a7+a11+a15!= total) continue;
                                    if(a4+a8+a12+a16!=total) continue;
                                    if(a5==a2)
                                        ++cnt;
                                    else
                                        cnt += 2;
                                }
                            }
                            
                        }
                    }
                    
                }
            }

        }
    }
    return cnt;
}
int main()
{
    int sum = 0;
    for(int i = 0; i <= 18; ++i){
        int val = search_grids(i);
        if(i == 18)
           sum += val; 
        else
           sum += 2* val;
    }
    printf("%d\n", sum);
}
