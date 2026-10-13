#include <iostream>
#include "thread.hpp"
#include "primes.hpp"
#include <vector>
#include <pthread.h>

void *worker (void *arg) {
    Prime_task *task = (Prime_task *) arg;  
    task->results = primes(task->start, task->end);
    return nullptr;
}

std::vector<Prime_task> split_range(int num_thread, long long start, long long end) {
    long long total_gap = (end - start) / num_thread;
    std::vector<Prime_task> tasks(num_thread);
    for (int i = 0; i < num_thread; i++) {
        tasks[i].start = start + i * total_gap;
        tasks[i].end = tasks[i].start + total_gap;
                tasks[i].results = {};
        if (i > 0 && tasks[i].start == tasks[i-1].end) {
            tasks[i].start += 1;
        }
    }
    return tasks;
}

std::vector<long long> prime_thread(int num_thread, long long start, long long end) {
    std::vector<Prime_task> tasks = split_range(num_thread, start, end);
    std::vector<pthread_t> threads(num_thread);
    for (int i = 0; i < num_thread; i++) {
        // pthread_create takes 4 argument: a pointer to pthread_t, attributes (use nullptr as default), a function, a pointer to struct
        pthread_create(&threads[i], nullptr, worker, &tasks[i]);    // thread is just start working and return right away
    }
    for (int i = 0; i < num_thread; i++) {
        pthread_join(threads[i], nullptr);  // the main program waits (block) until the thread 0 finish
    }
    std::vector<long long> merged;
    for (const auto &t : tasks) {   // loops thread 1 and thread 2 to find the prime and then merge them so the final is one vector from 5000000 to 10000000
        merged.insert(merged.end(), t.results.begin(), t.results.end()); 
    }
    // std::cout << "Count: " << merged.size() << std::endl;
    return merged;
}