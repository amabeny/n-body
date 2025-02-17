# Compiler
CXX = g++
CXXFLAGS = -Wall -O2 -std=c++17

# Target executable
TARGET = mergesort

# Source files
SRCS = mergesort.cpp

# Object files
OBJS = $(SRCS:.cpp=.o)

# Default rule: build the executable
all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean rule: removes compiled files
clean:
	rm -f $(OBJS) $(TARGET)
