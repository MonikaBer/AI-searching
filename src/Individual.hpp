#include <vector>
#include "Input.hpp"

#ifndef INDIVIDUAL_HPP
#define INDIVIDUAL_HPP

struct Point {
    bool room;            		  	//false - point beyond the room, true - point in the room
    int numberOfCameras;   	      //number of cameras which see the point
    bool camera;           			  //true - camera is here, false - lack of camera
};

struct CameraView {
    int height;
    int width;
    std::vector<std::vector<int>> view;                 //camera's view
};

class Individual {
private:
    std::vector<std::vector<Point>> arrangement;        //arrangement
    std::vector<float> fitness;                     	            //fitness function
    int camerasNumber;                                  //how much cameras individual has got
public:
    static int height;                                  //matrix's height
    static int width;                       	          //matrix's width
    static int radius;                                  //defines camera's view
    static int minNumberOfCameras;
    static int roomSurface;                             //how much points is in the room
    static std::vector<CameraView> camerasViews;           //possible cameras' views

public:
    Individual(Input &);
    Individual();
	void cameraSettingView();                           //setting camera visibility for every point in all cameras' viewes
    void cameraSettingView(int);                   //setting camera visibility for every point in cameras' view
	  void cleanNumberOfCamerasForEachPoint();		      	//set numberOfCameras of every pool on 0
	  void clearCameras();	                             	//delete all cameras in the room
	bool doesItMeetRequierments();
    void findCameraCoordinates(int, int &, int &);
    Individual crossover(Individual &);
    Individual randomCrossover(Individual &);
    Individual randomCrossover();
    Individual newRandomIndividual();
    bool isCornerOnLine(int,int,int,int);		            //check is there a corner between two point
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
    std::vector<float> getFitness();

    //setters:
	void setCamera(int,int);
    void setArrangement(std::vector<std::vector<Point>>);

    friend class Population;
};

#endif
