#include <stdio.h>
#include <stdlib.h>

#define limit 10000000

int main(void){
  int *count = (int*) malloc(limit * sizeof(int));
  
  int i, d, aux, nbSols;
  for (i = 0; i < limit; i++){
    count[i] = 2; /* The trivial divisors */
  }
  count[0] = 0;
  count[1] = 1;
  d = 2;
  while (d*d < limit){
    aux = d*d;
    count[aux]++; /* Perfect squares have an odd number of divisors */
    aux += d;
    while(aux < limit){
      count[aux] += 2; /* Accounting for d and aux/d */
      aux += d;
    } 
    d++;
  }
  nbSols = 0;
  for (i = 0; i < limit - 1; i++){
    if (count[i] == count[i + 1]){
      nbSols++;
    }
  }
  printf("Solutions: %d\n", nbSols);
  return 0;
}
