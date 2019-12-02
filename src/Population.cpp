#include <iostream>
#include <random> 
#include <functional>
#include <algorithm>
#include "Population.hpp"

using namespace std;

Population::Population(Input & input) {
    for (int i = 0; i < size; i++) {
       population.push_back(Individual(input));
    }   
}

void Population::createNewGeneration(){
	int secondParentNumber;

	random_shuffle(this->population.begin(), this->population.end()); 
	
	for(int i = 0; i < this->size; i++) {
		
		if(i == this->size-1)  secondParentNumber = 0;
		else	               secondParentNumber = i+1;
		
		Individual offspring;
		//the next, think of changing "offspring =" below
		if(this->population[i].getCamerasNumber() != 0 && this->population[secondParentNumber].getCamerasNumber() != 0) {
			offspring = this->population[i].crossover(this->population[secondParentNumber]);   
		} else if(this->population[i].getCamerasNumber() == 0 && this->population[secondParentNumber].getCamerasNumber() != 0) {
			offspring = this->population[secondParentNumber].randomCrossover();                
		} else if(this->population[i].getCamerasNumber() != 0 && this->population[secondParentNumber].getCamerasNumber() == 0) {
			offspring = this->population[i].randomCrossover();
		} else {            //both parents haven't got any cameras
			offspring = this->population[i].newRandomIndividual();
		}

		offspring.mutation(this->size);
		offspring.calcFitness();
		this->population.push_back(offspring);
	}
}  

void Population::orderPopulation(){
	sort(this->population.begin(), this->population.end(), [](const Individual & a, const Individual & b) {
		if(a.fitness[0] > b.fitness[0]) return false;
		else if (a.fitness[0] < b.fitness[0])  return true;
		else if (a.fitness[1] <= b.fitness[1])  return false;
		else  return true;    
	});
}

void Population::cutPopulation(){
	for(int i = 0; i < this->size; i++) {
		this->population.pop_back();
	}
}

void Population::displayTheBest(){
	cout << "\n\nThe best individual:\n\nRoom appearance:\n";
	this->population[0].displayRoomAppearance();
	cout <<"\nHow many cameras see every point:\n";
	this->population[0].displayHowManyCamerasForEachPoint();
	cout << "\nWhere cameras are:\n";
	this->population[0].displayWhereCamerasAre();
	cout << "\nCameras coordinates:\n";
	this->population[0].displayCamerasCoordinates();
	
	vector<float> fitness = this->population[0].getFitness();
	cout << "\nIndividual fitness:\nFirst condition: " << fitness[0] << 
		"\nHow many cameras individual has got: " << fitness[1] << endl;
}

