//Version 1, 31 October 2025
#include <iostream>
#include "TargetDynamics.h"
#include "MissileDynamics.h"
#include <cmath>
#include <cstdlib>
#include <random>
#include <fstream>
using namespace std;

int main(){
    double azimuth, range, course, speed, altitude; //Variables for initializing a target
    double time{0.0}, timeStep{0.1};    //time variables
    bool missileLaunch = false, missileInFlight = false; 
    random_device rd; // obtain a random number from hardware
    mt19937 gen(rd()); // seed the generator
    uniform_int_distribution<> distr(1, 360); // define the range
    Missile missile1(distr(gen)), missile2(distr(gen)), missile3(distr(gen)); //Spawn 3 missiles at random locations 100m from origin (SNR-75)
    //ofstream MissileZ ("MissileHeight.txt"), MissileVelocity ("MissileVelocity.txt"), TimeOfFlight ("TimeOfFlight.txt"), MissileMass ("Mass.txt"), DragForce ("Drag.txt");

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
        if(target.crossRange() <= target.maxRange() && target.TTI() <= 45 && time > 0){ //Automatically determine when launch parameters have been achieved
            missile1.setEpsilon();
            missile1.setLaunchAngle(target.getEpsilon(), target.getBeta()); //Set initial launch angle towards target w/ 5 degree loft
            missileLaunch = true;
            break;
        }        
        time += timeStep;
    }
    if(missileLaunch == true){  //Begin missile flyout sequence when launch parameters achieved
        cout << "[Missile Launch Range Achieved]" << endl;
        cout << "Time to Intercept: " << target.TTI() << " seconds" << endl;
        cout << "Engagement Range: " << target.groundRange() << endl;
        cout << "Intercept Range: " << target.maxRange() << endl;
        while(missile1.getTOF() < 60){
            missile1.drag();
            if(missile1.getTOF() <= 2.5){missile1.diameter(0.654); missile1.boost(timeStep);}   //Booster stage acceleration until 3s TOF
                else if(missile1.getTOF() > 2.5 && missile1.getTOF() < 3){missile1.diameter(0.5); missile1.setMass(1390.4); missile1.glide(timeStep);}  //Reduce missile diameter and mass to sim booster departure
                else if(missile1.getTOF() >= 3 && missile1.getTOF() <= 45){missile1.sustain(timeStep);} //Operate missile sustainer until 45s TOF
                else{missile1.setMass(667); missile1.glide(timeStep);}  //Missile deccelerates after sustainer stops
            missile1.move(timeStep);
            missile1.setTOF(timeStep);
        }
    }
    if(missileLaunch == false){cout << "[Target failed to achieve launch range]" << endl;} 
    cout << "Runtime: " << time << " seconds" << endl;
    system("PAUSE");
    return 0;
}