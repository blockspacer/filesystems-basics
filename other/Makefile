CXX=g++
CXXFLAGS=--std=c++17 -Wall

all: ps lsof hide_arg

ps: ps.cpp utils.cpp
	$(CXX) ps.cpp utils.cpp $(CXXFLAGS) -lstdc++fs -o $@

lsof: lsof.cpp utils.cpp
	$(CXX) lsof.cpp utils.cpp $(CXXFLAGS) -lstdc++fs -o $@

hide_arg: hide_arg.cpp
	$(CXX) hide_arg.cpp $(CXXFLAGS) -o $@