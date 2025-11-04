//Version 1, 1 November 2025
#include <iostream>
#include <string>
#include <cmath>
using namespace std;

class Track{
    public:
    Track(){}
    //Trackfile calculations
    void trackInitial(double X, double Y, double Z){
        rangeInitial = sqrt(X*X + Y*Y + Z*Z); //calculate ground range based on XY-plane coordinates
        betaInitial = atan2(Y, X); epsilonInitial = atan2(Z, sqrt(X*X + Y*Y)); //generate new beta and epsilon angles based on calculated values
        betaReciprocal = betaInitial+ M_PI; //Set the recipricol heading of the target
    }
    void trackFinal(double X, double Y, double Z){
        rangeFinal = sqrt(X*X + Y*Y + Z*Z); //calculate ground range based on XY-plane coordinates
        betaFinal = atan2(Y, X); epsilonFinal = atan2(Z, sqrt(X*X + Y*Y)); //generate new beta and epsilon angles based on calculated values
        betaReciprocal = betaFinal+ M_PI; //Set the recipricol heading of the target
    }
    void trackRates(double time){
        epsilonRate = (epsilonFinal - epsilonInitial)/time;
        rangeRate = (rangeFinal - rangeInitial)/time;
        betaRate = (betaFinal - betaInitial)/time;
        alpha;
    }
    void WEZ(){}    
    void targetTheta(double angle){theta = M_PI/2 - abs(alpha - betaReciprocal);}   //Angle difference between target LOS and tangent point
    //Outputs for debugging

    private:
    double epsilonInitial, epsilonFinal, epsilonRate, betaInitial, betaFinal, betaRate, rangeInitial, rangeFinal, rangeRate, alpha, theta, betaReciprocal; //Target variables
};