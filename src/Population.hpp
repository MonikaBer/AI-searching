#include <vector>
#include "Individual.hpp"
#include "lib.hpp"

#ifndef POPULATION_HPP
#define POPULATION_HPP


class Population {
private:    
    std::vector<Individual> population;  
public:    
    static const int size = POPULATION_SIZE;         

public:
    Population(Input &);
    void createNewGeneration();          
    void orderPopulation();
    void cutPopulation();
    void displayTheBest();

    //getters:

    //friend class Individual;
};

#endif
