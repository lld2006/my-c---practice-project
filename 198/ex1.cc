#include <stdio.h>
#include <stdlib.h>

int main (int argc, const char * argv[]) {
    int a = 1;
    int b = 100;
    int c = 0;
    int q = 100000000;
    int q_2 = q / 2;
    
    int count = 0;
    int top = 0;
    int *stack = NULL;
    
    stack = (int *)malloc(q*sizeof(int));
    
    count = 49;
    
    while (1) {
        if (a <= q_2/b && a*b <= q_2) {
            count += 1;
            c = a + b;
            stack[top++] = c;
            stack[top++] = b;
            b = c;
        } else if (top) {
            a = stack[--top];
            b = stack[--top];
        } else {
            break;
        }
    }
    
    printf("%d\n", count);
    return 0;
}
