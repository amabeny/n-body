CXX = g++
CXXFLAGS = -std=c++11 -O2

TARGET = nbody
SRC = n-body.cpp

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC)

clean:
	rm -f $(TARGET) output.tsv
