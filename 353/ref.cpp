#include <cassert>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <vector>
#include <map>
#include <iostream>
#include <complex>

typedef long long int ll;
typedef std::complex<int> cint;
size_t const N=15;

struct point
{
   point(): x(), y(), z(), next_in_grid(-1) {}
   point(int _x, int _y, int _z)
   : x(_x), y(_y), z(_z), next_in_grid(-1) {}

   int x, y, z;
   size_t next_in_grid;
};

size_t const K=2*35000;
point points[K];
size_t points_size=0;
size_t north=0;
size_t south=0;

// grid of point indexes
size_t const O=64;
size_t const G=2*O;
size_t grid_size=256;
size_t grid[G][G][G];

size_t const P=65535;
size_t const PI=10000;
char sieve[P+1]={0};
size_t primes_size=0;
size_t primes[PI];
cint s2sq[P+1]={};


double f2(double k1, point const &p1, point const &p2)
{
   ll dx=p1.x-p2.x;
   ll dy=p1.y-p2.y;
   ll dz=p1.z-p2.z;
   ll l2=dx*dx+dy*dy+dz*dz;
   double l=sqrt(double(l2));
   double f=2.0*asin(l*k1);
   return f*f;
}


void grid_pos(size_t &gx, size_t &gy, size_t &gz, point const &p)
{
   gx=size_t(p.x+O*grid_size)/grid_size;
   gy=size_t(p.y+O*grid_size)/grid_size;
   gz=size_t(p.z+O*grid_size)/grid_size;
}


void a_point_yo(size_t &ix, point const &p)
{
   // north/south
   if(p.x==0 && p.y==0)
      if(0<p.z)
         north=ix;
      else south=ix;
   size_t gx, gy, gz;
   grid_pos(gx, gy, gz, p);
   points[ix]=p;
   points[ix].next_in_grid=grid[gx][gy][gz];
   grid[gx][gy][gz]=ix;
   ++ix;
}


void wtf(size_t &ix, point const &p)
{
   for(int mz=-1; mz<=1; mz+=2)
      if(0<p.z || 0<mz)
         a_point_yo(ix, point(p.x, p.y, p.z*mz));
   //printf("[%u] (%d, %d, %d)\n", ix, p.x, p.y, p.z);
}


void factors_of(size_t *fn, size_t *fe, size_t &fs, size_t n)
{
   fs=0;
   for(size_t i=0, p, e; i<primes_size && (p=primes[i])*p<=n; ++i)
   {
      for(e=0; n%p==0; ++e)
         n/=p;
      if(e)
      {
         fn[fs]=p;
         fe[fs]=e;
         ++fs;
      }
   }
   if(1<n)
   {
      fn[fs]=n;
      fe[fs]=1;
      ++fs;
   }
}


void gen_int_pos_rec(size_t n, cint c,
   size_t const *fn, size_t const *fe, size_t fs,
   bool half, int z)
{
   while(n<fs && fn[n]%4==3)
      ++n;
   if(n<fs)
   {
      bool was_half=half;
      size_t p=fn[n];
      size_t e=fe[n];
      cint c1=s2sq[p];
      cint c2=conj(c1);
      size_t l;
      if(p==2)
         l=e;
      else if(half)
      {
         l=(e+1)/2;
         half=false;
      }
      else l=0; 

      for(size_t k=l; k<=e; ++k)
      {
         cint s=c;
         for(size_t i=0; i<k; ++i)
            s*=c1;
         for(size_t i=k; i<e; ++i)
            s*=c2;
         gen_int_pos_rec(n+1, s, fn, fe, fs, 2*k==e?was_half:half, z);
      }
   }
   else
   {
      int x=std::abs(c.real());
      int y=std::abs(c.imag());
      if(y<x)
         std::swap(x, y);
      wtf(points_size, point(x, y, z));
   }
}


