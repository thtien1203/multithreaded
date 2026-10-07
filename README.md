# Multithreaded Prime Finder 

## Description
Find all primes between n and 2n where n is the passed-in argument and measure how much faster it runs with mutiple threads (POSIX pthread) compared with single thread. A single thread is a baseline and a multithreaded version search on the same range. The program checks that both produce the identical results, and then checks the speedup

## Features
- Checks isPrime and collects the primes into a vector
- Uses a Prime_task struct to hold each thread's start, end and it owns results vector
- Splits the range into non-overlapping chunks, one per thread, so no two threads do the same work
- All threads creates pthread_create, and then pthread_join so they run at the same time
- Merges each thread's results into one vector and compares it with the single thread
- Times both versions with std::chrono::steady_clock and prints the speedup

## Results
Range: 5,000,000 to 10,000,000 (316,066 primes found)
Thread       |      Time(s)        |       Speedup      |   Efficiency
    1        |      1.47056        |       1.00x        |   100%
    2        |      0.873346       |       1.68x        |   84%
    4        |      0.450477       |       3.27x        |   82%
    8        |      0.267015       |       5.52x        |   69%

Speedup = single-thread time / multithread time. Efficiency = speedup / number of threads

## Observations
- Time drops and sppedup grows as threads are added, but efficiency falls (84% to 69%), so each extra thread adds less than the one before
- The speedup stays below the ideal because the chunks are uneven (larger numbers take longer to test) and creating threads and merging results add overhead
    