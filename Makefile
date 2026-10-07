CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra

TARGET = thread
SOURCE = multithreading.cpp


all:
	$(CXX) $(CXXFLAGS) $(SOURCE) -o $(TARGET) $(LDFLAGS)

run: all
	./$(TARGET)

clean:
	rm -f $(TARGET)