#include <vector>
#include "Individual.hpp"

#ifndef POPULATION_HPP
#define POPULATION_HPP


struct TheBest {
    unsigned int individualID;  //the best invidual's index in generation
    unsigned int fitness;       //number of cameras in the best individual
};

class Population {
private:    
    unsigned int populationSize;
    std::vector<Individual> population;
    std::vector<Individual> parents;

public:
    Population(unsigned int , unsigned int, unsigned int);
    void calculateFitnessForIndividuals();
    void selection();                                       //select individuals for crossover 
    void crossover();                                       //new generation creation
    void checkTheBestIndividual(TheBest);
    
    //getters:
};


#endif
