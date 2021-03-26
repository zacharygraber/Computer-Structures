## 1: How many characters do you see printed on screen?
Only two characters get printed. Which 2 of the 3 characters these are is unpredictable, since we don't know which thread(s) will execute first.

## 2: What happened to the executing program?
The program hangs indefinitely. This happens because the thread for the third character (the one that doesn't get printed) blocks indefinitely, waiting on a semaphore that will never be released. The semaphore is initialized to `2`. The first thread to run will decrement it to `1` before printing its character. The second will decrement it to `0` before printing its character. Now, the third thread tries to decrement the semaphore, but can't (since that would make it `-1`), so it blocks until it can. The problem is, though, the semaphore will never be *incremented*, so the block lasts forever.

## 3: The fix
After initializing the semaphore in the `main` function to `2`, we can add the following line:
```c
sem_post(&sem); // FIX for code issue
```
This line *increments* the semaphore to `3` before the threads are executed. This allows each thread to decrement the semaphore without blocking.