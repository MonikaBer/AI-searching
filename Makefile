.PHONY: all

CC = clang++ -g -O0
CFLAGS = -Wall -Werror -std=c++11
SRC1 = src/Individual.cpp
SRC2 = src/Population.cpp
SRC3 = src/lib.cpp
SRC4 = src/main.cpp
EXE = main

all: $(EXE)


$(EXE): $(SRC1) $(SRC2) $(SRC3) $(SRC4)
	$(CC) $(CFLAGS) $^ -o $@

clean:
	rm $(EXE) 