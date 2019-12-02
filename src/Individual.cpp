#include <iostream>
#include <random>
#include <functional>
#include "Individual.hpp"
#include "lib.hpp"

using namespace std;

int Individual::height;
int Individual::width;
int Individual::radius;
int Individual::minNumberOfCameras;
int Individual::roomSurface;
vector<CameraView> Individual::camerasViews;


Individual::Individual(Input & input){
    vector<vector<bool>> matrix = input.getMatrix();

    std::random_device prob;
    std::mt19937 mt(prob());
    std::uniform_int_distribution<int> cameraSetting(0, 1);
    int isCamera;
    camerasNumber = 0;

    for(int i = 0; i < height; i++) {
        vector<Point> row;
        for(int j = 0; j < width; j++){
            Point point;
            point.room = matrix[i][j];

            if(point.room == true) {
                isCamera = cameraSetting(mt);
                if(isCamera == 1) {
                    point.camera = true;
                    camerasNumber++;
                } else {
                    point.camera = false;
                }
            } else  point.camera = false;

            point.numberOfCameras = 0;  //will be set later
            row.push_back(point);
        }
        arrangement.push_back(row);
    }

    //cameras view (increment for points)
    int cameraNr = 1;
    for(int i = 0; i < height; i++) {
        for(int j = 0; j < width; j++) {
            if(arrangement[i][j].room == true) {
                if(arrangement[i][j].camera == true)
                    this->cameraSettingView(cameraNr);
                cameraNr++;
            }
        }
    }

    this->fitness.push_back(0.0);
    this->fitness.push_back(0.0);
    this->calcFitness();
}

Individual::Individual() {}

void Individual::cameraSettingView()
{
	int cameraNr = 1;
    for(int i = 0; i < height; i++) {
        for(int j = 0; j < width; j++) {
            if(arrangement[i][j].room == true) {
                if(arrangement[i][j].camera == true)
                    this->cameraSettingView(cameraNr);
                cameraNr++;
            }
        }
    }
}

void Individual::cameraSettingView(int cameraNr) {
	for(int i = 0; i < this->height; i++) {
        for(int j = 0; j < this->width; j++) {
            this->arrangement[i][j].numberOfCameras += this->camerasViews[cameraNr-1].view[i][j];
        }
    }
}

void Individual::calcFitness() {  //think of changing target function
    float firstCondition = 0.0;
    for(int i = 0; i < this->height; i++) {
        for(int j = 0; j < this->width; j++) {
            if(this->arrangement[i][j].room == true && this->arrangement[i][j].numberOfCameras >= this->minNumberOfCameras)
                firstCondition++;
        }
    }

    firstCondition /= (float)(this->roomSurface);
    this->fitness[0] = firstCondition;             //first condition -> how much room points is saw by min number of cameras

    this->fitness[1] = (float)this->camerasNumber;        //second condition -> individual with lower number of cameras is better
}

void Individual::cleanNumberOfCamerasForEachPoint() {
	for(int i = 0; i < this->height; i++) {
        for(int j = 0; j < this->width; j++) {
            this->arrangement[i][j].numberOfCameras = 0;
        }
    }
}

void Individual::clearCameras(){
	for(int i = 0; i < this->height; i++) {
        for(int j = 0; j < this->width; j++) {
            this->arrangement[i][j].camera = false;
        }
    }
}

void Individual::findCameraCoordinates(int cameraNumber, int & x, int & y) {
    int counter = 0;
    for(int i = 0; i < this->height; i++) {
        for(int j = 0; j < this->width; j++) {
            if(this->arrangement[i][j].camera == true) {
                counter++;
                if(counter == cameraNumber) {
                    x = i;
                    y = j;
                    return;
                }
            }
        }
    }

    throw "Number of cameras in Individual is calculated invalidly";
}

