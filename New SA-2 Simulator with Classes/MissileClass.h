#include <iostream>
#include <string>
#include <cmath>
#include <math.h>
using namespace std;

class Missile{
    public:
    Missile(int bearing, int distance){ //Generate a missile's launch location based on random input variables
        beta = (450 - bearing)*(M_PI/180);
        Z = 0;
        epsilon = atan2(Z, distance);
        X = distance*cos(beta);
        Y = distance*sin(beta);
        velocity = 0;
        mass = 2395;
        TOF = 0;
    }
    void timeOfFlight(int t){TOF = TOF + t;} //log time of launch for missile
    void drag(){  //calculate air density based on missile height
        if(Z < 9144){rho = 1.22557*exp(-Z/9144);}
        else{rho = 1.75228763*exp(-Z/6705.6);}
        aDrag = (rho*0.03*0.196349541*(pow(velocity, 2)/2))/mass;
    }
    void booster(int t){ //generate velocity of missile during boost phase
        mass = mass - 200*t;
        thrust = 4708880 - 127530*(TOF/3);
        velocity = velocity + (thrust/mass)*t - aDrag*t;
    }
    void sustainer(int t){  //generate velocity of missile during sustainer phase
        mass = mass - 20.5*t;
        thrust = 34335;
        velocity = velocity + (thrust/mass)*t - aDrag*t;
    }
    void glide(int t){  //generate velocity of missile during glide phase
        mass = 695;
        velocity = velocity - aDrag*t;
    }
    int getMissileX(){return X;}
    int getMissileY(){return Y;}
    private:
    int X, Y, Z, Vx, Vy, Vz, mass, thrust;
    double beta, epsilon, velocity, rho, TOF, aDrag;
};