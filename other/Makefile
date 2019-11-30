CXX=g++
CXXFLAGS=--std=c++17 -Wall

all: ps lsof hide_arg

ps: ps.cpp
	$(CXX) ps.cpp $(CXXFLAGS) -lstdc++fs -o $@

lsof: lsof.cpp
	$(CXX) lsof.cpp $(CXXFLAGS) -o $@

hide_arg: hide_arg.cpp
	$(CXX) hide_arg.cpp $(CXXFLAGS) -o $@