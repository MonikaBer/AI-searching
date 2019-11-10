#include <iostream>
#include <random> 
#include "Population.hpp"


Population::Population(unsigned int pSize, unsigned int  iHeight, unsigned int iWidth) {
    populationSize = pSize;

    for (unsigned int i = 0; i < populationSize; i++) {
       //population.push_back(Individual(iHeight, iWidth));
    }
}

// void calculateFitnessForIndividuals() {

// }
   
// void selection() {

// }

// void crossover(){

// }   

void checkTheBestIndividual(TheBest theBestIndividual){

}