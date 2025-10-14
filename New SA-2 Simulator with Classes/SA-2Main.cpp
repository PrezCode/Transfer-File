//Version 1, 10 October 2025
#include <iostream>
#include "TargetClass.h"
#include "MissileClass.h"
#include <cmath>
#include <math.h>
#include <cstdlib>
#include <fstream>
using namespace std;

int main(){
    //ofstream targetX("TargetX.txt"), targetY("TargetY.txt");    //Output target position for data collection
    int azimuth, range, course, speed, altitude; //Variables for initializing a target
    int azimuthMissile, rangeMissile;   //Variables for initializing a missile
    bool launch1 = false, launch2 = false, launch3 = false; //Default values for whether a launch has occured.
    bool impact = false, failure = false, inRange = false; //Try to make the simulation run until missile impact or failure is achieved
    double time{0}, timeStep{1};

    cout << "S-75 Missile Intercept Simulation\n";
    cout << endl;
    cout << "Please enter initial target parameters:\n";
    cout << "Bearing: "; cin >> azimuth;
    cout << "Range(km): "; cin >> range;
    cout << "Altitude(km): "; cin >> altitude;
    cout << "Course heading: "; cin >> course;
    cout << "Speed(m/s): "; cin >> speed;    
    Target newTarget(azimuth, range, course, speed, altitude);
    system("PAUSE");
    cout << endl;
    while(launch1 == false || time < 60.0){    //Track target until either a launch happens or target fails to enter launch envelope within 60s 
        //targetX << newTarget.getTargetX() << endl;
        //targetY << newTarget.getTargetY() << endl;
        newTarget.moveX(timeStep);
        newTarget.moveY(timeStep);
        newTarget.moveBeta();
        newTarget.moveRangeGround();
        newTarget.moveRangeSlant();
        newTarget.moveEpsilon();
        if(newTarget.getRangeCross() <= 45000 && newTarget.getRange() <= 45000){
            inRange == true;
        }
        if(inRange == true){
            launch1 == true;
            rangeMissile = rand() % 150;
            azimuthMissile = rand() % 360;             
            Missile missile1(azimuthMissile, rangeMissile);
            time = time + timeStep;
            break;
        }
        time = time + timeStep;
    }
    cout << "rangeMissile: " << rangeMissile << endl;
    cout << "azimuthMissile: " << rangeMissile << endl;
    cout << "Target Range: " << newTarget.getRange() << endl;
    cout << "Target Azimuth: " << newTarget.getBeta()*(180/M_PI) << endl;
    cout << "Runtime: " << time << endl;
    return 0;
}