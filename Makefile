# Defines

CXX = g++
CXXFLAGS = -Wall
SRC = src/*.cpp src/ciphers/*.cpp 
BIN_NAME = peaked

# Conf

.RECIPEPREFIX = ~

# Rules

binary:
~ $(CXX) $(CXXFLAGS) -o $(BIN_NAME) $(SRC)