# Questions
### 1. How much time does it take for each thread to complete its task?
    - The single-threaded version took 3.732 seconds to complete
    - The multi-threaded version took about 3.111 seconds to complete
        - The first thread took about 3.111 seconds to complete
        - The second thread took about 1.394 seconds to complete

### 2. In the multi-threaded version does `main thread time == thread 1 time + thread 2 time` ?
No. The main thread time is less than the combined time of each separate thread. This is easily explainable when thinking about what is happening. Both threads are running concurrently, so the total time taken to execute both is not additive, but rather is limited by the "weakest link" (the thread that takes the longest). Of course, the total execution time will be higher than that of the longer thread, since it has some extra overhead to perform, such as reaping the threads, reading command-line args, etc.

### 3. Which method (single-thread or multi-thread) results in a faster execution time? Explain why the given version is faster than the other.
The multi-threaded method is faster than the single-threaded version. In the single-threaded version, each file search must be done sequentially (one, then the next), whereas the multi-threaded approach allows the operations to happen *concurrently*. If you needed to fold 100 pieces of paper, it would be much faster to give half to a friend, then both fold them at the same time, rather than folding all 100 yourself (unless your friend is twice as slow as you--then it would take the same time).

### 4. In the `Step 4 - Execution` section above, why are there two possible outputs for the same code?
Just like with processes, the order in which threads execute is not guaranteed. If you have 2 threads (call them t1 and t2) and t1 executes first, its output will be printed first; however, it is also possible for t2 to execute first, meaning its output would be given before t1's. Another situation is described as follows: the machine has more than one core, each thread is run on a different core, the execution of both threads starts at the exact same time, and neither execution is interrupted by something else. In this situation, the output given first would simply be that of the thread that took less time to execute its operation.
