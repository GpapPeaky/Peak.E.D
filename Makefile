# Defines

CXX = g++
CXXFLAGS = -Wall
SRC = peaky_encrypt_decrypt.cpp 
BIN_NAME = peaked

# Conf

.RECIPEPREFIX = ~

# Rules

binary:
~ $(CXX) $(CXXFLAGS) -o $(BIN_NAME) $(SRC)
