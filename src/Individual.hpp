#include <vector>
#include "Input.hpp"

#ifndef INDIVIDUAL_HPP
#define INDIVIDUAL_HPP

struct Point {
    bool room;             //false - point beyond the room, true - point in the room
    int numberOfCameras;   //number of cameras which see the point
    bool camera;           //true - camera is here, false - lack of camera
};


class Individual {
private:    
    unsigned int height;                      //matrix's height
    unsigned int width;                       //matrix's width
    std::vector <std::vector <Point>> arrangement;       //arrangement 
    unsigned int fitness;                     //fitness function

public:
    Individual(unsigned int, unsigned int, Input);
    void calculateFitness(); 
    void completeArrangement();
    void crossover(Individual);
    void mutation();
    void displayCamerasCoordinates();
    //getters:
    
    //setters:      

    friend class Population;
};

#endif