void gen_int_pos(size_t const *fn, size_t const *fe, size_t fs, int z)
{
   int m=1;
   cint c(1, 0);
   for(size_t i=0; i<fs; ++i)
   {
      size_t p=fn[i];
      size_t e=fe[i];
      if(p%4==3)
      {
         if(e%2!=0)
            return;
         for(e/=2; e--;)
            c*=p;
      }
   }
   gen_int_pos_rec(0, c, fn, fe, fs, true, z);
}


int main()
{
   // sieve
   size_t p=2;
   for(; p*p<=P; ++p)
      if(!sieve[p])
      {
         primes[primes_size++]=p;
         for(size_t n=p*p; n<=P; n+=p)
            sieve[n]=1;
      }
   for(; p<=P; ++p)
      if(!sieve[p])
         primes[primes_size++]=p;

   // gen primes as sum of 2 squares
   for(size_t a=1; a*a<=P; ++a)
      for(size_t b=a; a*a+b*b<=P; ++b)
         s2sq[a*a+b*b]=cint(a, b);

   double S=0;
   for(size_t lr=1; lr<=N; ++lr)
   {
      size_t r=(1<<lr)-1;
      double k1=1.0/2.0/r;

      grid_size=std::max<size_t>(32+lr*16, 2*r/(G-2)+1);
      for(size_t gx=0; gx<G; ++gx)
         for(size_t gy=0; gy<G; ++gy)
            for(size_t gz=0; gz<G; ++gz)
               grid[gx][gy][gz]=size_t(-1);

      // gen r^2=x^2+y^2+z^2 integer triples
      // by enumerating all possible ways to write r^2-z^2 as sum of 2 squares
      points_size=0;
      wtf(points_size, point(0, 0, r));
      for(size_t z=0; z<r; ++z)
      {
         size_t fn[64];
         size_t fe[64];
         size_t fs=0;
         factors_of(fn, fe, fs, r*r-z*z);
         gen_int_pos(fn, fe, fs, z);
      }

      // dijkstra from north to south
      std::vector<bool> visited(points_size, 0);
      std::vector<double> risks(points_size, 0);
      typedef std::multimap<double, size_t> sorted;
      sorted q;
      typedef std::vector<sorted::iterator> indexes;
      indexes c(points_size, q.end());
      c[north]=q.insert(sorted::value_type(0, north));
      double h=42.0;
      while(!q.empty())
      {
         double risk=(*q.begin()).first;
         size_t at=(*q.begin()).second;
         q.erase(q.begin());
         c[at]=q.end();
         if(!visited[at])
         {
            risks[at]=risk;
            visited[at]=1;

            // z=0 mirror baby yeah
            if(points[at].z<0 && visited[at+1])
               h=std::min(h, risk+risks[at+1]);
            else
            {
               size_t g0x, g0y, g0z;
               grid_pos(g0x, g0y, g0z, points[at]);
               for(size_t gx=g0x-1; gx<=g0x+1; ++gx)
                  for(size_t gy=g0y-1; gy<=g0y+1; ++gy)
                     for(size_t gz=g0z-1; gz<=g0z+1; ++gz)
                     {
                        for(size_t i=grid[gx][gy][gz];
                           i!=size_t(-1); i=points[i].next_in_grid)
                        {
                           if(!visited[i])
                           {
                              double dr=f2(k1, points[at], points[i]);
                              if(c[i]==q.end())
                                 c[i]=q.insert(sorted::value_type(risk+dr, i));
                              else if(risk+dr<(*c[i]).first)
                              {
                                 q.erase(c[i]);
                                 c[i]=q.insert(sorted::value_type(risk+dr, i));
                              }
                           }
                        }
                     }
            }
         }
      }
      double M=h/M_PI/M_PI;
      S+=M;

      printf("l=%zu, r=%zu, size=%zu, grid_size=%zu, dr=%.10f\n",
         lr, r, points_size, grid_size, M);
   }
   printf("r=%.10f\n", S);
   return 0;
}
