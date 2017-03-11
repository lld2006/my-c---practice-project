#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#if 0
#define R (10000)
#define M (400)
#define C (50000)
#else
#define R (20000)
#define M (400)
#define C (1000000)
#endif

#define LIM ((R-1)/M)

typedef struct { int x[2], y[2], z[2]; } cuboid_t;

static cuboid_t cuboid[C];
static cuboid_t cub2[C];
static double   vol = 0;

static int *pop[1+LIM][1+LIM][1+LIM] = {{{NULL}}};
static int np[1+LIM][1+LIM][1+LIM] = {{{0}}};

static int lfg(int reset) {
  static int s[56];
  static unsigned long long k = 0;
  if (reset) { k = 0; return -1; }
  if (++k <= 55) {
    s[k%56] = ( 100003 + 200003*(4000000-k) + ((300007*k)%1000000) * ((k*k)%1000000) ) % 1000000 - 500000;
  } else {
    s[k%56] = ( s[(k+32)%56] + s[(k+1)%56] + 1000000 ) % 1000000 - 500000;
  }
  return s[k%56] + 500000;
}

static void add_cuboid(cuboid_t *c, int idx, int max_idx) {

  for (; idx<max_idx; idx++)
    if (  c->x[0]<cub2[idx].x[1] && c->x[1]>cub2[idx].x[0] \
       && c->y[0]<cub2[idx].y[1] && c->y[1]>cub2[idx].y[0] \
       && c->z[0]<cub2[idx].z[1] && c->z[1]>cub2[idx].z[0] )
      break;
  
  if (idx < max_idx) {
    cuboid_t chunk[2];
    chunk[0].x[0] = chunk[1].x[0] = c->x[0];   chunk[0].x[1] = chunk[1].x[1] = c->x[1];
    chunk[0].y[0] = chunk[1].y[0] = c->y[0];   chunk[0].y[1] = chunk[1].y[1] = c->y[1];
    chunk[0].z[0] = chunk[1].z[0] = c->z[0];   chunk[0].z[1] = chunk[1].z[1] = c->z[1];

#define TRY(COORD,FACE)                                                           \
  if ( c->COORD[0]<cub2[idx].COORD[FACE] && cub2[idx].COORD[FACE]<c->COORD[1] ) { \
    chunk[0].COORD[1] = chunk[1].COORD[0] = cub2[idx].COORD[FACE];                \
    add_cuboid( &chunk[FACE],   idx+1, max_idx );                                 \
    add_cuboid( &chunk[1-FACE], idx,   max_idx );                                 \
  }

    TRY(x,0) else TRY(x,1) else TRY(y,0) else TRY(y,1) else TRY(z,0) else TRY(z,1)

  } else {
    vol += (c->x[1]-c->x[0]) * (c->y[1]-c->y[0]) * (c->z[1]-c->z[0]);
  }
  
  return;
}

int main(void) {
  clock_t clk = clock();
  int i, j, k;

  lfg(1);

  for (i=0; i<C; i++) {
    int p = (cuboid[i].x[0] = lfg(0) % R) / M;
    int q = (cuboid[i].y[0] = lfg(0) % R) / M;
    int r = (cuboid[i].z[0] = lfg(0) % R) / M;
    cuboid[i].x[1] = cuboid[i].x[0] + 1 + lfg(0)%(M-1);
    cuboid[i].y[1] = cuboid[i].y[0] + 1 + lfg(0)%(M-1);
    cuboid[i].z[1] = cuboid[i].z[0] + 1 + lfg(0)%(M-1);
    if (!(np[p][q][r]&(1+np[p][q][r]))) pop[p][q][r] =(int*) realloc(pop[p][q][r],(2*np[p][q][r]+1)*sizeof(int));
    pop[p][q][r][np[p][q][r]++] = i;
  }
  
  if (0) for (i=1; i<C; i++)
    if (  cuboid[i].x[0]<cuboid[0].x[1] && cuboid[i].x[1]>cuboid[0].x[0]
       && cuboid[i].y[0]<cuboid[0].y[1] && cuboid[i].y[1]>cuboid[0].y[0]
       && cuboid[i].z[0]<cuboid[0].z[1] && cuboid[i].z[1]>cuboid[0].z[0]) {
      printf("cuboid[%d] intersects cuboid[0]\n",i);
      return 0;
    }
    

  for (i=0; i<C; i++) {
    int p, q, r, nc2=0;
    for (p=(cuboid[i].x[0]+1-M)/M; p<=(cuboid[i].x[1]-1)/M; p++) if (0<=p && p<=LIM) {
      for (q=(cuboid[i].y[0]+1-M)/M; q<=(cuboid[i].y[1]-1)/M; q++) if (0<=q && q<=LIM) {
        for (r=(cuboid[i].z[0]+1-M)/M; r<=(cuboid[i].z[1]-1)/M; r++) if (0<=r && r<=LIM) {
          for (j=0; j<np[p][q][r] && (k=pop[p][q][r][j])<i; j++ ) {
            cuboid_t *c = &cuboid[k];
            if (  cuboid[i].x[0]<c->x[1] && cuboid[i].x[1]>c->x[0] \
               && cuboid[i].y[0]<c->y[1] && cuboid[i].y[1]>c->y[0] \
               && cuboid[i].z[0]<c->z[1] && cuboid[i].z[1]>c->z[0] ) {
              cub2[nc2].x[0] = c->x[0];   cub2[nc2].x[1] = c->x[1];
              cub2[nc2].y[0] = c->y[0];   cub2[nc2].y[1] = c->y[1];
              cub2[nc2].z[0] = c->z[0];   cub2[nc2].z[1] = c->z[1];
              nc2++;
            }
          }
        }
      }
    }
    if (i<2) printf("C%d has parameters {(%d,%d,%d),(%d,%d,%d)}\n",i+1,cuboid[i].x[0],cuboid[i].y[0],cuboid[i].z[0],cuboid[i].x[1]-cuboid[i].x[0],cuboid[i].y[1]-cuboid[i].y[0],cuboid[i].z[1]-cuboid[i].z[0]);
    add_cuboid(&cuboid[i],0,nc2);
    if (i+1 == 100) printf("V100 = %f\n",vol);
  }
  
  printf("Volume = %f\n",vol);
  printf("Timing = %f seconds\n",(clock()-clk)/(double)CLOCKS_PER_SEC);
      
  return 0;
}
