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


int main(){
    cout << "\n--------------------INDIVIDUAL_TEST--------------------\n";

    cout << "INDIVIDUAL'S CONSTRUCTOR TEST\n\n";
    IndividualTest();

    return 0;
}