Individual Individual::crossover(Individual & secondParent) {
    int x, y;
    int parentNumber, cameraNumber;
    vector<Point2d> camerasToCrossover;                //cameras' coordinates
    
    std::random_device prob;
    std::mt19937 mt(prob());
    std::uniform_int_distribution<int> whichParent(1,2);
    
    Individual offspring;
    //a greater part of arrangement from parent who will be selected in drawing
    if(whichParent(mt) == 1) {
        offspring.setArrangementAndCamerasNumber(this->arrangement, this->camerasNumber);
        parentNumber = 1;
    } else {
        offspring.setArrangementAndCamerasNumber(secondParent.getArrangement(), secondParent.getCamerasNumber());
        parentNumber = 2;
    }

    std::random_device prob2;
    std::mt19937 mt2(prob2());
    std::uniform_int_distribution<int> whichCamera1(1, this->camerasNumber);
    
    std::random_device prob3;
    std::mt19937 mt3(prob3());
    std::uniform_int_distribution<int> whichCamera2(1, secondParent.camerasNumber);
	
    //draw cameras to crossover
    for(int k = 0; k < CAMERAS_TO_CROSSOVER; k++) {                
		if(whichParent(mt) == 1) {                                        //camera is draw from parent1
			cameraNumber = whichCamera1(mt2);                             //draw camera number to crossover
			this->findCameraCoordinates(cameraNumber, ref(x), ref(y));
            if(secondParent.arrangement[x][y].camera == true) {           //both parents have got this camera
                offspring.arrangement[x][y].camera = true;
            } else {                                                      // secondParent hasn't got this camera
                offspring.arrangement[x][y].camera = false;
            }
		}
		else {                                                                    //camera is draw from parent2
			cameraNumber = whichCamera2(mt3);                                    //draw camera number to crossover
			secondParent.findCameraCoordinates(cameraNumber, ref(x), ref(y));
            if(this->arrangement[x][y].camera == true) {                         //first parent has got this camera too
                offspring.arrangement[x][y].camera = true;
            } else {                                                             //first parent hasn't got this camera
                offspring.arrangement[x][y].camera = false;
            }
        }
    }
	
	offspring.cleanNumberOfCamerasForEachPoint();
	offspring.camerasNumber = 0;
	
    int cameraNr = 1;
	for(int i = 0; i < offspring.height; i++) {
        for(int j = 0; j < offspring.width; j++) {
            if(offspring.arrangement[i][j].room == true) {
                if(offspring.arrangement[i][j].camera == true) {
                    offspring.camerasNumber++;
                    offspring.cameraSettingView(cameraNr);
                }
                cameraNr++;
            }   
        }
    }

	return offspring;
}

Individual Individual::randomCrossover() {
    Individual offspring;
    offspring.setArrangementAndCamerasNumber(this->arrangement, this->camerasNumber);
    
    srand(time(NULL));
	for(int i = 0; i < this->height; i++) {
        for(int j = 0; j < this->width; j++) {
			if(rand()%2 == 0)  //camera setting from "this" parent
				offspring.arrangement[i][j].camera = this->arrangement[i][j].camera;
			else
				offspring.arrangement[i][j].camera = false;
        }
    }

	offspring.cleanNumberOfCamerasForEachPoint();
	offspring.camerasNumber = 0;

    int cameraNr = 1;
	for(int i = 0; i < offspring.height; i++) {
        for(int j = 0; j < offspring.width; j++) {
            if(offspring.arrangement[i][j].room == true) {
                if(offspring.arrangement[i][j].camera == true) {
                    offspring.camerasNumber++;
                    offspring.cameraSettingView(cameraNr);
                }
                cameraNr++;
            }   
        }
    }

	return offspring;
}

