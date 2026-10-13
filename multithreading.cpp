#include <iostream>
#include <pthread.h>
#include <vector>
#include <chrono>
#include <stdexcept>
#include "primes.hpp"
#include "thread.hpp"


int main () {
    long long num1, num2;
    try {
        std::cout << "Enter the start and end of the range (eg: 5000000 10000000): ";
        std::cin >> num1 >> num2;
        if (!std::cin) {
            throw std::invalid_argument("Please enter the whole number");
        }
        if (num1 < 0 || num2 < 0) {
            throw std::invalid_argument("Numbers must be non-negative");
        }
        if (num1 > num2) {
            throw std::invalid_argument("Start must be larger than end");
        }
    }
    catch (const std::invalid_argument &e) {
        std::cerr << "Error: " << e.what() << '\n';
        return 1;
    }

    //std::vector<long long> result = primes(5000000, 10000000);
    std::vector<long long> result = primes(num1, num2);
    //////////// single thread baseline (without threads) ///////////////
    auto start1 = std::chrono::steady_clock::now();
    result = primes(num1, num2);
    auto end1 = std::chrono::steady_clock::now();
    auto double_seconds = std::chrono::duration<double, std::ratio<1>>(end1 - start1).count();    
    std::cout << "Time: " << double_seconds << " " << "Count: " << result.size() << std::endl;

#ifndef PROFILE_ONLY    
    /////////// multithread ///////////
    int num_thread;
    try {
        std::cout << "Enter number of thread: ";
        std::cin >> num_thread;
        if (!std::cin) {
            throw std::invalid_argument("Please enter the whole number");
        }
        if (num_thread <= 1) {
            throw std::invalid_argument("Numbers must be greater than 1");
        }
    }
    catch (const std::invalid_argument &e) {
        std::cerr << "Error: " << e.what() << '\n';
        return 1;
    } 
    std::vector<Prime_task> tasks = split_range(num_thread, num1, num2);
    for (int i = 0; i < num_thread; i++) {
        std::cout << tasks[i].start << " " << tasks[i].end << " " << std::endl;
    }

    auto start2 = std::chrono::steady_clock::now();
    std::vector<long long> thread = prime_thread(num_thread, num1, num2);
    auto end2 = std::chrono::steady_clock::now();
    auto multiSeconds = std::chrono::duration<double, std::ratio<1>>(end2 - start2).count();  
    std::cout << "Time: " << multiSeconds << " " << "Count: " << thread.size() << std::endl;

    // compare between single thread baseline and multithread
    if (double_seconds / multiSeconds) {    // how much faster of the thread version is
        if (result == thread) {
            std::cout << "Single thread and multithread have the same prime in vector" << std::endl;
        }
        std::cout << "The faster of the thread version is: " << (double_seconds / multiSeconds) << std::endl;
    }
#endif

    return 0;
}

