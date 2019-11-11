#include <iostream>
#include <fstream>
#include "Individual.hpp"
#include "Population.hpp"
#include "Input.hpp"
#include "lib.hpp"

using namespace std;


int main(int argc, char** argv){
    if ( argc != 2 ) {
      cout << "usage: ./main <path to input file>\n";
      return 1;
    }

    ifstream ifs (argv[1]);    

    Input input(ifs);

    return 0;
}


