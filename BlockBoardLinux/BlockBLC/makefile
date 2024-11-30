# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++17 -Wall
LDFLAGS = -lX11 -pthread

# Source files and object files
SRC = $(wildcard *.cpp)
OBJ = $(SRC:.cpp=.o)

# Output executable name
TARGET = BlockBL

# Default target
all: $(TARGET)

# Rule for linking the target
$(TARGET): $(OBJ)
	@echo "Linking $@ from $^"
	$(CXX) $(OBJ) -o $(TARGET) $(LDFLAGS)

# Rule for compiling .cpp to .o
%.o: %.cpp
	@echo "Compiling $< to $@"
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean rule to remove object files and the target executable
clean:
	@echo "Cleaning up..."
	rm -f $(OBJ) $(TARGET)

# Optional: Define a target to run the program
run: $(TARGET)
	./$(TARGET)

# Optional: Install the binary (adjust as needed)
install: $(TARGET)
	sudo cp $(TARGET) /usr/local/bin/

.PHONY: all clean run install
