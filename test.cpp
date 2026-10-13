#include <gtest/gtest.h>
#include "primes.hpp"
#include "thread.hpp"

TEST(isPrimeTest, smallNumber) {
    EXPECT_FALSE(isPrime(0));
    EXPECT_FALSE(isPrime(1));
    EXPECT_FALSE(isPrime(8));
    EXPECT_FALSE(isPrime(10));
    EXPECT_FALSE(isPrime(15));
    EXPECT_FALSE(isPrime(90));

    EXPECT_TRUE(isPrime(2));
    EXPECT_TRUE(isPrime(3));
    EXPECT_TRUE(isPrime(11));
    EXPECT_TRUE(isPrime(29));
    EXPECT_TRUE(isPrime(97));
    EXPECT_TRUE(isPrime(67));
}

TEST(primeNumTest, smallNum) {
    std::vector<long long> expected1 = {2,3,5,7};
    EXPECT_EQ(primes(1, 10), expected1);
    std::vector<long long> expected2 = {11,13,17};
    EXPECT_NE(primes(10, 20), expected2);
    std::vector<long long> expected3 = {23, 29};
    EXPECT_EQ(primes(20, 30), expected3);
}

TEST(splitRangeNumber, NoOverlap) {
    std::vector<Prime_task> task = split_range(3, 1 , 10);
    ASSERT_EQ(task.size(), 3u);
    ASSERT_EQ(task.front().start, 1);
    ASSERT_EQ(task.back().end, 10);
    for (size_t i = 1; i < task.size(); i++) {
       EXPECT_EQ(task[i].start, task[i-1].end + 1); 
    }
}

TEST(primeThreadedTest, matchSingleThread) {
    std::vector<long long> expected1 = primes(1, 10);
    for (int t : {1, 2, 4, 8}) {
        EXPECT_EQ(prime_thread(t, 1, 10), expected1) << "threads = " << t;
    }

    std::vector<long long> expected2 = primes(1, 100);
    for (int t : {1, 2, 4, 8}) {
        EXPECT_EQ(prime_thread(t, 1, 100), expected2) << "threads = " << t;
    }
}

TEST(primeThreadedTest, primeThreadNumber) {
    std::vector<long long> expected = {11,13,17,19};
    EXPECT_EQ(prime_thread(3, 10, 20), expected);
}

TEST(PrimesThreadedTest, FullRangeCount) {
    EXPECT_EQ(prime_thread(4, 1, 100).size(), 25u);
    EXPECT_EQ(prime_thread(2, 5000000, 10000000).size(), 316066u);
}