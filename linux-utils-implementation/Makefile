CXX=g++
CXXFLAGS=--std=c++17 -Wall

all: ps lsof hide_arg

ps: ps.cpp utils.hpp
	$(CXX) ps.cpp $(CXXFLAGS) -lstdc++fs -o $@

lsof: lsof.cpp utils.hpp
	$(CXX) lsof.cpp $(CXXFLAGS) -lstdc++fs -o $@

hide_arg: hide_arg.cpp
	$(CXX) hide_arg.cpp $(CXXFLAGS) -o $@