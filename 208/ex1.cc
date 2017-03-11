#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define PI 3.141592653589793238462643383
#define eps 1e-6
#define n 70

typedef struct
{
    long long int offset;
    long long int count;
}List;

int compare (const void* source, const void* dest)
{
    List* listSource = (List*) source;
    List* listDest = (List*) dest;
    if((listSource->offset)>(listDest->offset))  return 1;
    return -1;
}
 
double ABS(double x)  {
    if(x<0.0)  return -x;
    return x;
}

int main()  {
    
    int i,i2,I,NUM,j,dir,dir2,num,angle,angle2,A[5];
    long long int offset,total,pow256[8];
    double x,y;
    List* myList;
    List* myList2;
    
    pow256[0]=1;
    for(i=1;i<8;i++)  pow256[i]=pow256[i-1]<<8;
    
    myList=(List*)(malloc)(1*sizeof(List));
    
    num=1;
    myList[0].count=1;
    myList[0].offset=2+127*pow256[2]+128*pow256[3]+128*pow256[4]+128*pow256[5]+128*pow256[6];
    for(I=0;I<n;I++)  {
        myList2=(List*)(malloc)(2*num*sizeof(List));
        for(i=0;i<num;i++)  {
            offset=myList[i].offset;
            dir=(offset&255)-1;
            offset>>=8;
            angle=offset&255;
            
            i2=i<<1;
            angle2=(angle+2*dir+10)%10;
            myList2[i2].offset=myList[i].offset+((angle2-angle)<<8);
            myList2[i2].count=myList[i].count;
            
            dir2=-dir;
            angle2=(angle+5+2*dir2)%10;
            myList2[i2+1].offset=myList[i].offset+(dir2-dir)+((angle2-angle)<<8);
            if(angle<5)  myList2[i2+1].offset+=2*pow256[angle+2];
            else  myList2[i2+1].offset-=2*pow256[angle+2-5];
            myList2[i2+1].count=myList[i].count;
        }
        free(myList);
        num<<=1;
        qsort(myList2,num,sizeof(List),compare);
        NUM=0;
        for(i=1;i<num;i++)  {
            if(myList2[i].offset==myList2[NUM].offset)  {
                   myList2[NUM].count+=myList2[i].count;
            }
            else  {
                   NUM++;
                   myList2[NUM].offset=myList2[i].offset;
                   myList2[NUM].count=myList2[i].count;
            }
        }
        num=NUM+1;
        myList=(List*)(malloc)(num*sizeof(List));
        for(i=0;i<num;i++)  {
             myList[i].offset=myList2[i].offset;
             myList[i].count=myList2[i].count;
        }
        free(myList2);
    }
    total=0;
    for(i=0;i<num;i++)  {
        offset=myList[i].offset;
        dir=(offset&255)-1;
        offset>>=8;
        angle=offset&255;
        for(j=0;j<5;j++)  {
            offset>>=8;
            A[j]=(offset&255)-128;
        }
        if(angle<5)  A[angle]++;
        else  A[angle-5]--;
        
        x=0.0;
        y=0.0;
        for(j=0;j<5;j++)  {
            x+=(double) A[j]*cos((double) j*2.0*PI/10.0);
            y+=(double) A[j]*sin((double) j*2.0*PI/10.0);
        }
        if((ABS(x)<eps)&&(ABS(y)<eps))  total+=myList[i].count;
    }
    printf("%lld\n",total);
       
    return 0;
}
