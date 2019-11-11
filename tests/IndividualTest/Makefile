.PHONY: all

CC = clang++ -g -O0
CFLAGS = -Wall -Werror -std=c++11
SRC1 = ../../src/Input.cpp
SRC2 = ../../src/Individual.cpp
SRC3 = ../../src/lib.cpp
SRC4 = IndividualTest.cpp
EXE = IndividualTest

all: $(EXE)


$(EXE): $(SRC1) $(SRC2) $(SRC3) $(SRC4)
	$(CC) $(CFLAGS) $^ -o $@

clean:
	rm $(EXE) 
