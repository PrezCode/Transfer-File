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
        epsilon = 0;
        X = 100*cos(beta);
        Y = 100*sin(beta);
    }
    void setEpsilon(){epsilon = atan2(Z, sqrt(X * X + Y * Y));}
    void setTOF(double t){TOF += t;} //log time of launch for missile
    void drag(){  //calculate air density based on missile height
        if(Z < 9144){rho = 1.22557*exp(-Z/9144);}
        else{rho = 1.75228763*exp(-Z/6705.6);}
        aDrag = (rho*0.03*0.196349541*(pow(velocity, 2)/2))/mass;
    }
    void booster(double t){ //generate velocity of missile during boost phase
        mass -= 200*t;
        thrust = 4708880 - 127530*(TOF/3);
        velocity += (thrust/mass) - aDrag;
        Vx = velocity*cos(heading);
        Vy = velocity*sin(heading);
        Vz = velocity*sin(theta);
    }
    void sustainer(double t){  //generate velocity of missile during sustainer phase
        mass -= 20.5*t;
        thrust = 34335;
        velocity += (thrust/mass) - aDrag;
        Vx = velocity*cos(heading);
        Vy = velocity*sin(heading);
        Vz = velocity*sin(theta);
    }
    void glide(){  //generate velocity of missile during glide phase
        mass = 695;
        velocity = -aDrag;
        Vx = velocity*cos(heading);
        Vy = velocity*sin(heading);
        Vz = velocity*sin(theta);
    }
    void setElevation(double E){theta = E;} //Set initial elevation angle of missile
    void setHeading(double B){heading = B;} //Set initial heading angle of missile
    void move(double t){X += Vx*t; Y += Vy*t; Z += Vz*t;}
    double getTOF(){return TOF;}  //Return calculated time of flight
    double SlantRange(){return slantRange = sqrt(X*X + Y*Y + Z*Z);} //return slant range to missile
    double getX(){return X;}    //Return missile X coordinate
    double getY(){return Y;}    //Return missile Y coordinate
    double getZ(){return Z;}    //Return missile Z coordinate
    private:
    double X, Y, Z, Vx, Vy, Vz, mass, thrust, acceleration, Ax, Ay, Az;
    double beta, epsilon, heading, theta, velocity, rho, TOF, aDrag, slantRange;
};