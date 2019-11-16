#include <vector>
#include "Individual.hpp"

#ifndef POPULATION_HPP
#define POPULATION_HPP


struct TheBest {
    int individualID;  //the best invidual's index in generation
    int fitness;       //number of cameras in the best individual
};

class Population {
private:    
    int populationSize;
	int parentsNumber;
    std::vector<Individual> population;
    std::vector<Individual> parents;

public:
    Population(int ,int ,Input);
    void calculateFitnessForIndividuals();
    void selection();                                       //select individuals for crossover 
    void crossover();                                       //new generation creation
    void checkTheBestIndividual(TheBest);
    
    //getters:
};


#endif
