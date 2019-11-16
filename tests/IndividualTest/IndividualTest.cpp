#include <iostream>
#include "../../src/Individual.hpp"
#include "../../src/lib.hpp"
#include "../../src/Input.hpp"

using namespace std;

#define INPUT_PATH "../input"


//tests
void IndividualTest(){
    ifstream ifs (INPUT_PATH);    
    Input input(ifs);

    Individual individual(input);
    
    cout << "Room appearance:\n"; 
    individual.displayRoomAppearance();

    cout << "\nWhere cameras are:\n";
    individual.displayWhereCamerasAre();

    cout << "\nHow much cameras for each point:\n";
    individual.displayHowMuchCamerasForEachPoint();
}

void IndividualCrossoverTest(){
    ifstream ifs (INPUT_PATH);    
    Input input(ifs);

    Individual individual(input);
	Input input2(ifs);
	
	Individual i1(input);
	Individual i2(input);
	
	Individual child = i1.crossover(i2);
	
	cout << "hmcfep parrent1:" << endl;
	i1.displayHowMuchCamerasForEachPoint();
	cout << "hmcfep parrent2:" << endl;
	i2.displayHowMuchCamerasForEachPoint();
	cout << "hmcfep child:" << endl;
	child.displayHowMuchCamerasForEachPoint();
}

int main(){
    cout << "\n--------------------INDIVIDUAL_TEST--------------------\n";

    cout << "INDIVIDUAL'S CONSTRUCTOR TEST\n\n";
    IndividualTest();
	
	cout << "INDIVIDUAL'S CROSSOVER TEST\n\n";
    IndividualCrossoverTest();

    return 0;
}
