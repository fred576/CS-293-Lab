#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <cassert>
#include <vector>
#include <iterator>
#include "rdtsc.h"

typedef unsigned int uint32;
typedef unsigned long long uint64;
typedef unsigned long long ticks;

using namespace std;


// In this exercise, we will compare the performance of arrays and vectors.

// The key difference between arrays and vectors is that the size of an
// array is not flexible, while the size of a vector can be adjusted. For
// example, using vector.push_back(a) can extend the length of the vector
// by 1. However, this flexibility comes with an overhead cost for automatic
// size maintenance. Our objective is to measure this cost by calculating the
// average access time (average cost of one read/write) to the container.

// We will use the following simple test program:

//  1. Declare the container.
//  2. Assign container[i] = i for i ranging from 0 to N.
//  3. Find the maximum value stored in the container and return the value.

// The above program will have 2N accesses to the container
// (N writes and N reads). So average access time = runtime/(2N)

// If the container is an array, the size needs to be declared in advance.
// In the case of vectors, we will use push_back to insert elements and
// simulate the flexible size of vectors.

// For arrays, write the following two versions of the test:
//  1. Locally declared array.
//  2. Globally declared array.

// For vectors, write the following four versions of the test:
//  1. Local vector.
//  2. Local vector with reserve ( refer to the C++ manual for the
//                                 reserve function).
//  3. Local vector with access to the vector using an iterator.
//     For example, for(int v : vector).
//  4. Global vector (you may use static keyword).

// Run your experiments for N = 2 2*64 2*64*64 2*64*64*64 2*64*64*64*64
// and compute average runtime

// For measuring time use "rdtsc.h"
// It has class, ClockCounter, which measure time by counting clock of CPU.

// Run your code for various compilation levels -O0,-O1,-O2,-O3

//----------------------------------------------------------------------------

//==================================

int test_array(size_t N) {

  int bigarray[N];
  for(unsigned int k = 0; k<N; ++k)
    bigarray[k] = k;
  int sum = 0;
  for(unsigned int k = 0; k<N; ++k)
    { if( bigarray[k] > sum ) sum = bigarray[k]; }
  return sum;
  // allocate an array of size N;
  // Your code must not have memory leaks.
  // You may also try using pointers.
}

//==================================

int test_array_pre_allocated( int* bigarray, size_t N) {
  for(unsigned int k = 0; k<N; ++k)
    bigarray[k] = k;
  int sum = 0;
  for(unsigned int k = 0; k<N; ++k)
    { if( bigarray[k] > sum ) sum = bigarray[k]; }
  return sum;

  // Allocate the array once by the caller and receive the pointer
}

//==================================

int test_local(size_t N) {
  //Implementation given
  vector<int> bigarray;
  for(unsigned int k = 0; k<N; ++k)
    bigarray.push_back(k);
  int sum = 0;
  for(unsigned int k = 0; k<N; ++k)
    { if( bigarray[k] > sum ) sum = bigarray[k]; }
  return sum;
}

//==================================

int test_local_reserve( size_t N ) {
   vector<int> bigarray;
   bigarray.reserve(N);
  for(unsigned int k = 0; k<N; ++k)
    bigarray.push_back(k);
  int sum = 0;
  for(unsigned int k = 0; k<N; ++k)
    { if( bigarray[k] > sum ) sum = bigarray[k]; }
  return sum;
}

//==================================

int test_local_iter(size_t N) {
vector<int> bigarray;
  for(unsigned int k = 0; k<N; ++k)
    bigarray.push_back(k);
  int sum = 0;
  vector<int>::iterator ptr ;
  for(ptr = bigarray.begin(); ptr!= bigarray.end(); ++ptr)
    { if( *ptr> sum ) sum = *ptr; }
  return sum;
}

//==================================
static std::vector<int> myArray;
int test_static(size_t N) {
  int sum = 0;
  for(unsigned int k = 0; k < N; ++k)
    myArray.push_back(k);
  for(unsigned int k = 0 ; k < N; ++k)
    {if(myArray[k] > sum) sum = myArray[k];}
  //declare the vector static
  return sum;
}


//----------------------------------------------------------------------------

int main() {
  ClockCounter time;
  const size_t NM = 32 * 1024 * 1024;
  size_t N = 2;

  N = 2;
  int sum = 0;
  float average = 0;
  for( unsigned idx = 0; idx < 4; idx++ ) {
    const size_t M = NM/N;
    

    // Example: local vector - on stack
    time.start();
    sum = 0;
    for(unsigned int k = 0; k<M; ++k) { sum += test_array(N); }
    double t = (double)time.stop();
    //std::cerr << t <<"\n";
    average += t;
    N = N*64;
  }
  average/=(2*NM);
  std::cout<<"Average of local array: "<<average/4 <<"\n";

  N = 2;
  sum = 0;
  average = 0;
  for( unsigned idx = 0; idx < 4; idx++ ) {
    const size_t M = NM/N;

    int bigarray[N];
    // Example: local vector - on stack
    time.start();
    sum = 0;
    for(unsigned int k = 0; k<M; ++k) { sum += test_array_pre_allocated(bigarray, N); }
    double t = (double)time.stop();
    //std::cerr << t <<"\n";
    average +=t;
    N = N*64;
  }
  average/=(2*NM);
  std::cout<<"Average of pre-allocated array: "<<average/4<<"\n";

  N = 2;
  sum = 0;
  average = 0;
  for( unsigned idx = 0; idx < 4; idx++ ) {
    const size_t M = NM/N;
    int bigarray[N];

    // Example: local vector - on stack
    time.start();
    sum = 0;
    for(unsigned int k = 0; k<M; ++k) { sum += test_local(N); }
    double t = (double)time.stop();
    //std::cerr << t <<"\n";
    average +=t;
    N = N*64;
  }
  average/=(2*NM);
  std::cout<<"Average of local vector: "<<average/4<<"\n";

  N = 2;
  sum = 0;
  average = 0;
  for( unsigned idx = 0; idx < 4; idx++ ) {
    const size_t M = NM/N;
    int bigarray[N];

    // Example: local vector - on stack
    time.start();
    sum = 0;
    for(unsigned int k = 0; k<M; ++k) { sum += test_local_reserve(N); }
    double t = (double)time.stop();
    //std::cerr << t <<"\n";
    average +=t;
    N = N*64;
  }
  average/=(2*NM);
  std::cout<<"Average of local vector with reserve: "<<average/4<<"\n";

  N = 2;
  sum = 0;
  average = 0;
  for( unsigned idx = 0; idx < 4; idx++ ) {
    const size_t M = NM/N;
    int bigarray[N];

    // Example: local vector - on stack
    time.start();
    sum = 0;
    for(unsigned int k = 0; k<M; ++k) { sum += test_local_iter(N); }
    double t = (double)time.stop();
    //std::cerr << t <<"\n";
    average +=t;
    N = N*64;
  }
  average/=(2*NM);
  std::cout<<"Average of local vector with iterator: "<<average/4<<"\n";

  N = 2;
  sum = 0;
  average = 0;
  for( unsigned idx = 0; idx < 4; idx++ ) {
    const size_t M = NM/N;
    int bigarray[N];

    // Example: local vector - on stack
    time.start();
    sum = 0;
    for(unsigned int k = 0; k<M; ++k) { sum += test_static(N); }
    double t = (double)time.stop();
    //std::cerr << t <<"\n";
    average +=t;
    N = N*64;
  }
  average/=(2*NM);
  std::cout<<"Average of Globally declared static vector: "<<average/4<<"\n";


  return 0;
}
