//Version 1, 1 November 2025
#include <iostream>
#include <string>
#include <cmath>
using namespace std;
//V-755 Model
class Missile{
    public:
    Missile(double azimuth){ //Generate a missile and initial position/values
        Z = 0;          
        velocity = 0;
        mass = 2397.9;
        TOF = 0;
        beta = (450 - azimuth)*(M_PI/180);
        epsilon = 0;
        X = 100*cos(beta);
        Y = 100*sin(beta);
    }
    void setEpsilon(){epsilon = atan2(Z, sqrt(X*X + Y*Y));}
    void setTOF(double t){TOF += t;} //log time of launch for missile
    void drag(){  //calculate air density based on missile height
        Cd = 0.5;
        if(Z < 11000){  //calculations from NASA: https://www.grc.nasa.gov/www/k-12/airplane/atmosmet.html
            tempurature = 15.04 - 0.00649*Z;
            pressure = 101.29*pow(((tempurature + 273.1) / 288.08), 5.256);
            rho = pressure/(0.2869*(tempurature + 273.1));}
        else{
            tempurature = -56.46;
            pressure = 22.65*exp(1.73 - 0.000157*Z);
            rho = pressure/(0.2869*(tempurature + 273.1));
        }
        Drag = (Cd*rho*area*(pow(velocity, 2)/2));
    }
    void diameter(double r){area = M_PI*pow(0.5*r, 2) + 0.0123375;} //Set missile diameter for area value in drag calculation
    void boost(double t){
        mass -= 203*t;  
        thrust = 560000 - 80000*(TOF/2.5);
        Vx += (thrust/mass)*cos(heading)*t - (Drag/mass)*cos(heading)*t;
        Vy += (thrust/mass)*sin(heading)*t - (Drag/mass)*sin(heading)*t;
        Vz += (thrust/mass)*sin(theta)*t - (Drag/mass + 9.8)*sin(theta)*t;
        velocity = sqrt(Vx*Vx + Vy*Vy + Vz*Vz);
    }
    void sustain(double t){
        mass -= 3617/210*t;
        thrust = 35000;
        Vx += (thrust/mass)*cos(heading)*t - (Drag/mass)*cos(heading)*t;
        Vy += (thrust/mass)*sin(heading)*t - (Drag/mass)*sin(heading)*t;
        Vz += (thrust/mass)*sin(theta)*t - (Drag/mass + 9.8)*sin(theta)*t;
        velocity = sqrt(Vx*Vx + Vy*Vy + Vz*Vz);
    }
    /*void throttle(double t){  //generate velocity of missile during transistion to minimum thrust sustainer phase
        mass -= 2400/217*t;
        thrust = 1.679*(TOF*TOF) -181.786*TOF + 6917.495;
        velocity += (thrust/mass)*t - aDrag*t;
        Vx = velocity*cos(heading);
        Vy = velocity*sin(heading);
        Vz = velocity*sin(theta);
    }*/
    void glide(double t){
        Vx -= (Drag/mass)*cos(heading)*t;
        Vy -= (Drag/mass)*sin(heading)*t;
        Vz -= (Drag/mass + 9.8)*sin(theta)*t;
        velocity = sqrt(Vx*Vx + Vy*Vy + Vz*Vz);
    }
    void setLaunchAngle(double E, double B){theta = E; heading = B;}
    void move(double t){X += Vx*t; Y += Vy*t; Z += Vz*t;}
    void setMass(double m){mass = m;}       
    double getTOF(){return TOF;}  //Return calculated time of flight
    double SlantRange(){return slantRange = sqrt(X*X + Y*Y + Z*Z);} //return slant range to missile
    
    //Diagnostic Commands
    double getTheta(){return theta*180/M_PI;}
    double getheading(){return heading;}
    private:
    double X, Y, Z, Vx, Vy, Vz, mass, thrust, pressure, tempurature, area, Cd;
    double beta, epsilon, heading, theta, velocity, rho, TOF, Drag, slantRange;
};