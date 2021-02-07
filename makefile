CXX := g++
CXXFLAGS := --std=c++17 -Wall -Wextra

SRC_DIR := src
BUILD_DIR := build
HEADER_DIR := header

RES := image
MAIN := main.cpp
EXEC := build/main

SRCS := $(shell ls src/*.cpp)
OBJ := $(SRCS:$(SRC_DIR)/%.cpp=$(BUILD_DIR)/%.o)
DEPS := $(OBJ:%.o=%.d)
HEADER_FLAG := -I$(HEADER_DIR)


imgs/$(RES).png: $(EXEC)
	$(EXEC) | pnmtopng > imgs/$(RES).png


$(EXEC): $(MAIN) $(OBJ)
	$(CXX) $(CXXFLAGS) $(HEADER_FLAG) $(OBJ) $(MAIN) -o $(EXEC)


$(OBJ):$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) $(HEADER_FLAG) -MMD -c $< -o $@


.PHONY: clean
clean:
	-rm build/*.o 
	-rm build/*.d 
	-rm $(EXEC)


-include $(DEPS)
