# File Names
EXEC = sysprogramming
SOURCES =$(wildcard src/*.cpp)
OBJECTS = $(SOURCES:.cpp=.o)

# Compiler Variables
CC = clang++
CC_FLAGS = -std=c++11 -g -Wall -pedantic -I include

# Main target
$(EXEC): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(EXEC)

# To obtain object files
%.o: %.cpp
	$(CC) -c $(CC_FLAGS) $< -o $@

# To remove generated files
clean:
	rm -f $(EXEC) $(OBJECTS)
