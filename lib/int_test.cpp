#include "int.h"
#include <iostream>
#include <string>

void constructor_test() {
  int num = 12345678;
  // integer constructor
  BigInt n(num);
  std::string s(n);
  assert(n == string("12345678"));

  // string constructor
  BigInt ns("98765432");
  cout << ns.to_string() << "\n";
  assert(ns.to_string() == "98765432");
}

void add_test() {
  // tried with 1 digit blocks and it works as expected.
  long long int a = 123456789012;
  long long int b = 99978654349;
  BigInt ni(to_string(a));
  BigInt nj(to_string(b));
  assert((ni + nj).to_string() == to_string(a + b));

  // test operator+=
  ni += nj;
  assert(ni.to_string() == to_string(a + b));
}

void muliplication_test() {
  long long int a = 92349876;
  long long int b = 49876009;
  BigInt na(a);
  BigInt nb(b);
  assert((na * nb).to_string() == to_string(a * b));
  na *= (nb + 9765);
  assert(na.to_string() == to_string(a * (b + 9765)));
}

vector<int> GetVector(int n){
  vector<int> ret;
  while(n > 0){
    int q = n/10;
    int r = n-q*10;
    ret.push_back(r);
    n = q;
  }
  return ret;
}

void AlgorithmD() {
  for (int u = 1000; u <= 9999; ++u) {
    for (int v = 100; v <= 999; ++v) {
      int norm = 10/((v/100)+1);
      int nv = v*norm;
      int nu = u*norm;
      assert(nu /100 >= 5);
      vector<int> vu = GetVector(nu);
      vector<int> vv = GetVector(nv);
      vu.push_back(0);
      int ulen = vu.size();
      int u1 = vu[ulen-1];
      int u2 = vu[ulen-2];
      int u3 = vu[ulen-3];
      int vlen = vv.size();
      int v1 = vv[vlen-1];
      int v2 = vv[vlen-2];
      int qt = (10*u1+u2)/v1;
      int rt = (10*u1+u2) - v1*qt;
      if (false && qt > 11){
        printf("case 1 u= %d %d v= %d %d\n", u, nu, v, nv);
        return;
      }
      int cnt = 0;
      while (qt * v2 > 10*rt + u3 || qt == 10){
        // printf("qt %d rt %d t1 %d t2 %d\n", qt, rt, qt*v2, 10*rt+u3);
        --qt;
        rt += v1;
        ++cnt;
      }
      if (cnt >= 3){
        printf("case 2 u= %d %d v= %d %d\n", u, nu, v, nv);
      }
    }
  }
}
int main() {
  AlgorithmD();
  return 0;
  constructor_test();
  add_test();
  return 0;
}