#include <iostream>
#include <random> 
#include "Population.hpp"


Population::Population(int pSize, int parSize, Input input) {
    populationSize = pSize;
	parentsNumber = parSize;

    for (int i = 0; i < populationSize; i++) {
       population.push_back(Individual(input));
    }
	
	for (int i = 0; i < parentsNumber; i++) {
       parents.push_back(population[i]);
    }
}

// void calculateFitnessForIndividuals() {

// }
   
// void selection() {

// }

void Population::crossover(){
	for(int i = 0; i < parentsNumber; i++)
	{
		int second_parents_number;
		
		if(i == parentsNumber -1)	second_parents_number = 0;
		else	second_parents_number = i;
		
		Individual child = parents[i].crossover(parents[second_parents_number]);
		
		
	}
}   

void checkTheBestIndividual(TheBest theBestIndividual){

}