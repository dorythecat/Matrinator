# Matrinator
A really silly program that my maths teacher promoted me to do, in order to prove that Gauss' method to obtain the
inverse of a matrix is not only viable, but also faster than the adjugate method. (He was right). The main code is
really compact (296 lines, as of last updating this README), and pretty efficient too (With Gauss' method, the inverse
of a 50000x50000 identity matrix takes 4 seconds to complete, with  the adjugate method, 4.18 seconds), and it was
quite a fun project to pour some time onto. Hope you have fun with it!

## Usage
The program takes various arguments. First comes the order of the matrix, then, the method used to solve the inverse
(0 for Gauss, 1 for adjugate), and if more than those two paramenters are present, the program will ask the user
for a matrix to input. Otherwise, an identity matrix will be used. The program will then return the matrix itself, the
determinant, and the inverse of said matrix.

## Limitations
I have only tested this program up to 50000x50000 matrices. From there onwards, there be dragons. It should be easy to
adapt to higher order matrices, but unless you're doing some really complex stuff with this (which I doubt, and actually
challenge you to try out), it should be fine. Besides, most consumer computers will just bug out at around that point,
it takes up 10 GB of RAM out of your system. I would personally reccommed not surpassing the 2000s on your matrix sizes.

## About the graphs
The graphs provided in the "test results" folder have been generated with the following Python code:
```
import time
import subprocess

import matplotlib.pyplot as plt

r = range(<lowr bound>, <higher bound>, 1)
dt = []
for i in r:
    start_time = time.time()
    subprocess.run(['<Path to Matrinator.exe>', str(i), '<0|1>'])
    end_time = time.time()
    result_time = end_time - start_time
    dt.append(result_time)
    print(f"Elapsed time for {i}x{i} identity matrix: {result_time} seconds")

plt.plot(r, dt)

plt.xlabel("Matrix size")
plt.ylabel("Compute time (s)")

plt.show()
```
The tests have been run on the "Release" build of the program, available to download from GitHub, and have been tested
on a fairly common test rig, that should mimic an average computer/laptop setup. The graphs are at different scales
because I gave the program (mostly) the same runtime, except for the various Gauss' method graphs, where I was intrigued
by the sudden change in growth that happens precisely at 512x512 matrices. If anyone finds why this happens, please let
me know, and, kudos to you in advance.

The graphs are as follows:
### Gauss
![Gauss' Method from order 1 to 700.png](test%20results%2FGauss%201-700.png)
![Gauss' Method from order 1 to 1000.png](test%20results%2FGauss%201-1000.png)
![Gauss' Method from order 1 to 1200.png](test%20results%2FGauss%201-1200.png)

### Adjugate (Gauss determinant)
![Adjugate (Gauss's determinant) from order 1 to 200.png](test%20results%2FAdjugate%20%28Gauss%29%201-200.png)

### Adjugate (Recursive minor determinant)
![Adjugate (Recursive minor determinant) from 1 to 12.png](test%20results%2FAdjugate%20%28Adjugate%29%201-12.png)

(This one was implemented separately, and we can't run much higher, since it is O(n!), and, if you know, you know)
