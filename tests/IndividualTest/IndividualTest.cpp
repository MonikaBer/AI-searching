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
    individual.displayHowManyCamerasForEachPoint();
}

void IndividualCrossoverTest(){
    ifstream ifs (INPUT_PATH);    
    Input input(ifs);

    Individual individual(input);
	Input input2(ifs);
	
	Individual i1(input);
	Individual i2(input);
	
	cout << "hmcfep parrent1:" << endl;
	i1.displayHowManyCamerasForEachPoint();
	cout << "hmcfep parrent2:" << endl;
	i2.displayHowManyCamerasForEachPoint();
	cout << "hmcfep child:" << endl;
	Individual child = i1.crossover(i2);
	child.displayHowManyCamerasForEachPoint();
}

void CornerTest(){
	ifstream ifs ("input2");   
    Input input(ifs);
	Individual i(input);
	i.clearCameras();
	i.cleanNumberOfCamerasForEachPoint();
	i.setCamera(5,4);
	i.cameraSettingView();
	printf("\nWHERE CAMERAS ARE:\n");
	i.displayWhereCamerasAre();
	
	printf("\nHOW MANY CAMERAS:\n");
	i.displayHowManyCamerasForEachPoint();
}

int main(){
    cout << "\n--------------------INDIVIDUAL_TEST--------------------\n";

    cout << "INDIVIDUAL'S CONSTRUCTOR TEST\n\n";
    //IndividualTest();
	
	cout << "INDIVIDUAL'S CROSSOVER TEST\n\n";
    //IndividualCrossoverTest();
	
	cout << "INDIVIDUAL'S CORNER TEST\n\n";
    CornerTest();

    return 0;
}
