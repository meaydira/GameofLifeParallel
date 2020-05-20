# GameofLifeParallel
Parallel Implementation of Conway's Game of Life using OpenMP

1.1.Purpose
In this assignment, we were instructed to do implement a parallel version of Conway’s Game of Life. We were provided with a serial version of the game. Through the use of the parallel programming techniques and OpenMP, my aim was to increase the performance of running time of Conway’s Game Of Life. Parallel Programming Assignment 1 Part 1 : Conway’s Game of Life
1.2.About Game of Life
The universe of the Game of Life is a cellular automaton, in which cells live on a 2- dimensional world. They are born, live and die over successive generations. The world is defined as a binary-valued array, and each generation evolves according to the following rules:
• Each cell can be one of two possible states: alive or dead.
• Every cell interacts with its eight neighbours, which are the cells that are horizontally,
vertically and diagonally adjacent.
• At each step in time, the following transitions occur:
- Any live cell with fewer than two live neighbours dies, as if caused by under- population. - Any live cell with two or three live neighbours lives on to the next generation.
- Any live cell with more than three live neighbours dies, as if by overcrowding.
- Any dead cell with exactly three live neighbours becomes a live cell, as if by reproduction.
The first generation can be created randomly and the successive generations will follow the above rules simultaneously to every cell. Each generation is a pure function of the preceding one. The rules continue to be applied repeatedly to create further generations.
(Game information is taken from the assignment description.)

2.Implementation 2.1.Analysis
For the assignment, we needed to use two parallelism techniques: data parallelism and task parallelism.I analyzed the code to identify serial and potentially parallel parts.
First I have tried to analyze the performance of the code, identify different tasks and their computation time to decide on the bottleneck operation. I have used the getTime() function provided to identify parts that has higher run time.
Generating and initializing the world took 0.002 seconds which includes memory allocation, and initialization. After a few experiments, I decided to keep this part serial and thought that it should be done by master thread since it didn’t make a noticeable difference in the performance and it was only a one time operation; so I came to the conclusion that it wasn’t worth to the parallelization overhead. Also, I have printed the computation time and Meshplot() display operation’s time since they were both tasks which need to be done in each iteration. The output of the running time for these tasks can be seen in the screenshots below.
  
When I inspected the results, I have seen that displaying the results and computing the next generation had the highest running time and realized that plotting the current world was taking x30 / x35 times more than computing the next generation of cells. When computation took only 0.003 sec on average, displaying the data took 0.1 seconds on average for each iteration.Hence, it would be a logical move to deploy task parallelism for these two tasks since they were not dependent, they were appropriate for running concurrently. They were not doing modifications on the current world array but only reading from it, so I have added a firstprivate variable as currWorld. I have used task parallelism for:
1-Computing the nextWorld array’s data
2-Displaying currentWorld’s data.
I also decided to deploy data parallelism for nested loops in which I can use one-dimensional decomposition. Consequently, I decided to parallelize the nested for loop section for next generation cells computing part because there was no loop carried dependency, except population array.
In each iteration, number of live cells should be added to population’s array same index, so multithreading could have created a race condition here. I solved this problem by using a temporary variable int sum, adding to it by using OpenMP’s reduction(operation:list) clause.
2.2.Test of Correctness
To make sure that my parallel version of Conway’s Game of Life works correctly, I have used the problems with known solutions like the 2x2 Block, and saw that my code gives the same result with the serial version.

In addition, I have used the step by step iterating command with small inputs to manually check if the parallel version’s iterations are proceeding and be displayed correctly according to the game rules.
 3.Experimental Results 3.1. Experiment 1
For the first, experiment, I have run the code on campus clusters with different number of threads, 1,2,4,8 and 16. You can see the results in the charts and snapshots below.
Results were expected and speedup was close to the optimal expected result (%98 efficiency) for thread number 2 but with the increase in the number of threads, efficiency decreased which might be due to the parallelization overhead for increasing number of threads.

 Figure 1: Running Time for Different Thread Counts: 1,2,4,8,16
 Figure 2: Running Time in Seconds for Different Thread Counts n: 2000
 
3.2. Experiment 2
For the first, experiment, I have run the code on campus clusters with different number of input sizes n , 2000, 4000, 6000, 8000 and 10.000; and with a thread count 16. You can see the results in the charts and snapshots below.
Results were unexpected for n = 2000, which has higher running time than bigger input sizes. I think this may be due to cache and the load on the machine.


4.Conclusion
The final implementation of my Game of Life parallel version combines both task and data parallelism. These include:
• utilising minimum 2 threads for task parallelism
• parallelising nested loops to include data parallelism
Since simulation had a significantly higher running time than the other task, task parallelism was not efficient enough to speed up the iterations since tasks had to wait each other and synchronize at the end of each iteration. Also, using parallel techniques for sections of code which are not hard to perform or compute causes unnecessary parallelization overhead which can cause to a decrease in speedup factor. However, the implementation had significantly successful results which indicates that Game of Life is appropriate for a multithreaded implementation.
