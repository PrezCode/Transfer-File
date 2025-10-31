#include <iostream>
#include <string>
#include <cmath>
#include <math.h>
using namespace std;

class Target{
    public:
    Target(double bearing, double range, double heading, double speed, double altitude){   //Generate initial target information
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
        if(beta <= M_PI){betaReciprocal = beta + M_PI;} //Set the recipricol heading of the target
            else{betaReciprocal = beta - M_PI;}
        theta = M_PI/2 - abs(alpha - betaReciprocal);     
    }
    void move(double t){
        X += Vx*t; Y += Vy*t;   //move target along XY-plane
        range_ground = sqrt(X*X + Y*Y); //calculate ground range based on XY-plane coordinates
        range_slant = sqrt(pow(range_ground, 2) + pow(height, 2));  //calculate slant range to target
        beta = -atan2(X, Y); epsilon = atan2(height, range_ground); //generate new beta and epsilon angles based on calculated values
        if(beta <= M_PI){betaReciprocal = beta + M_PI;} //Set the recipricol heading of the target
            else{betaReciprocal = beta - M_PI;}
        theta = M_PI/2 - abs(alpha - betaReciprocal);
    }
    double getBeta(){return beta;}
    double getEpsilon(){return epsilon;}
    double crossRange(){return range_ground*cos(theta);}
    double predictedRange(){return sqrt(pow(X + Vx*55, 2) + pow(X + Vy*55, 2));}
    double Height(){return height;}
    double groundRange(){return range_ground;}
    double slantRange(){return range_slant;}
    double getX(){return X;}
    double getY(){return Y;}
    double getVx(){return Vx;}
    double getVy(){return Vy;}
    private:
    double range_ground, range_slant, range_cross, height, X, Y, Vx, Vy, Vz;
    double beta, epsilon, betaReciprocal, alpha, theta;
};