Individual Individual::newRandomIndividual() {
    Individual offspring;
    offspring.setArrangementAndCamerasNumber(this->arrangement, this->camerasNumber);

    srand(time(NULL));
	for(int i = 0; i < this->height; i++) {
        for(int j = 0; j < this->width; j++) {
			if(rand()%2 == 0)  //camera isn't here
				offspring.arrangement[i][j].camera = false;
			else //camera is here
				offspring.arrangement[i][j].camera = true;
        }
    }

    offspring.cleanNumberOfCamerasForEachPoint();
	offspring.camerasNumber = 0;

    int cameraNr = 1;
	for(int i = 0; i < offspring.height; i++) {
        for(int j = 0; j < offspring.width; j++) {
            if(offspring.arrangement[i][j].room == true) {
                if(offspring.arrangement[i][j].camera == true) {
                    offspring.camerasNumber++;
                    offspring.cameraSettingView(cameraNr);
                }
                cameraNr++;
            }   
        }
    }

    return offspring;
}

void Individual::mutation(int populationSize) {
    int pointNumber, counter = 0;

    std::random_device prob;
    std::mt19937 mt(prob());
    std::uniform_int_distribution<int> ifMutation(1, populationSize);

    // (1/populationSize) -> probability of mutation
    if(ifMutation(mt) == 1) {                               //mutation
        std::random_device prob2;
        std::mt19937 mt2(prob2());
        std::uniform_int_distribution<int> whichRoomPoint(1, this->roomSurface);
        pointNumber = whichRoomPoint(mt2);

        for(int i = 0; i < this->height; i++) {
            for(int j = 0; j < this->width; j++) {
                if(this->arrangement[i][j].room == true) {
                    counter++;
                    if(counter == pointNumber) {
                        if(this->arrangement[i][j].camera == true) {
                            this->arrangement[i][j].camera = false;
                            this->camerasNumber--;
                        } else {
                            this->arrangement[i][j].camera = true;
                            this->camerasNumber++;
                        }
                        this->cleanNumberOfCamerasForEachPoint();

                        i = this->height;
                        j = this->width;
                    }
                }
            }
        }
    } else {               //without mutation
        return;
    }

    //set cameras' view (increment for room points)
    int cameraNr = 1;
	for(int i = 0; i < this->height; i++) {
        for(int j = 0; j < this->width; j++) {
            if(this->arrangement[i][j].room == true) {
                if(this->arrangement[i][j].camera == true) {
                    this->cameraSettingView(cameraNr);
                }
                cameraNr++;
            }   
        }
    }

}


//helpers

void Individual::displayRoomAppearance() {
    for(int i = 0; i < this->height; i++) {
        for(int j = 0; j < this->width; j++) {
            cout << this->arrangement[i][j].room;
        }
        cout << "\n";
    }
}

void Individual::displayHowManyCamerasForEachPoint() {
    for(int i = 0; i < this->height; i++) {
        for(int j = 0; j < this->width; j++) {
            cout << this->arrangement[i][j].numberOfCameras << "\t";
        }
        cout << "\n";
    }
}

void Individual::displayWhereCamerasAre() {
    for(int i = 0; i < this->height; i++) {
        for(int j = 0; j < this->width; j++) {
            cout << this->arrangement[i][j].camera;
        }
        cout << "\n";
    }
}

void Individual::displayCamerasCoordinates() {
    int counter = 1;
    for(int i = 0; i < this->height; i++) {
		for(int j = 0; j < this->width; j++) {
			if(this->arrangement[i][j].camera == true) {
				cout << "\tCamera " << counter << ": (" << i << ", " << j << ")\n";
				counter++;
			}
		}
	}
}


//getters

int Individual::getCamerasNumber() {
    return this->camerasNumber;
}

vector<vector<Point>> Individual::getArrangement() {
    return this->arrangement;
}

vector<float> Individual::getFitness() {
    return this->fitness;
}


//setters
void Individual::setCamera(int rowNumber, int columnNumber){
	this->arrangement[rowNumber][columnNumber].camera = true;
}

void Individual::setArrangementAndCamerasNumber(vector<vector<Point>> parentArrangement, int parentCamerasNumber){
    this->arrangement = parentArrangement;
    this->camerasNumber = parentCamerasNumber;

    this->fitness.push_back(0.0);
    this->fitness.push_back(0.0);
}
