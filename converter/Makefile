CXX = g++
TARGET = converter
CXX_FLAGS = -std=c++11 -Wall

all: $(TARGET)

$(TARGET): main.cpp converter.cpp
	$(CXX) $(CXX_FLAGS) $^ -o $@

clean:
	rm $(TARGET)