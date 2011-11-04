#include <cstdio>

int main()
{
    int count = 0, md;
    int month[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31,30, 31};
    int day  = 1;
    int year = 1900;
    while( year <= 2000 ){
        for(int i = 1; i <= 12; ++i){
            if(i != 2) 
                md = month[i-1];
            else if( year % 4 == 0&& year != 1900)
                md = month[1]+1;
            else
                md = month[1];
        day += md;    
            printf("year %d month %d day %d\n", year, (i+1)%12, day %7);
        if(day % 7 == 0 && year != 1900) {
            ++count;
        }
        }
        ++year;
    }
    printf("count is %d\n", count);
    return 0; 
}
