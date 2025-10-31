//Version 1, 29 October 2025
#include <iostream>
#include "TargetClass.h"
#include "MissileClass.h"
#include <cmath>
#include <math.h>
#include <cstdlib>
#include <random>
using namespace std;

int main(){
    double azimuth, range, course, speed, altitude; //Variables for initializing a target
    double time{0.0}, timeStep{0.1};    //time variables
    bool missileLaunch = false, missileInFlight = false; 
    random_device rd; // obtain a random number from hardware
    mt19937 gen(rd()); // seed the generator
    uniform_int_distribution<> distr(1, 360); // define the range
    Missile missile1(distr(gen)), missile2(distr(gen)), missile3(distr(gen)); //Spawn 3 missiles at random locations 100m from origin (SNR-75)

    cout << "S-75 Missile Intercept Simulation\n";
    cout << endl;
    cout << "Please enter initial target parameters:\n";
    cout << "Bearing: "; cin >> azimuth;
    cout << "Range(km): "; cin >> range;
    cout << "Altitude(km): "; cin >> altitude;
    cout << "Course heading: "; cin >> course;
    cout << "Speed(m/s): "; cin >> speed;    
    Target target(azimuth, range, course, speed, altitude);
    cout << endl;
    while(time < 120){    //Track target until either a launch happens or target fails to enter launch envelope within 60s 
        target.move(timeStep);
        if(target.crossRange() <= 36500 && target.predictedRange() <= 36500){
            missile1.setEpsilon();
            missile1.setElevation(target.getEpsilon());
            missile1.setHeading(target.getBeta());
            missileLaunch = true;
            break;
        } 
        if(missileInFlight == true){
            missile1.setTOF(timeStep);            
            missile1.drag();
            if(missile1.getTOF() <= 3){missile1.booster(timeStep);}
            else if(missile1.getTOF() > 3 && missile1.getTOF() <= 42){missile1.sustainer(timeStep);}
            else if(missile1.getTOF() > 42){missile1.glide();}
            missile1.move(timeStep); 
            if(missile1.getTOF() == 55){missileInFlight = false; cout << "[Missile Timed Out]" << endl;}
        }
        time += timeStep;
        if(time == 120){cout << "[Target failed to achieve launch range]" << endl; break;}
    }
    if(missileLaunch == true){cout << "[Missile Launch Range Achieved]" << endl;}
    cout << "Target Range: " << target.groundRange() << endl;
    cout << "Cross Range: " << target.crossRange() << endl;
    //cout << "Predicted Intercept Range: " << target.predictedRange() << endl;
    cout << "Runtime: " << time << " seconds" << endl;
    system("PAUSE");
    return 0;
}