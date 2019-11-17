#include <vector>
#include "Input.hpp"

#ifndef INDIVIDUAL_HPP
#define INDIVIDUAL_HPP

struct Point {
    bool room;            		  	//false - point beyond the room, true - point in the room
    int numberOfCameras;   	        //number of cameras which see the point
    bool camera;           			//true - camera is here, false - lack of camera
};


class Individual {
private:    
    std::vector<std::vector<Point>> arrangement;        //arrangement 
    float fitness;                     	                //fitness function
    int camerasNumber;                                  //how much cameras individual has got
public:
    static int height;                                  //matrix's height
    static int width;                       	        //matrix's width 
    static int radius;                                  //defines camera's view
    static int minNumberOfCameras;
    static int roomSurface;                             //how much points is in the room
 
public:
    Individual(Input &);
    Individual();
    void cameraSettingView(int, int);                   //setting camera visibility for every point in cameras' view
	void cleanNumberOfCamerasForEachPoint();			//set numberOfCameras of every pool on 0            
    void findCameraCoordinates(int, int &, int &);           
    Individual crossover(Individual &);
    void mutation(int);
    void calcFitness(); 

    //helpers
    void displayRoomAppearance();
    void displayHowManyCamerasForEachPoint();
    void displayWhereCamerasAre();
    void displayCamerasCoordinates();

    //getters
    int getCamerasNumber();
    std::vector<std::vector<Point>> getArrangement();
    float getFitness();

    //setters:
    void setArrangementAndCamerasNumber(std::vector<std::vector<Point>>, int);

    friend class Population;
};

#endif