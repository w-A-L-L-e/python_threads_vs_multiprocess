#!/bin/env/python
#
# Description:  Simple test that starts some threads and does a busy loop to simulate
#               some heavy computation
# Author:       Walter Schreppers
#
import threading


def compute():
    test=0
    # simulate some heavy computation
    for i in range(30000000):
       test = 1/(i+2)

    print(f"{test=}")

if __name__ == "__main__":
    # start 5 trheads and do some simulated heavy computation
    threads = list()
    for index in range(5):
        print("Starting thread", index)
        x = threading.Thread(target=compute, args=())
        threads.append(x)
        x.start()

    for index, thread in enumerate(threads):
        thread.join()
