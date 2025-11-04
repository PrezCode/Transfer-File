//Version 1, 3 November 2025
#include <iostream>
#include "TargetDynamics.h"
#include "MissileDynamics.h"
#include "CoordinateDeterminationSystem.h"
#include <cmath>
#include <cstdlib>
#include <random>
#include <fstream>
using namespace std;

int main(){
    double azimuth, range, course, speed, altitude; //Variables for initializing a target
    double time{0.0}, timeStep{0.01}, timeLaunch{0};    //time variables
    bool missileLaunch = false, missileInFlight = false; 
    random_device rd; // obtain a random number from hardware
    mt19937 gen(rd()); // seed the generator
    uniform_int_distribution<> distr(1, 360); // define the range
    Missile missile1(distr(gen)), missile2(distr(gen)); //Spawn 2 missiles at random locations 100m from origin (SNR-75)
    Trackfile track(0), beacon1(0), beacon2(0);
    //ofstream Missile1V ("Missile1V.txt"), Altitude1 ("Height1.txt"), Altitude2 ("Height2.txt"), TimeOfFlight ("TOF.txt"), Thrust ("Thrust.txt");

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
        //Target motion before launch
        track.initial(target.getX(), target.getY(), target.getZ()); 
        target.move(timeStep);
        track.final(target.getX(), target.getY(), target.getZ());
        track.rates(timeStep);
        track.WEZ();
        if(track.crossRange() <= track.maxRange() && track.TTI() <= 45 && time > 0){ //Automatically determine when launch parameters have been achieved
            missile1.setLaunchAngle(target.getEpsilon() + M_PI/45, target.getBeta()); //Set initial launch angle towards target w/ 4 degree loft
            missileLaunch = true;
            time += timeStep;
            timeLaunch = time;
            break;
        }   
        time += timeStep;
    }
    if(missileLaunch == true){  //Begin missile flyout sequence when launch parameters achieved
        cout << "[Missile Launch Range Achieved]" << endl;
        cout << "Estimated Time to Intercept: " << track.TTI() << " seconds" << endl;
        cout << "Engagement Range: " << track.getRange() << endl;
        cout << "Estimated Intercept Range: " << track.maxRange() << endl;
        while(time <= timeLaunch + 70){
            //Target motion after launch
            track.initial(target.getX(), target.getY(), target.getZ()); 
            target.move(timeStep);
            track.final(target.getX(), target.getY(), target.getZ());
            track.rates(timeStep);
            track.WEZ();
            //Missile 1 motion
            missile1.drag(); 
            if(missile1.getTOF() > 0 && missile1.getTOF() <= 3.1){missile1.diameter(0.654); missile1.boost(timeStep);}   //Booster stage acceleration until 3s TOF
                else if(missile1.getTOF() > 3.1 && missile1.getTOF() < 3.5){missile1.diameter(0.5); missile1.setMass(1390.4); missile1.glide(timeStep);}  //Reduce missile diameter and mass to sim booster departure
                else if(missile1.getTOF() >= 3.5 && missile1.getTOF() <= 46){missile1.sustain(timeStep);} //Operate missile sustainer for 42s
                else{missile1.setMass(667); missile1.glide(timeStep);}  //Missile deccelerates after sustainer stops
            beacon1.initial(missile1.getX(), missile1.getY(), missile1.getZ()); 
            missile1.move(timeStep); 
            beacon1.final(missile1.getX(), missile1.getY(), missile1.getZ()); 
            beacon1.rates(timeStep); 
            missile1.setTOF(timeStep); 
            //Missile 2 motion delayed by 6 seconds
            if(missile1.getTOF() == 6){missile2.setLaunchAngle(target.getEpsilon() + M_PI/45, target.getBeta());}
            if(missile1.getTOF() > 6){
                 //Set initial launch angle towards target w/ 4 degree loft
                missile2.drag();
                if(missile2.getTOF() > 0 && missile2.getTOF() <= 3.1){missile2.diameter(0.654); missile2.boost(timeStep);}   //Booster stage acceleration until 3s TOF
                    else if(missile2.getTOF() > 3.1 && missile2.getTOF() < 3.5){missile2.diameter(0.5); missile2.setMass(1390.4); missile2.glide(timeStep);}  //Reduce missile diameter and mass to sim booster departure
                    else if(missile2.getTOF() >= 3.5 && missile2.getTOF() <= 46){missile2.sustain(timeStep);} //Operate missile sustainer until 45s TOF
                    else{missile2.setMass(667); missile2.glide(timeStep);}  //Missile deccelerates after sustainer stops
                beacon2.initial(missile1.getX(), missile1.getY(), missile1.getZ());
                missile2.move(timeStep);
                beacon2.final(missile1.getX(), missile1.getY(), missile1.getZ());
                missile2.setTOF(timeStep);
                beacon2.rates(timeStep);
            }            
            time += timeStep;
            //Altitude1 << missile1.getZ() << endl; Altitude2 << missile2.getZ() << endl; TimeOfFlight << missile1.getTOF() << endl;
        }
    }
    if(missileLaunch == false){cout << "[Target failed to achieve launch range]" << endl;}
    cout << "Launch Time: " << timeLaunch << " seconds" << endl;
    cout << "Runtime: " << time << " seconds" << endl;
    system("PAUSE");
    return 0;
}