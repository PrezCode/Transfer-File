#include <iostream>
#include <string>
#include <cmath>
#include <math.h>
using namespace std;

class Target{
    public:
    Target(int bearing, int range, int heading, int speed, int altitude){
    }
    double getBeta() const {
        return beta;
    }
    double getEpsilon() const {
        return epsilon;
    }
    int getHeight() const {
        return height;
    }
    int getRange() const {
        return range_ground;
    }
    int getSlant() const {
        return range_slant;
    }
    private:
    int beta, epsilon, range_ground, range_slant, velocity, height;
};