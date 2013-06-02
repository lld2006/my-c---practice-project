#include <stdio.h>
int main(){
int a=0,c=250000,xm=500;
for(int x=1;x<=xm;x++)a+=c/x;
printf("%d",a-xm*(xm+1)/2);
return 0;}
