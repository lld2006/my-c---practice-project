#include <cstdio>
#include <string>
#include <cassert>
#include <cstdio>
using namespace std;

enum roman {I=1, IV=4, V=5, IX=9, X= 10, XL=40, L=50, XC=90, C= 100, CD=400, D= 500, CM=900, M = 1000};
//char runit[][4]= {'I', "IV", 'V', "IX",'X', "XL", 'L', "XC", 'C', "CD",'D', "CM", 'M'};

int  getValue(string& sbuf){
    unsigned int size = sbuf.size();
    int value = 0;
    string str1;
    unsigned int pos = 0;
    while(pos < size){
        string ts(sbuf, pos, 2);
        assert(ts.size() <= 2);
        switch(ts[0]){
            case 'M':
                value += 1000;
                ++pos;
                break;
            case 'D':
                value += 500;
                ++pos;
                break;
            case 'C':
                if(ts.size()==2){
                    switch(ts[1]){
                        case 'M':
                            value += 900;
                            pos += 2;
                            break;
                        case 'D':
                            value += 400;
                            pos += 2;
                            break;
                        default:
                            value += 100;
                            pos += 1;
                    }
                }else{
                    value += 100;
                    ++pos;
                }
                break;
            case 'L':
                value += 50;
                pos += 1;
                break;
            case 'X':
                if(ts.size()==2){
                    switch(ts[1]){
                        case 'C':
                            value += 90;
                            pos += 2;
                            break;
                        case 'L':
                            value += 40;
                            pos+=2;
                            break;
                        default:
                            value += 10;
                            ++pos;
                            break;
                    }
                }else{
                        value += 10;
                        ++pos;
                }
                break;
            case 'V':
                value += 5;
                ++pos;
                break;
            case 'I':
                if(ts.size()==2){
                    switch(ts[1]){
                        case 'X':
                            value += 9;
                            pos+= 2;
                            break;
                        case 'V':
                            value += 4;
                            pos += 2;
                            break;
                        default:
                            ++value;
                            ++pos;
                    }
                }
                else{
                    value += 1;
                    ++pos;
                }
                break;
            default:
                assert(0);
        }
    }
    return value;
}
int reformulate(int value){
    int size=0;
    while(value > 0){
        if(value >= M){
            value -= M;
            ++size;
        }else if(value >= CM){
            value -= CM;
            size += 2;
        }else if(value >= D){
            value -= D;
            ++size;
        }else if(value >= CD){
            value -= CD;
            size += 2;
        }else if(value >= C){
            value -= C;
            ++size;
        }else if(value >= XC){
            value -= XC;
            size += 2;
        }else if(value >= L){
            value -= L;
            ++size;
        }else if(value >= XL){
            value -= XL;
            size += 2;
        }else if(value >= X){
            value -= X;
            size += 1;
        }else if(value >= IX){
            value -= IX;
            size += 2;
        }else if(value >= V){
            value -= V;
            size += 1;
        }else if(value >= IV){
            value -= IV;
            size += 2;
        }else{
            value -= I;
            size += 1;
        }
    }
    return size;
}
int main(){
    char buf[128]; 
    FILE* fp;
    int acc = 0;
    int count = 0;
    fp = fopen("roman.txt", "r");
    while(fscanf(fp, "%s", buf)==1){
        ++count;
        string sbuf(buf);
        int value = getValue(sbuf);
        int newv = reformulate(value );
        if(newv > sbuf.size())
            printf("count %d %d %d %s\n",count, newv, sbuf.size(), sbuf.c_str());
        assert(newv <= static_cast<int>(sbuf.size()));
        acc += (sbuf.size()-newv);
    }
    printf("%d\n", acc);
}
