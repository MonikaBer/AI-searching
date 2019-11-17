#include <iostream>
#include "Input.hpp"
#include "Individual.hpp"

using namespace std;

Input::Input(istream & in){
    string str;
    int counter = 0;                //how much points is in the room
    
    in >> radius;
    in.get();
    in >> minNumberOfCameras;
    in.get();
    in >> height;
    in.get();
    in >> width;
    in.get();

    Individual::height = height;
    Individual::width = width;
    Individual::radius = radius;
    Individual::minNumberOfCameras = minNumberOfCameras;
    
    for(int i = 0; i < height; i++){
        vector<bool> row;
        getline(in, str);
        for(int j = 0; j < width; j++){
            if(str[j] == '0') {
                row.push_back(false);
            } else if (str[j] == '1') {
                row.push_back(true);
                counter++;
            } else {
                throw "Incorrect file format";
            } 
        }
        matrix.push_back(row);
    }


    Individual::roomSurface = counter;    
}

void Input::displayMatrix(){
    for(int i = 0; i < this->height; i++){
        for(int j = 0; j < this->width; j++){
            if (this->matrix[i][j] == true)  cout << "1";
            else cout << "0";
        }
        cout << "\n";
    }
}

//getters
int Input::getHeight(){
    return this->height;
}

int Input::getWidth(){
    return this->width;
}

int Input::getRadius(){
    return this->radius;
}

int Input::getMinNumberOfCameras(){
    return this->minNumberOfCameras;
}

vector <vector <bool>> Input::getMatrix(){
    return this->matrix;
}