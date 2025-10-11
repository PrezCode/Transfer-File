//Version 1, 10 October 2025
#include <iostream>
#include "TargetClass.h"
#include <cmath>
#include <math.h>
using namespace std;

int main(){
    int azimuth, range, course, speed, altitude, count_missile;
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
    cout << "Target Returns\n";
    cout << "Beta: " << newTarget.getBeta() << endl;
    cout << "Epsilon: " << newTarget.getEpsilon() << endl;
    cout << "Range(m): " << newTarget.getRange() << endl;
    cout << "Slant(m): " << newTarget.getSlant() << endl;
    cout << "Height(m): " << newTarget.getHeight() << endl;
    system("PAUSE");

    return 0;
}