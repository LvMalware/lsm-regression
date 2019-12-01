#include <iostream>

#include "regression.hpp"

using namespace std;

int
main(int argc, char *argv[])
{
    regression::Linear li;
    regression::Logarithmic lo;
    regression::Exponential ex;
    regression::Power po;
    li.loadData("../data.txt");
    lo.loadData("../data.txt");
    ex.loadData("../data.txt");
    po.loadData("../data.txt");
    li.findCoefficients();
    lo.findCoefficients();
    ex.findCoefficients();
    po.findCoefficients();
    cout << "Lin: " << li.evaluate(2) << " | R2: " << li.getR2() << endl;
    cout << "Log: " << lo.evaluate(2) << " | R2: " << lo.getR2() << endl;
    cout << "Exp: " << ex.evaluate(2) << " | R2: " << ex.getR2() << endl;
    cout << "Pow: " << po.evaluate(2) << " | R2: " << po.getR2() << endl;
    
    return 0;
}