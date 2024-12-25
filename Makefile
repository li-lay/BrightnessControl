# Compiler
CXX = g++
# Compiler flags
CXXFLAGS = -Wall -std=c++17
# Target executable
TARGET = BrightnessControl
# Source files
SRCS = main.cpp monitor.cpp menu.cpp
# Header files (for dependency tracking)
HDRS = monitor.h menu.h
# Object files
OBJS = $(SRCS:.cpp=.o)
# Install path
PREFIX = /usr/local/bin

# Default rule to build the target
all: $(TARGET)

# Rule to link the object files and create the executable
$(TARGET): $(OBJS)
		$(CXX) $(CXXFLAGS) -o $@ $^

# Rule to compile source files into object files
%.o: %.cpp $(HDRS)
		$(CXX) $(CXXFLAGS) -c $< -o $@

# Rule to install the executable
install: $(TARGET)
		sudo install -m 755 $(TARGET) $(PREFIX)/$(TARGET)

# Rule to clean up the build files
clean:
		rm -f $(OBJS) $(TARGET)

.PHONY: all install clean
