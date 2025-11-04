//Version 1, 1 November 2025
#include <iostream>
#include <string>
#include <cmath>
using namespace std;

class Target{
    public:
    Target(double bearing, double range, double heading, double speed, double altitude){   //Generate initial target information
        Vsum = speed;
        beta = (450 - bearing)*(M_PI/180); //heading to target in rad
        alpha = (450 - heading)*(M_PI/180); //target heading in rad
        epsilon = atan2(altitude, range); 
        range_ground = range*1000;
        height = altitude*1000;               
        range_slant = sqrt(pow(range, 2) + pow(altitude, 2))*1000;
        X = range_ground*cos(beta);
        Y = range_ground*sin(beta);
        Vx = speed*cos(alpha);
        Vy = speed*sin(alpha);      
    }
    void move(double t){X += Vx*t; Y += Vy*t;}//move target along XY-plane
    double getBeta(){return beta;}
    double getEpsilon(){return epsilon;}
    double getX(){return X;}
    double getY(){return Y;}
    double getZ(){return height;}
    private:
    double range_ground, range_slant, range_cross, height, X, Y, Vsum, Vx, Vy, Vz;
    double beta, epsilon, betaReciprocal, alpha, theta, Rmax;
};