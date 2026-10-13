#include "primes.hpp"
#include <vector>

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