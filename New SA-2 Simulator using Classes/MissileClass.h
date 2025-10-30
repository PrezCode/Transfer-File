#include <iostream>
#include <string>
#include <cmath>
#include <math.h>
using namespace std;

class Missile{
    public:
    Missile(double azimuth){ //Generate a missile and initial position/values
        Z = 0;          
        velocity = 0;
        mass = 2395;
        TOF = 0;
        beta = (450 - azimuth)*(M_PI/180);
        X = 100*cos(beta);
        Y = 100*sin(beta);
    }
    void setMissileEpsilon(){epsilon = atan2(Z, sqrt(X * X + Y * Y));}
    void timeOfFlight(double t){TOF += t;} //log time of launch for missile
    void drag(){  //calculate air density based on missile height
        if(Z < 9144){rho = 1.22557*exp(-Z/9144);}
        else{rho = 1.75228763*exp(-Z/6705.6);}
        aDrag = (rho*0.03*0.196349541*(pow(velocity, 2)/2))/mass;
    }
    void booster(double t){ //generate velocity of missile during boost phase
        mass -= 200*TOF;
        thrust = 4708880 - 127530*(TOF/3);
        velocity += (thrust/mass)*t - aDrag*t;
    }
    void sustainer(double t){  //generate velocity of missile during sustainer phase
        mass -= 20.5*(TOF - 3);
        thrust = 34335;
        velocity += (thrust/mass)*t - aDrag*t;
    }
    void glide(double t){  //generate velocity of missile during glide phase
        mass = 695;
        velocity -= aDrag*t;
    }
    double getTOF(){return TOF;}
    double getMissileX(){return X;}
    double getMissileY(){return Y;}
    private:
    double X, Y, Z, Vx, Vy, Vz, mass, thrust;
    double beta, epsilon, velocity, rho, TOF, aDrag;
};