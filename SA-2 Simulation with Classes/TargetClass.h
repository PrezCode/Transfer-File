#include <iostream>
#include <string>
#include <cmath>
#include <math.h>
using namespace std;

class Target{
    public:
    Target(int bearing, int range, int heading, int speed, int altitude){   //Generate initial target information
        beta = (360 - bearing)*(M_PI/180);
        alpha = (360 - heading)*(M_PI/180);
        epsilon = atan2(altitude, range); 
        range_ground = range*1000;
        height = altitude*1000;               
        range_slant = sqrt(pow(range, 2) + pow(altitude, 2))*1000;
        X = -range_ground*sin(beta);
        Y = range_ground*cos(beta);
        Vx = speed*sin(alpha);
        Vy = speed*cos(alpha);         
    }
    void moveX(int t){X = X + Vx*t;}
    void moveY(int t){Y = Y + Vy*t;}
    void moveRangeGround(){range_ground = sqrt(pow(X, 2) + pow(Y, 2));}
    void moveRangeSlant(){range_slant = sqrt(pow(range_ground, 2) + pow(height, 2));}
    void moveBeta(){beta = -atan2(X, Y);}
    void moveEpsilon(){epsilon = atan2(height, range_ground);}
    double getBeta(){return beta;}
    double getEpsilon(){return epsilon;}
    double getBetaDegrees(){return 360 - beta*(180/M_PI);}
    int getRangeCross(){
        if(beta <= M_PI){
            betaReciprocal = beta + M_PI;
        }else{
            betaReciprocal = beta - M_PI;
        }
        if(betaReciprocal < alpha){
            theta = M_PI - (M_PI/2 + alpha + (2*M_PI - betaReciprocal));
        }else if(betaReciprocal > alpha){
            theta = M_PI - (M_PI/2 + betaReciprocal + (2*M_PI - alpha));
        }else{
            theta = 0;
        }
        if(M_PI/2 + theta < M_PI){
            return range_cross = range_ground*sin(theta);
        }else{
            return 999;
        }
    }
    int getHeight(){return height;}
    int getRange(){return range_ground;}
    int getSlant(){return range_slant;}
    int getTargetX(){return X;}
    int getTargetY(){return Y;}
    int getVx(){return Vx;}
    int getVy(){return Vy;}
    private:
    int range_ground, range_slant, range_cross, height, X, Y, Vx, Vy, Vz;
    double beta, epsilon, betaReciprocal, alpha, theta;
};