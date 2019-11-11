#include <iostream>
#include "../../src/Input.hpp"

using namespace std;

#define INPUT_PATH "../input"


//tests
void inputTest(){
    ifstream ifs (INPUT_PATH);    
    Input input(ifs);
    cout << "Matrix's height: " << input.getHeight();
    cout << "\nMatrix's width: " << input.getWidth();
    cout << "\nCamera's radius: " << input.getRadius();
    cout << "\nMinimum number of cameras which see every point: " << input.getMinNumberOfCameras() << "\n\n";
    input.displayMatrix();
}


int main(){
    cout << "\n--------------------INPUT_TEST--------------------\n";

    cout << "INPUT'S CONSTRUCTOR TEST\n\n";
    inputTest();

    return 0;
}
