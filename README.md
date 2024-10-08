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

## Using threads in c++

Just for completeness I did the same exercise of writing 5 threads that do a
heavy computation (simulated with a similar busy loop but added some more iterations and used a sum so that
the compiler doesnt optimize it away) with c++.
And here we do see 5 cores going to 99% cpu usage. (For this a Makefile and threads.cpp was added as a quick example).

```
$ make
g++  threads.cpp -o threads_with_cpp -lpthread

$ time ./threads_with_cpp
Starting thread 0
Starting thread 1
Starting thread 2
Starting thread 3
Starting thread 4
Thread 3 finished. test= 20.1951
Thread 2 finished. test= 20.1951
Thread 0 finished. test= 20.1951
Thread 4 finished. test= 20.1951
Thread 1 finished. test= 20.1951
./threads_with_cpp  14.61s user 0.00s system 494% cpu 2.958 total
```

When you now run htop and search for threads_with_cpp you see this, proving that
when you use c++ you don't have a GIL and therefore threads really work on seperate cpu cores:

Here's a screenshot of the threads_with_cpp running on my machine:
![Screenshot from 2024-09-30 21-42-47](https://github.com/user-attachments/assets/cb4b2ce2-59ca-4eaf-adea-45c3f755c156)

## Conclusions

Right now, when using python it's still best to use multi processing if you want all your cores to do some work. Sure you loose a bit of memory with multiple python interpreters being started but it allows you to churn through a lot of data more quickly by using multiple cpu cores.

With c++ and java you can also just use threads to perform something on multiple cpu cores (unlike with python where this didnt work in above example). This is also most likely why the latest python versions now want to move to having an option to turn of the GIL. This however makes it harder for a lot of libraries to be thread safe and most likely a lot of existing pip packages will break when running without the GIL.
And most likely there is some pip package out there using green threads or something that also allows doing something similar to c++ but as python makes multi processing so simple and straightforward, for now I'm sticking with that.
