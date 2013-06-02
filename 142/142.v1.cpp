#include <cstdio>
#include <cmath>
#define LIMIT 7000

int is_square(int n) {
   double tmp;
   int k;

   tmp = sqrt(n); 
   k = tmp;
   if (k*k == n) return 1;
   else return 0;
}

main() {
   int a,b,c,d,e,f;
   int a1,b1,c1,d1,e1,f1;

   for(a=1; a<LIMIT; a++) {
      a1 = a*a;

      for(c=a%2; c<a; c+=2) {
         if (c==0) continue;

         c1 = c*c;
         if (!is_square(a1 - c1)) continue;

         for(b=a%2; b<c; b+=2) {
            if (b==0) continue;

            b1 = b*b;
            if (!is_square(c1 - b1)) continue;
            if (!is_square(a1 + b1 - c1)) continue;
            printf("%d %d %d: ", a, b, c);
            printf("x=%d, y=%d, z=%d %d\n", (a1+b1)/2, (a1-b1)/2, (c1 - (a1+b1)/2), c1+(a1-b1)/2);
         }

      }
   }

}
