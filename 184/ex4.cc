#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main() {
    unsigned long long int num = 0, sum = 0, c;
    unsigned int x, xx, y, ya, r = 105, rr = r*r, rr2 = rr*2, rr4 = rr*4, h = r+r-2;

    unsigned int *angles = (unsigned int *)calloc(2*rr, sizeof(unsigned int));
    angles[0] = r-1;

    for(x = 1; x < r; ++x) {
        xx = x*x;
        for(y = 1, xx++, ya = 1; xx < rr; ++y, ya+=2, xx += ya) {
            int value = atan2(y,x)*rr4/M_PI;
            printf("%d %d %d\n", x, y, value);
            angles[value]++;
            h += 2;
        }
    }

    for(x = 0; x < rr2; ++x) {
        if (angles[x]) {
            c = angles[x] * sum;
            sum += angles[x];
            c *= h - sum;
            num += c;
        }
    }

    printf("%llu\n", num*4);

    free(angles);

    return 0;
}
