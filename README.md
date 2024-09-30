# Threading vs multiprocessing in python

Just a little test. To validate that indeed only with multiprocessing you get performance boost with multiple core cpu.

```
$ time python thread_test.py
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
python thread_test.py  13.65s user 0.09s system 100% cpu 13.616 total
```

The computation is a simple busy loop with a division which takes around 2.5 seconds. We see even though we have
5 threads the total time is still more than 13 seconds.
Even though we fire multiple threads at the same time its not like in java or c++ where this would also make use of 5 cpu cores.

When we switch to multiprocessing we truly see 5 cpu cores working and the same calculation is now done in
under 3 seconds total.

```
$ time python multi_test.py
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
python multi_test.py  12.30s user 0.02s system 490% cpu 2.513 total
```
# python_threads_vs_multiprocess
