# Compiler settings
CXX := g++
CXXFLAGS := -std=c++17 -Wall -Wextra -I.
LDFLAGS := 

# Project files
SRCS := main.cpp HeapAlloc.cpp
OBJS := $(SRCS:.cpp=.o)
HEADERS := HeapAlloc.hpp
TARGET := heap_allocator

# Build rules
all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(LDFLAGS) $^ -o $@

%.o: %.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean rule
clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean
