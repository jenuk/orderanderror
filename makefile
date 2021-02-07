CXX := g++
CXXFLAGS := --std=c++17 -Wall -Wextra

RES = image

MAIN = main.cpp
HEADER = image.h node.h graph.h

OBJ = $(HEADER:%.h=build/%.o)

.PHONY: clean

imgs/$(RES).png: main
	./main | pnmtopng > imgs/$(RES).png

main: $(MAIN) $(OBJ)
	$(CXX) $(CXXFLAGS) $(OBJ) $(MAIN) -o main


# assumes .h for every .cpp
$(OBJ):build/%.o: src/%.cpp header/%.h
	$(CXX) $(CXXFLAGS) -c $< -o $@


clean:
	-rm build/*.o 
	-rm main
