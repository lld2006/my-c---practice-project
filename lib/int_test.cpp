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
  // for(int i = 0; i < 999; ++i){
  //     BigInt ni(i);
  //     for (int j = 0; j < 999; ++j){
  //         BigInt nj(j);
  //         assert( (ni + nj).to_string() == std::to_string(i +j));
  //     }
  // }
  long long int a = 123456789012;
  long long int b = 99978654349;
  BigInt ni(to_string(a));
  BigInt nj(to_string(b));
  assert((ni + nj).to_string() == to_string(a + b));

  // test operator+=
  ni += nj;
  assert(ni.to_string() == to_string(a + b));
}

int main() {
  constructor_test();
  add_test();
  return 0;
}