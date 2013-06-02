#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct { int a3min, a3max; double angle; } ta_t;

static ta_t alist[211*211];
static int  nal;

#define JPI (3.141592653589793238462643383)
#define EPSILON (0.000000001)

static double angle(int x, int y) {
  double a = asin( fabs(y) / sqrt(x*x+y*y) );
  
  if (x>=0 && y>=0) return a;
  if (x<=0 && y>=0) return JPI - a;
  if (x<=0 && y<=0) return JPI + a;
  
  return 2*JPI - a;
}

static int qstatcmp(const void *a, const void *b) {
  double r = ((ta_t *)a)->angle;
  double s = ((ta_t *)b)->angle;
  
  return (r<s) ? -1 : (r>s);
}

static int good(double ang1, double ang2) {

  ang2 -= ang1;
  if (ang2 < 0) ang2 += 2*JPI;
  
  return (ang2 < JPI-EPSILON);
}

static double foo_fast(double r) {
  double ct;
  int x, y, a1, a2, a3;
  
  nal = 0;
  for (x=-r; x<=r; x++) for (y=-r; y<=r; y++) if (0<x*x+y*y && x*x+y*y<r*r) alist[nal++].angle = angle(x,y);
  qsort(&alist[0],nal,sizeof(ta_t),qstatcmp);

  for (a1=0; a1<nal; a1++) {
    for (a3=a1+1; a3<nal; a3++) if (!good(alist[a1].angle,alist[a3].angle)) break;
    alist[a1].a3max = a3 - 1;
    for (a3=nal-1; a3>a1; a3--) if (!good(alist[a3].angle,alist[a1].angle)) break;
    alist[a1].a3min = a3 + 1;
  }
  
  ct = 0;

  for (a1=0; a1<nal; a1++) if (good(0,alist[a1].angle)) {
    for (a2=a1+1; a2<nal; a2++) if (good(alist[a1].angle,alist[a2].angle)) {
      int extra = 1 + alist[a2].a3max - alist[a1].a3min;
      if (extra > 0) ct += extra;
    }
  }
 
  return ct;
}

int main(void) {
  int r[] = { 105 };
  int i;
  
    printf("count(%2d) = %f\n",r[i],foo_fast(r[i]));
    
  return 0;
}
