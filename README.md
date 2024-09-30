# Threading vs multiprocessing in python

Just a little test. To validate that indeed only with multiprocessing you get performance boost with multiple core cpu.

```
$ time python threads_example.py
Starting thread 0
Starting thread 1
Starting thread 2
Starting thread 3
Starting thread 4
test=3.333333222222226e-08
test=3.333333222222226e-08
test=3.333333222222226e-08
test=3.333333222222226e-08
test=3.333333222222226e-08
python threads_example.py  13.83s user 0.11s system 100% cpu 13.838 total
```

The computation is a simple busy loop with a division which takes around 2.5 seconds. We see even though we have
5 threads the total time is still more than 13 seconds.
Even though we fire multiple threads at the same time due to the GIL it's not like in java or c++ where this would also make use of 5 cpu cores.

When we switch to multiprocessing we truly see 5 cpu cores working and the same calculation is now done in
under 3 seconds total.

```
$ time python multi_example.py
starting process 0...
starting process 1...
starting process 2...
starting process 3...
starting process 4...
test=3.333333222222226e-08
test=3.333333222222226e-08
test=3.333333222222226e-08
test=3.333333222222226e-08
test=3.333333222222226e-08
python multi_example.py  12.30s user 0.02s system 479% cpu 2.569 total
```

Tested with python 3.9 and 3.12 with similar results (above timings were with 3.9. in 3.12 both are a little faster
but still the multiprocess version is roughly 5 times faster than the threaded one).

Just for completeness I did the same exercise of writing 5 threads that do a
heavy computation with c++.
And here we do see 5 cores going to 99% cpu usage. (For this a Makefile and threads.cpp was added as a quick example).

```
make
g++  threads.cpp -o threads_with_cpp -lpthread
(python_env) ➜  threads_vs_multiprocess git:(main) ✗ ./threads_with_cpp
Starting thread 0
Starting thread 1
Starting thread 2
Starting thread 3
Starting thread 4
```

When you now run htop and search for threads_with_cpp you see this, proving that
when you use c++ you don't have a GIL and therefore threads really work on seperate cpu cores:

Here's a screenshot of the threads_with_cpp running on my machine:
