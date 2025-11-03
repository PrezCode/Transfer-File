
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
    void move(double t){
        X += Vx*t; Y += Vy*t;   //move target along XY-plane
        range_ground = sqrt(X*X + Y*Y); //calculate ground range based on XY-plane coordinates
        range_slant = sqrt(pow(range_ground, 2) + pow(height, 2));  //calculate slant range to target
        beta = atan2(Y, X); epsilon = atan2(height, range_ground); //generate new beta and epsilon angles based on calculated values
        betaReciprocal = beta + M_PI; //Set the recipricol heading of the target
        theta = M_PI/2 - abs(alpha - betaReciprocal);
    }
    double maxRange(){    //Determine max range based on quadratic regression formula using real documented effective ranges
        if(Vsum <= 640){    //Rmax for Three-Point Method
            if(height < 1000){Rmax = 15000;}
            else if(height >= 1000 && height <= 20000){Rmax = -0.000007832*pow(height, 2) + 1.159*height + 23295;}
            else if(height > 20000 && height <= 25000){Rmax = 43000;}
            else{Rmax = 0;}
        }else{Rmax = 0;}
        return Rmax;
    }
    double getBeta(){return beta;}
    double getEpsilon(){return epsilon;}
    double crossRange(){return range_cross = range_ground*cos(theta);}
    double TTI(){
        return (sqrt(pow(range_ground, 2) - pow(range_cross, 2)) - sqrt(pow(Rmax, 2) - pow(range_cross, 2)))/Vsum;
    }
    double groundRange(){return range_ground;}
    double slantRange(){return range_slant;}
    private:
    double range_ground, range_slant, range_cross, height, X, Y, Vsum, Vx, Vy, Vz;
    double beta, epsilon, betaReciprocal, alpha, theta, Rmax;
};