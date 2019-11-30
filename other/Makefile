CXX=g++
CXXFLAGS=--std=c++17 -Wall

all: ps hide_arg

ps: ps.cpp
	$(CXX) ps.cpp $(CXXFLAGS) -lstdc++fs -o $@

hide_arg: hide_arg.cpp
	$(CXX) hide_arg.cpp $(CXXFLAGS) -o $@