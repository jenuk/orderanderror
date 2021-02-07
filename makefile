CXX := g++
CXXFLAGS := --std=c++17 -Wall -Wextra

SRC_DIR := src
BUILD_DIR := build
HEADER_DIR := header

RES := image
MAIN := main.cpp
EXEC := build/main

SRCS := $(shell ls $(SRC_DIR)/*.cpp)
OBJ := $(SRCS:$(SRC_DIR)/%.cpp=$(BUILD_DIR)/%.o)
DEPS := $(OBJ:%.o=%.d)
HEADER_FLAG := -I$(HEADER_DIR)

.PHONY: image clean

image: $(EXEC)
	$(EXEC) 
	pnmtopng imgs/image.ppm > imgs/$(RES).png
	rm imgs/image.ppm


$(EXEC): $(MAIN) $(OBJ)
	$(CXX) $(CXXFLAGS) $(HEADER_FLAG) $(OBJ) $(MAIN) -o $(EXEC)


$(OBJ):$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) $(HEADER_FLAG) -MMD -c $< -o $@


clean:
	-rm $(BUILD_DIR)/*.o 
	-rm $(BUILD_DIR)/*.d 
	-rm $(EXEC)


-include $(DEPS)
