#include <iostream>
#include <thread>
#include <vector>

void compute(int id) {
  // simular simulation of heavy computation like we used in python examples
  // to avoid that optimizer optimizes we accumulate a sum instead and do factor
  // 100 more iterations than the python version, because c++ is still so darn
  // fast when doing simple loops ;)
  double test = 0.0;
  for (int i = 0; i < 3000000000; i++) {
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
