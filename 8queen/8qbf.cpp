// brute force method to find all possible solutions for 8 queens problem
// lessons learned 
// 1) variable defined and modified, then assume to be 
// the initial value, use const
// 2) check reverse criteria not complete, think !
// 3) in the getNextPermutation function, the less operator is critical
//    when there is possiblity that first equal second 
//      read better code;
#include <cstdio>
#include <vector>
#include <cassert>
#include <cmath>
using namespace std;

void printArray(vector<int>& configVec)
{
    vector<int>::iterator iterBegin= configVec.begin(), 
                          iterEnd  = configVec.end(), iter;
    for( iter = iterBegin; iter != iterEnd; ++iter)
      printf("%d ", *iter);
    printf("\n");
}

void initializePermutation(vector<int>& configVec, unsigned int num)
{
    configVec.resize(num);
    assert(configVec.size() == num);
    vector<int>::iterator iterBegin= configVec.begin(), 
                          iterEnd  = configVec.end(), iter;
    int i=0;
    for( iter =iterBegin; iter != iterEnd; ++iter)
    {
        *iter = ++i;//initialize the vector to 1,...,n
    }
}

//assumption number from 1, ..., n, 
bool getNextPermutation(vector<int>& vec)
{
    if( vec.size() == 0 || vec.size() ==1)
        return false;
    vector<int>:: iterator begin=vec.begin(), end=vec.end();
    vector<int>:: iterator iter, first, second;
    first = end; // search from the end of the vector
    --first;
     // search for pattern  first< second
    second = first--;
    // removed a bug in the next line
    while(second != begin && !(*first <*second))
    { 
      second = first--;
    }

    if(second == begin)
      return false;
    iter = end;
    while(!( *(--iter) > *first));//search for the first element from end
                               // that is greater than first
    //switch the value;
     swap(*first, *iter);
    // from second to last, reverse the vector;
    while(second != end && second != --end )
    {
      //assert something? the thing is that we can not compare two
      //iterators;
      // permutation to next level, reverse the order of all elments 
      // to increase order
      swap(*second++, *end);
    }
    return true;
}

bool checkQueen(const vector<int>& vec)
{
    for(unsigned int i=0; i< vec.size(); ++i)
      for(unsigned int j=i+1; j<vec.size(); ++j)
      {
            unsigned int dist = abs(vec[i] - vec[j]);
            if(dist == j-i) return false;
      }
    return true;
}

int main()
{
  vector<int> vec;
  vec.resize(10);
  for(int i=0; i<10; ++i)
  {
    vec[i] = i;
  }
  int num = 1;
  while(num < 1000000)
  {
    getNextPermutation(vec);
    ++num;  
  }
  for(int i=0; i<10; ++i)
  {
    printf("%d", vec[i]);
  }
  printf("\n");
  
}
//int main()
//{
//  unsigned int solution = 0;
//  unsigned int numQueens = 8;
//  vector<int> permuteConfig;
//  permuteConfig.resize(5);
//  //initializePermutation(permuteConfig, numQueens);
//  permuteConfig[0] = 1;
//  permuteConfig[1] = 1;
//  permuteConfig[2] = 1;
//  permuteConfig[3] = 2;
//  permuteConfig[4] = 2;
//  printArray(permuteConfig);
//  while (getNextPermutation(permuteConfig))
//  {
//    printArray(permuteConfig);
//  }
//  return 0;
//  if(checkQueen(permuteConfig))
//  {
//    printArray(permuteConfig);
//    ++solution;
//  }
//  while (getNextPermutation(permuteConfig))
//  {
//    if(checkQueen(permuteConfig))
//    {
//        printArray(permuteConfig);
//        ++solution;
//    }
//  }  
//  printf("total number of solutions is %u\n", solution);
//  return 0;
//}
