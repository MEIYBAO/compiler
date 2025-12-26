CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -Iinclude

SRC_DIR = src
OBJS = $(SRC_DIR)/parser.o $(SRC_DIR)/scanner.o $(SRC_DIR)/ast.o $(SRC_DIR)/semantic.o $(SRC_DIR)/ir.o $(SRC_DIR)/optimizer.o $(SRC_DIR)/codegen.o $(SRC_DIR)/main.o

all: minic

$(SRC_DIR)/parser.cpp $(SRC_DIR)/parser.hpp: $(SRC_DIR)/parser.y
	bison -d --defines=$(SRC_DIR)/parser.hpp -o $(SRC_DIR)/parser.cpp $(SRC_DIR)/parser.y

$(SRC_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

minic: $(OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@

.PHONY: clean
clean:
	rm -f $(SRC_DIR)/parser.cpp $(SRC_DIR)/parser.hpp $(SRC_DIR)/scanner.cpp $(OBJS) minic
