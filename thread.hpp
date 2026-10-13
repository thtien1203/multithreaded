#ifndef THREAD_HPP
#define THREAD_HPP
#include <vector>

// give each thread on it owns data
struct Prime_task{
    long long start, end;
    std::vector<long long> results;
};

void *worker (void *arg);   // thread function
std::vector<Prime_task> split_range(int num_thread, long long start, long long end);
std::vector<long long> prime_thread(int num_thread, long long start, long long end);
#endif