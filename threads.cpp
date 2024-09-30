/*=============================================================================
author        : Walter Schreppers
filename      : threads.cpp
description   : Minimal example of using threads in c++.
                We don't use any fancy mutexes or locking. We just want to
                see if it's possible to make multiple cpu cores work at once
                (SPOILER: to no surprise for most c++ developers this does
                indeed just work on multiple cores unlike the python version,
                and yes this also worked very similar way back in the 90's using
                the same lib pthread).
=============================================================================*/

#include <iostream>
#include <thread>
#include <vector>

void compute(int id) {
  // simular simulation of heavy computation like we used in python examples
  // to avoid that optimizer optimizes we accumulate a sum instead and do
  // quite some more iterations than the python version, because c++ is still
  // too darn fast when doing these simple for loops ;)
  double test = 0.0;
  for (int i = 0; i < 900000000; i++) {
    test += 1.0 / (i + 2);
  }
  std::cout << "Thread " << id << " finished. test= " << test << std::endl;
}

int main() {
  std::vector<std::thread> threads;

  for (int i = 0; i < 5; i++) {
    std::cout << "Starting thread " << i << std::endl;
    threads.emplace_back(compute, i);
  }

  for (auto &thread : threads) {
    thread.join();
  }

  return 0;
}
