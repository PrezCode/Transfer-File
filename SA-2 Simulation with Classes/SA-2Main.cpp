//Version 1, 29 October 2025
#include <iostream>
#include "TargetClass.h"
#include "MissileClass.h"
#include <cmath>
#include <math.h>
#include <cstdlib>
#include <random>
#include <fstream>
using namespace std;

int main(){
    //ofstream targetX("TargetX.txt"), targetY("TargetY.txt");    //Output target position for data collection
    double azimuth, range, course, speed, altitude; //Variables for initializing a target
    double time{0.0}, timeStep{1.0};    //time variables
    bool missileLaunch = false, missileImpact = false;
    Missile Launch1(0), Launch2(0), Launch3(0);
    random_device rd; // obtain a random number from hardware
    mt19937 gen(rd()); // seed the generator
    uniform_int_distribution<> distr(1, 360); // define the range

    cout << "S-75 Missile Intercept Simulation\n";
    cout << endl;
    cout << "Please enter initial target parameters:\n";
    cout << "Bearing (-1 to cancel): "; cin >> azimuth;
    if(azimuth == -1){
        cout << "Simulation Canceled" << endl;
    }else{
        cout << "Range(km): "; cin >> range;
        cout << "Altitude(km): "; cin >> altitude;
        cout << "Course heading: "; cin >> course;
        cout << "Speed(m/s): "; cin >> speed;    
        Target newTarget(azimuth, range, course, speed, altitude);
        cout << endl;
        cout << "Cross Range: " << newTarget.getRangeCross() << endl;
        while(time < 60){    //Track target until either a launch happens or target fails to enter launch envelope within 60s 
            newTarget.moveX(timeStep);
            newTarget.moveY(timeStep);
            newTarget.moveBeta();
            newTarget.moveRangeGround();
            newTarget.moveRangeSlant();
            newTarget.moveEpsilon();
            if(newTarget.getRangeCross() <= 45000 && newTarget.getRange() <= 45000){
                Launch1.initialBeta(distr(gen));
                Launch1.intialMissileX();
                Launch1.initialMissileY();
                Launch1.setMissileEpsilon();

                cout << "[Missile Launch Range Achieved]" << endl;
                missileLaunch = true;
                break; 
            } 
            time += timeStep;
            if(time == 60){cout << "[Target failed to achieve launch range]" << endl;}
        }
        if(missileLaunch == true){
            while(missileImpact == false){
            Launch1.drag();
            Launch1.timeOfFlight(timeStep);
            if(Launch1.getTOF() <= 3){Launch1.booster(timeStep);}
            if(Launch1.getTOF() > 3 && Launch1.getTOF() <= 40){Launch1.sustainer(timeStep);}
            if(Launch1.getTOF() > 40){Launch1.}
            time += timeStep;
            }
            cout << "Missile TOF: " << Launch1.getTOF();
        }
        
        cout << "Runtime: " << time << " seconds" << endl;
    }
    system("PAUSE");
    return 0;
}