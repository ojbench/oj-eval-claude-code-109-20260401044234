CXX = g++
CXXFLAGS = -std=c++17 -O2 -Wall

code: solution.cpp
	$(CXX) $(CXXFLAGS) solution.cpp -o code

clean:
	rm -f code *.o
