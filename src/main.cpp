#include <iostream>
#include <fstream>
#include "Individual.hpp"
#include "Population.hpp"
#include "Matrix.hpp"
#include "lib.hpp"

using namespace std;

#define PPOULATION_SIZE 100
#define PARENTS_SIZE 30         //in percents


int main(int argc, char** argv){
    if ( argc != 2 ) {
      cout << "usage: ./main <path to input file>\n";
      return 1;
    }

    ifstream ifs (argv[1]);    

    Matrix matrix(ifs);

    return 0;
}


