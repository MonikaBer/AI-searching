#include <iostream>
#include "../../src/Individual.hpp"
#include "../../src/lib.hpp"
#include "../../src/Input.hpp"
#include "../../src/Population.hpp"

using namespace std;

#define INPUT_PATH "../input"


//tests
void PopulationTest(){
    ifstream ifs (INPUT_PATH);    
    Input input(ifs);

	Population population(100,50,input);
}

int main(){
    cout << "\n--------------------POPULATION_TEST--------------------\n";

    cout << "POPULATION'S CONSTRUCTOR TEST\n\n";
    PopulationTest();

    return 0;
}
