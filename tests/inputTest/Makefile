.PHONY: all

CC = clang++ -g -O0
CFLAGS = -Wall -Werror -std=c++11
SRC1 = ../../src/Input.cpp
SRC2 = inputTest.cpp
EXE = inputTest

all: $(EXE)


$(EXE): $(SRC1) $(SRC2)
	$(CC) $(CFLAGS) $^ -o $@

clean:
	rm $(EXE) 
