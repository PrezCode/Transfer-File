//Version 1, 3 November 2025
#include <iostream>
#include <string>
#include <cmath>
using namespace std;

class Trackfile{
    public:
    Trackfile(double zero){
        rangeInitial = zero; rangeFinal = zero; rangeRate = zero;
        betaInitial = zero; betaFinal = zero; betaRate = zero;
        epsilonInitial = zero; epsilonFinal = zero; epsilonRate = zero;
    }
    //Trackfile calculations
    void initial(double X, double Y, double Z){
        rangeInitial = sqrt(X*X + Y*Y + Z*Z); //Create first slant range reference value
        betaInitial = atan2(Y, X);  //Create first beta reference value
        epsilonInitial = atan2(Z, sqrt(X*X + Y*Y)); //Create first epsilon reference value
        polarInitialX = rangeInitial*cos(betaInitial);
        polarInitialY = rangeInitial*sin(betaInitial);
        heightInitial = rangeInitial*sin(epsilonInitial);
    }
    void final(double X, double Y, double Z){
        rangeFinal = sqrt(X*X + Y*Y + Z*Z); //Create second slant range reference value
        betaFinal = atan2(Y, X);    //Create second beta reference value
        epsilonFinal = atan2(Z, sqrt(X*X + Y*Y));   //Create second epsilon reference value
        polarFinalX = rangeFinal*cos(betaFinal);
        polarFinalY = rangeFinal*sin(betaFinal);
        heightFinal = rangeFinal*sin(epsilonFinal);
    }
    void rates(double time){
        rangeRate = (rangeFinal - rangeInitial)/time;
        epsilonRate = (epsilonFinal - epsilonInitial)/time;
        betaRate = (betaFinal - betaInitial)/time;        
        Vxy = (sqrt(pow(rangeInitial*betaRate, 2) + pow(rangeRate, 2)) + sqrt(pow(rangeFinal*betaRate, 2) + pow(rangeRate, 2)))/2;
    }
    void WEZ(){        
        if(Vxy <= 640){    //Rmax for Three-Point Method
            if(heightFinal < 1000){Rmax = 15000;}
            else if(heightFinal >= 1000 && heightFinal <= 20000){Rmax = -0.000007832*pow(heightFinal, 2) + 1.159*heightFinal + 23295;}
            else if(heightFinal > 20000 && heightFinal <= 25000){Rmax = 43000;}
            else{Rmax = 0;}
        }else{Rmax = 0;}
        alpha = atan2(polarFinalY - polarInitialY, polarFinalX - polarInitialX);
        theta = M_PI/2 - abs(alpha - (betaFinal + M_PI));
        range_cross = rangeFinal*cos(epsilonFinal)*cos(theta);
        TimeToIntercept = (sqrt(pow(rangeFinal*cos(epsilonFinal), 2) - pow(range_cross, 2)) - sqrt(pow(Rmax, 2) - pow(range_cross, 2)))/Vxy;
    }
    double TTI(){return TimeToIntercept;}
    double getRange(){return rangeFinal;}
    double crossRange(){return range_cross;}
    double maxRange(){return Rmax;}
    private:
    double epsilonInitial, epsilonFinal, epsilonRate, betaInitial, betaFinal, betaRate, rangeInitial, rangeFinal, rangeRate;
    double polarInitialX, polarFinalX, polarInitialY, polarFinalY, alpha, theta, range_cross, TimeToIntercept, Vxy, Rmax, heightInitial, heightFinal;
};