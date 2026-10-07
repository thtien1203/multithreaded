#include <iostream>
#include <pthread.h>
#include <vector>
#include <chrono>

bool isPrime(long long x);
std::vector<long long> primes(long long x, long long y);

// give each thread on it owns data
struct Prime_task{
    long long start, end;
    std::vector<long long> results;
};

void *worker (void *arg);   // thread function

int main () {
    std::vector<long long> result = primes(5000000, 10000000);
    //////////// single thread baseline (without threads) ///////////////
    auto start1 = std::chrono::steady_clock::now();
    result = primes(5000000, 10000000);
    auto end1 = std::chrono::steady_clock::now();
    auto double_seconds = std::chrono::duration<double, std::ratio<1>>(end1 - start1).count();    
    std::cout << "Time: " << double_seconds << " " << "Count: " << result.size() << std::endl;

    /////////// multithread ///////////
    // split thread, for 2 threads on 5,000,000 to 10,000,000, thread 1 takes the first half and thread 2 takes the second half
    std::vector<Prime_task> tasks = {{5000000, 7500000, {}}, {7500001, 10000000, {}}};   

    std::vector<pthread_t> threads(2);
    auto start2 = std::chrono::steady_clock::now();
    for (int i = 0; i < 2; i++) {
        // pthread_create takes 4 argument: a pointer to pthread_t, attributes (use nullptr as default), a function, a pointer to struct
        pthread_create(&threads[i], nullptr, worker, &tasks[i]);    // thread is just start working and return right away
    }

    for (int i = 0; i < 2; i++) {
        pthread_join(threads[i], nullptr);  // the main program waits (block) until the thread 0 finish
    }
    
    std::vector<long long> multiResult;
    for (const auto &t : tasks) {   // loops thread 1 and thread 2 to find the prime and then merge them so the final is one vector from 5000000 to 10000000
        multiResult.insert(multiResult.end(), t.results.begin(), t.results.end()); 
    }
    auto end2 = std::chrono::steady_clock::now();
    auto multiSeconds = std::chrono::duration<double, std::ratio<1>>(end2 - start2).count();    // convert duration to second with floating-point
    std::cout << "Time: " << multiSeconds << " " << "Count: " << multiResult.size() << std::endl;

    // compare between single thread baseline and multithread
    if (double_seconds / multiSeconds) {    // how much faster of the thread version is
        if (result == multiResult) {
            std::cout << "Single thread and multithread have the same prime in vector" << std::endl;
        }
        std::cout << "The faster of the thread version is: " << (double_seconds / multiSeconds) << std::endl;
    }

    return 0;
}

bool isPrime(long long x) {
    if (x < 2) return false;   // 1 is not a prime
    for (long long i = 2; i*i <= x; i++) {
        if (x % i == 0) {
            return false; 
        }
    }
    return true;
}

std::vector<long long> primes(long long x, long long y) {
    std::vector<long long> result;
    for (; x <= y; x++) {
        if (isPrime(x)) {
            result.push_back(x);
        }
    }
    return result;
}

void *worker (void *arg) {
    Prime_task *task = (Prime_task *) arg;  // arg stores the address of struct
    task->results = primes(task->start, task->end);
    return nullptr;
}
