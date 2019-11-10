#include <iostream>
#include <random> 
#include "Individual.hpp"
#include "lib.hpp"

using namespace std;

Individual::Individual(unsigned int iHeight, unsigned int iWidth, Input input){
    height = iHeight;
    width = iWidth;
    vector <vector <bool>> matrix = input.getMatrix();

    std::random_device prob;
    std::mt19937 mt(prob());
    std::uniform_int_distribution<int> cameraSetting(0, 1);

    for(unsigned int i = 0; i < height; i++) {
        vector <Point> row;
        for(unsigned int j = 0; j < width; j++){
            Point point;
            point.room = matrix[i][j];
            point.numberOfCameras = cameraSetting(mt);    //0 or 1 here
            point.camera = 0;                             //will be set later
            row.push_back(point);
        }
        arrangement.push_back(row);
    }


    //cameras view (increment for points)
    // for(unsigned int i = 0; i < height; i++) {
    //     for(unsigned int j = 0; j < width; j++){
    //         if(){

    //         }
    //     }
    // }
}

// void calculateFitness(){

// }

// void completeArrangement(){

// }

// void crossover(Individual individual){

// }

// void mutation(){

// }

// void displayCamerasCoordinates(){

// }