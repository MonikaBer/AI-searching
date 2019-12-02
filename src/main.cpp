#include <iostream>
#include <fstream>
#include <functional>
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

    ifstream ifs(argv[1]);    

    Input input(ifs); 
    Population population(input);
    
    for(int i = 0; i < GENERATIONS_NUMBER; i++){
		population.createNewGeneration();
        //now, population is 100 % greater than old population so we have to destroy the worst individuals
        population.orderPopulation();
        population.cutPopulation();
    }

    population.displayTheBest();

    return 0;
}


