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
		
		Individual offspring = this->population[i].crossover(this->population[secondParentNumber]);
		offspring.mutation(this->size);
		offspring.calcFitness();
		this->population.push_back(offspring);
	}
}  

void Population::orderPopulation(){
	sort(this->population.begin(), this->population.end(), [](const Individual & a, const Individual & b) {return a.fitness > b.fitness;});
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
	cout << "\nIndividual fitness: " << this->population[0].getFitness() << endl;
}

