#!/bin/env python
#
# Description: Some quickly written example of doing same computation with multiprocessing instead of threads
# Author:      Walter Schreppers
#
from multiprocessing import Process


def compute():
    test=0
    for i in range(30000000):
       # simulate some heavy computation
       test = 1/(i+2)

    print(f"{test=}")

if __name__ == '__main__':
    procs = []
    for i in range(5):
        p = Process(target=compute, args=())
        print(f"starting process {i}...")
        p.start()
        procs.append(p)

    result = map(lambda proc: proc.join(), procs)
