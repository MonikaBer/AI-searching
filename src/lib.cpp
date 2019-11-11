#include <math.h>
#include "lib.hpp"

float pointsDistance(int x, int y, int i, int j){
    return sqrt(pow(i-x,2) + pow(j-y,2));
}