//Formula to calculate and test cross range of a target (tangent radius)
#include <iostream>
#include <cmath>
#include <math.h>
using namespace std;

int main(){
    int alpha, beta, betaReciprocal, theta, range, rangeCross;
    cout << "Target azimuth: "; cin >> beta;
    cout << "Target heading: "; cin >> alpha;
    cout << "Target range (km): "; cin >> range;
    if(beta <= 180){
        betaReciprocal = beta + 180;
    }else{
        betaReciprocal = beta - 180;
    }
    if(betaReciprocal < alpha){
        theta = betaReciprocal + (360 - alpha);
    }else if(betaReciprocal > alpha){
        theta = betaReciprocal - alpha;
    }else{
        theta = 0;
    }
    if(90 + theta < 180){
        rangeCross = range*sin(theta*(3.141592/180));
        cout << "Cross range distance is: " << rangeCross << "km" << endl;
    }else{
        cout << "Target is receeding. No cross range available." << endl;
    }
    
    system("PAUSE");
    return 0;
}