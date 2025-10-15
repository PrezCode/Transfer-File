#include <iostream>
#include <string>
#include <cmath>
#include <math.h>
using namespace std;

class Missile{
    public:
    Missile(int bearing, int distance){ //Generate a missile's launch location based on random input variables
        beta = -bearing*(M_PI/180);
        Z = 0;
        epsilon = atan2(Z, distance);
        X = distance*sin(beta);
        Y = distance*cos(beta);
    }
    private:
    int X, Y, Z;
    double beta, epsilon;
};