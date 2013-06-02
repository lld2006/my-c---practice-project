#include <stdio.h>
#include <stdlib.h>
#include <time.h>


typedef struct
{
    int x1;
    int y1;
    int x2;
    int y2;
}List;

int MIN(int a,int b)
{
    if(a<b)  return a;
    return b;
}

int MAX(int a,int b)
{
    if(a<b)  return b;
    return a;
}

int compare (const void* source, const void* dest)
{
    List* listSource = (List*) source;
    List* listDest = (List*) dest;
    if ( (listSource->x1) > (listDest->x1))
        return 1;
    else if ( (listSource->x1) < (listDest->x1))
        return -1;
    else if ( (listSource->y1) > (listDest->y1))
        return 1;
    else if ( (listSource->y1) < (listDest->y1))
        return -1;
    else if ( (listSource->x2) > (listDest->x2))
        return 1;
    else if ( (listSource->x2) < (listDest->x2))
        return -1;
    else if ( (listSource->y2) > (listDest->y2))
        return 1;
    else if ( (listSource->y2) < (listDest->y2))
        return -1;

    return 0;
}

int gcd(int a,int b)

{

  if(a<0) a=-a;
  if(b<0) b=-b;

  int c;

  while(b>0)  {
     if(a>=b)  {
        a-=b;
        if(a>=b)  {
           a-=b;
           if(a>=b)  {
              a-=b;
              if(a>=b)  {
                 a-=b;
                 if(a>=b)  {
                    a-=b;
                    if(a>=b)  {
                       a-=b;
                       if(a>=b)  {
                          a-=b;
                          if(a>=b)  {
                             a-=b;
                             if(a>=b)  a%=b;
              }}}}}}}}
     c=a,a=b,b=c;
  }
  return a;
}

int main()
{
     double dtime=clock();    

     List *myList;
     myList=(List*) (malloc) (3000000*sizeof(List));
     
     int u=5000;
     long long int s=290797;
     int M=50515093;
     int R=500;
     int a1,a2,b1,b2,c1,c2,num1,num2,det;
     int I,j,sol,A[u],B[u],C[u],D[u],G,T=0;     
     
     for(I=0;I<u;I++)  {
         s=(s*s)%M;
         A[I]=s%R;
         s=(s*s)%M;
         B[I]=s%R;
         s=(s*s)%M;
         C[I]=s%R;
         s=(s*s)%M;
         D[I]=s%R;
     }
     
     T=0;
     for(I=0;I<u;I++)  {
     for(j=I+1;j<u;j++)  {
         a1=B[I]-D[I],b1=C[I]-A[I],c1=B[I]*C[I]-A[I]*D[I];
         a2=B[j]-D[j],b2=C[j]-A[j],c2=B[j]*C[j]-A[j]*D[j];
         det=b1*a2-b2*a1;
         if(det!=0)  {
            num1=c2*b1-c1*b2;
            num2=c1*a2-c2*a1;
            if(det<0)  det=-det,num1=-num1,num2=-num2;
            if((det*A[I]!=num1)||(det*B[I]!=num2))  {  
            if((det*C[I]!=num1)||(det*D[I]!=num2))  {  
            if((det*A[j]!=num1)||(det*B[j]!=num2))  {  
            if((det*C[j]!=num1)||(det*D[j]!=num2))  {  
            if((num1>=det*MIN(A[I],C[I]))&&(num1<=det*MAX(A[I],C[I])))  {
            if((num2>=det*MIN(B[I],D[I]))&&(num2<=det*MAX(B[I],D[I])))  {
            if((num1>=det*MIN(A[j],C[j]))&&(num1<=det*MAX(A[j],C[j])))  {
            if((num2>=det*MIN(B[j],D[j]))&&(num2<=det*MAX(B[j],D[j])))  {
            G=gcd(num1,det);
            myList[T].x1=num1/G;
            myList[T].y1=det/G;
            G=gcd(num2,det);
            myList[T].x2=num2/G;
            myList[T].y2=det/G;
            T++;
            }}}}}}}}
         }
     }}
     
     qsort(myList,T,sizeof(List),compare);
     
     sol=1;
     for(I=1;I<T;I++)  {
         if(myList[I].x1!=myList[I-1].x1)  sol++;
         else if(myList[I].x2!=myList[I-1].x2)  sol++;
         else if(myList[I].y1!=myList[I-1].y1)  sol++;
         else if(myList[I].y2!=myList[I-1].y2)  sol++;
     }
     
     printf("solution=%d,time=%.3lf sec.\n",sol,(double) (clock()-dtime)/CLOCKS_PER_SEC);

     return 0;
}
