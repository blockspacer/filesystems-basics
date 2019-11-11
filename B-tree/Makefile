CXX = g++
TARGET = tree
CXX_FLAGS = -std=c++11 -Wall

all: $(TARGET)

$(TARGET): main.cpp tree.cpp
	$(CXX) $(CXX_FLAGS) $^ -o $@

clean:
	rm $(TARGET) dumpFile.gv dumpFile.png