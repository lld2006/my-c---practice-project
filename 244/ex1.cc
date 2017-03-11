// Project Euler 244 - Bitbrett + Breitensuche
// runs <100ms
#include <stdio.h>

#define s 0xcccc
#define t 0x5a5a

char *dirs="LRUD",moves[16][4];

int dist[65536*16];
unsigned long long ways[65536*16];
unsigned long long checksum[65536*16];

void create_moves() {
  int gap,dir;
  for (gap=0;gap<16;gap++) for (dir=0;dir<4;dir++) {
    if (dir==0?(gap&3)==3:dir==1?(gap&3)==0:dir==2?gap>=12:gap<4)
      moves[gap][dir]=-1;
    else
      moves[gap][dir]=gap+(dir==0?1:dir==1?-1:dir==2?4:-4);
  }
}

int main() {
  int todo[65536*16];
  int ndone,ntodo,lastntodo,pos,gap,dir,nnew;

  create_moves();

  for (pos=0;pos<65536*16;pos++) dist[pos]=-1;

  ndone=0;ntodo=1;
  todo[0]=s;
  dist[s]=0;
  ways[s]=1;

  int step=0;
  while (dist[t]==-1) {
    printf("%d done, todo until index %d\n",ndone,ntodo);
    step++; lastntodo=ntodo;  
    while (ndone<lastntodo) {
      pos=todo[ndone++];
      gap=pos>>16;
      for (dir=0;dir<4;dir++) if ((nnew=moves[gap][dir])!=-1) {
        nnew=pos&0xffff&~(1<<gap|1<<nnew)
            |(nnew<<16)
            |((pos>>gap&1)<<nnew)
            |((pos>>nnew&1)<<gap);
        if (dist[nnew]==-1) {
          dist[nnew]=step;
          ways[nnew]=0;
          checksum[nnew]=0;
          todo[ntodo++]=nnew;
        }
        if (dist[nnew]==step) {
          ways[nnew]+=ways[pos];
          checksum[nnew]+=(checksum[pos]*243+ways[pos]*dirs[dir])%100000007;
        }
      }
    }
  }
  printf("ways=%llu checksum=%llu\n",ways[t],checksum[t]);
}
