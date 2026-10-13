CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -pthread

TARGET = thread
SOURCE = primes.cpp thread.cpp multithreading.cpp 
TEST_SOURCE = primes.cpp thread.cpp test.cpp

.PHONY: all prof test run clean

all:
	$(CXX) $(CXXFLAGS) $(SOURCE) -o $(TARGET)

prof:
	$(CXX) $(CXXFLAGS) -pg -DPROFILE_ONLY $(SOURCE) -o thread_prof 

test: 
	$(CXX) $(CXXFLAGS) $(TEST_SOURCE) -o test_primes -lgtest -lgtest_main
	./test_primes

run: all
	./$(TARGET)

clean:
	rm -f $(TARGET) thread_prof test_primes gmon.out report.txt