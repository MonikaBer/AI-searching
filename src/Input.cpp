#include <iostream>
#include "Input.hpp"

using namespace std;

Input::Input(istream & in){
    string str;
    
    in >> radius;
    in.get();
    in >> minNumberOfCameras;
    in.get();
    in >> height;
    in.get();
    in >> width;
    in.get();
    
    for(unsigned int i = 0; i < height; i++){
        vector<bool> row;
        getline(in, str);
        for(unsigned int j = 0; j < width; j++){
            if(str[j] == '0')        row.push_back(false);
            else if (str[j] == '1')  row.push_back(true);
            else                     throw "Incorrect file format";
        }
        matrix.push_back(row);
    }
}

void Input::displayMatrix(){
    for(unsigned int i = 0; i < this->height; i++){
        for(unsigned int j = 0; j < this->width; j++){
            if (this->matrix[i][j] == true)  cout << "1";
            else cout << "0";
        }
        cout << "\n";
    }
}

//getters
unsigned int Input::getHeight(){
    return this->height;
}

unsigned int Input::getWidth(){
    return this->width;
}

unsigned int Input::getRadius(){
    return this->radius;
}

unsigned int Input::getMinNumberOfCameras(){
    return this->minNumberOfCameras;
}

vector <vector <bool>> Input::getMatrix(){
    return this->matrix;
}