#include "Individual.hpp"

#ifndef LIB_HPP
#define LIB_HPP

#define MUTATION_PROBABILITY              10
#define GENERATIONS_NUMBER                50
#define CAMERAS_TO_CROSSOVER              2
#define POPULATION_SIZE                   200
//#define PROBABILITY_OF_CAMERA_SETTING   50      //in percents

struct Point2d {
    int x;
    int y;
};

float pointsDistance(int, int, int, int);  //distance between two points
void cameraSettingView(CameraView &, int, int, int, std::vector<std::vector<bool>>);
bool isCornerOnLine(int, int, int, int, std::vector<std::vector<bool>>);

#endif
