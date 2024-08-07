#include <vector>
#include <cstdio>
#include <cassert>
#include <algorithm>
using namespace std;
//lesson, need to have plan before implementation, some change during 
//implementation is very difficult to monitor 
//resize function is kind of dangerous, resize with default value
enum COLOR {H=0, D, S, C};//heart diamond, spade, club
enum GRADE {HIGH = 0,
            ONE = 13, 
            TWO = 26,
            THREE = 39,
            STRAIGHT = 52,
            FLUSH = 65,
            FULL = 78,
            FOUR = 91,
            SFLUSH = 104};

struct grade {
    unsigned int type;
    int sec_type;
    int highest;
    int same_color;
};
    
bool same_color(const vector<int>& color)
{
    return count(color.begin(), color.end(), 5);
}

//high_card 1---13
//one_pair  14--26
//two_pair  27--39 pair one, pair two
//three of a kind, 40--52
//straight 53--65
//flush 66-- 78
//full house 79--91
//four of a kind 92 -- 104 
//straight flush 105 -- 117

void check_num(vector<int>& num, grade& grade)
{
    int stat = 0;
    if(num[12]==1) stat  = 1;
    grade.highest = 0;
    for(unsigned int i = 0 ; i < num.size(); ++i){
        if(num[i]==4) {
            grade.type = FOUR + i;
            continue;
        }
        if( num[i] == 3 ){
            if(grade.type >= ONE) {
                assert(grade.type <= TWO );
                grade.sec_type = grade.type - ONE;
                grade.type = FULL+i;
                continue;
            }
            else{
                grade.type = THREE + i;    
                continue;
            }
        }
        if( num[i] == 2 ){
            if(grade.type >= THREE ){
                grade.type += FULL - THREE;
                grade.sec_type = i;
            }
            else if (grade.type >= ONE){
                assert( grade.type < TWO );
                assert( grade.type != ONE + i);
                int imax = max(i, grade.type-ONE);
                int imin = (i+grade.type-ONE-imax);
                grade.type = imax+TWO;
                grade.sec_type = imin;
            } else {
                grade.type = ONE + i;
            }
            continue;
        } 
        if(num[i] == 1){
            if(stat >=0 && stat < 5) ++stat;
            grade.highest = i;
        }else{
            if(stat < 5 && stat >0 ) --stat;
        }
    }
    if(stat == 5){
        grade.type = STRAIGHT +grade.highest;
        if(grade.same_color) 
            grade.type = SFLUSH + grade.highest;
    }else{
        if (grade.same_color)
            grade.type = FLUSH +grade.highest;//this may still not enough
    }
}
bool poke_compare(vector<int>& num1, vector<int>& color1, 
                  vector<int>& num2, vector<int>& color2){
    struct grade grade1, grade2;
    grade1.type = 0;
    grade1.sec_type = 0;
    grade1.highest = 0;
    grade2.type = 0;
    grade2.sec_type = 0;
    grade2.highest = 0;
    grade1.same_color = same_color(color1);
    grade2.same_color = same_color(color2);
    check_num(num1, grade1);
    check_num(num2, grade2);
    printf("grade %d %d\n", grade1.type, grade2.type);
    if(grade1.type != grade2.type|| (grade1.sec_type != grade2.sec_type)
           || (grade1.highest!=grade2.highest)   ){
        return grade1.type > grade2.type 
           || (grade1.type==grade2.type && grade1.sec_type > grade2.sec_type)
           || (grade1.type==grade2.type && grade1.sec_type == grade2.sec_type && grade1.highest > grade2.highest); // sec
    }else{
        for(int i = 12; i>=0 ; --i)
            if(num1[i]!=num2[i]) return num1[i] > num2[i];
        assert(0);
    }
}

void convert(char card[][3], vector<int>& num, vector<int>& color)
{
    num.clear();
    num.resize(13, 0);//13 numbers in pokers
    color.clear();
    color.resize(4, 0);//4 colors in pokers
    for(int i = 0; i < 5; ++i ){
        switch(card[i][1]) {
            case 'H':
                ++color[0];
                break;
            case 'D':
                ++color[1];
                break;
            case 'S':
                ++color[2];
                break;
            case 'C':
                ++color[3];
                break;
            default:
                assert(0);
        }
        switch(card[i][0]){
            case '2':
                ++num[0];
                break;
            case '3':
                ++num[1];
                break;
            case '4':
                ++num[2];
                break;
            case '5':
                ++num[3];
                break;
            case '6':
                ++num[4];
                break;
            case '7':
                ++num[5];
                break;
            case '8':
                ++num[6];
                break;
            case '9':
                ++num[7];
                break;
            case 'T':
                ++num[8];
                break;
            case 'J':
                ++num[9];
                break;
            case 'Q':
                ++num[10];
                break;
            case 'K':
                ++num[11];
                break;
            case 'A':
                ++num[12];
                break;
            default :
                assert(0);
        }
    }
}
int main()
{
    vector<int> num1, color1, num2, color2;
    FILE* fp;
    fp = fopen("poker.txt", "r");
    char card[5][3]; 
    int win = 0;
    int count = 0;
    while( count < 1000 ){
        int first  =fscanf(fp, "%s %s %s %s %s", card[0], card[1], card[2], card[3], card[4]);
        printf("%s %s %s %s %s---", card[0], card[1],card[2],card[3],card[4]);
        convert(card, num1, color1);
        int second =fscanf(fp, "%s %s %s %s %s", card[0], card[1], card[2], card[3], card[4]);
        printf("%s %s %s %s %s   ", card[0], card[1],card[2],card[3],card[4]);
        convert(card, num2, color2);

        ++count;
        bool awin = false;
        if(first == 5 && second ==5){
            awin =poke_compare(num1, color1, num2, color2);
            if(awin) ++win;
            printf("%d %d\n", awin, count);
        }
        else
            break;
    }
            printf("%d %d\n", win, count);
}
