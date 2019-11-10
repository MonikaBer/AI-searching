#include <iostream>
#include "../../src/Matrix.hpp"

using namespace std;

#define INPUT_PATH "../input"


//tests
void matrixTest(){
    ifstream ifs (INPUT_PATH);    
    Matrix matrix(ifs);
    matrix.displayMatrix();
}


int main(){
    cout << "\n--------------------MATRIX_TEST--------------------\n";

    cout << "MATRIX'S CONSTRUCTOR TEST\n\n";
    matrixTest();

    return 0;
}