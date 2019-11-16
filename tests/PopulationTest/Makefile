.PHONY: all

CC = clang++ -g -O0
CFLAGS = -Wall -Werror -std=c++11
SRC1 = ../../src/Input.cpp
SRC2 = ../../src/Individual.cpp
SRC3 = ../../src/lib.cpp
SRC4 = ../../src/Population.cpp
SRC5 = PopulationTest.cpp
EXE = PopulationTest

all: $(EXE)


$(EXE): $(SRC1) $(SRC2) $(SRC3) $(SRC4) $(SRC5)
	$(CC) $(CFLAGS) $^ -o $@

clean:
	rm $(EXE) 
