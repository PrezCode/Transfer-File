//Version 1, 10 October 2025
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
    int azimuth, range, course, speed, altitude; //Variables for initializing a target
    //bool impact = false, failure = false, inRange = false; //Try to make the simulation run until missile impact or failure is achieved
    double time{0.0}, timeStep{1.0};
    random_device rd; // obtain a random number from hardware
    mt19937 gen(rd()); // seed the generator
    uniform_int_distribution<> distr(1, 360); // define the range

    cout << "S-75 Missile Intercept Simulation\n";
    cout << endl;
    cout << "Please enter initial target parameters:\n";
    cout << "Bearing: "; cin >> azimuth;
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
            Missile launch1(distr(gen), 100);
            cout << "[Missile Launch Range Achieved]" << endl;
            break; 
        } 
        time = time + timeStep;
        if(time == 60){cout << "[Target failed to achieve launch range]" << endl;}
    }
    cout << "Runtime: " << time << " seconds" << endl;
    system("PAUSE");
    return 0;
}