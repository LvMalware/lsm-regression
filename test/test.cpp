#include <iostream>
#include "../src/regression.hpp"

using namespace std;

int
main(int argc, char *argv[])
{
    regression::Power       power;
    regression::Linear      linear;
    regression::Logarithmic logarithmic;
    regression::Exponential exponential;

    power.loadData("data.txt");
    power.findCoefficients();
    
    linear.loadData("data.txt");
    linear.findCoefficients();
    
    logarithmic.loadData("data.txt");
    logarithmic.findCoefficients();

    exponential.loadData("data.txt");
    exponential.findCoefficients();
    
    /*    LINEAR REGRESSION     */
    
    cout << "+-----------------------+" << endl;
    cout << "|   LINEAR REGRESSION   |" << endl;
    cout << "+-----------------------+" << endl;
    cout << "| f(x) = " << linear.getA() << "x + " <<
            linear.getB() << " |" << endl;
    cout << "+-----------------------+" << endl;
    cout << "|   YEAR  |  ACCIDENTS  |" << endl;
    cout << "+-----------------------+" << endl;
    for (int year = 2008; year < 2018; year++)
    {
        cout << "|  " << year << "   |\t" <<
            linear.evaluate(year) << " \t|" << endl;
    }
    cout << "+-----------------------+" << endl << endl;

    /*    LOGARITHMIC REGRESSION     */
    
    cout << "+-----------------------+" << endl;
    cout << "|LOGARITHMIC REGRESSION |" << endl;
    cout << "+-----------------------+" << endl;
    cout << "| f(x) = " << logarithmic.getA() <<
            "log(x) +" << logarithmic.getB() << " |" << endl;
    cout << "+-----------------------+" << endl;
    cout << "|   YEAR  |  ACCIDENTS  |" << endl;
    cout << "+-----------------------+" << endl;
    for (int year = 2008; year < 2018; year++)
    {
        cout << "|  " << year << "   |\t" <<
            logarithmic.evaluate(year) << " \t|" << endl;
    }
    cout << "+-----------------------+" << endl << endl;

     /*    EXPONENTIAL REGRESSION     */
    
    cout << "+-----------------------+" << endl;
    cout << "|EXPONENTIAL REGRESSION |" << endl;
    cout << "+-----------------------+" << endl;
    cout << "| f(x) = " << exponential.getB() <<
            "*exp(" << exponential.getA() << "x) |" << endl;
    cout << "+-----------------------+" << endl;
    cout << "|   YEAR  |  ACCIDENTS  |" << endl;
    cout << "+-----------------------+" << endl;
    for (int year = 2008; year < 2018; year++)
    {
        cout << "|  " << year << "   |\t" <<
            exponential.evaluate(year) << " \t|" << endl;
    }
    cout << "+-----------------------+" << endl << endl;

    /*    Power REGRESSION     */
    
    cout << "+-----------------------+" << endl;
    cout << "|    POWER REGRESSION   |" << endl;
    cout << "+-----------------------+" << endl;
    cout << "| f(x) = " << power.getB() <<
            "x^" << exponential.getA() << " |" << endl;
    cout << "+-----------------------+" << endl;
    cout << "|   YEAR  |  ACCIDENTS  |" << endl;
    cout << "+-----------------------+" << endl;
    for (int year = 2008; year < 2018; year++)
    {
        cout << "|  " << year << "   |\t" <<
            power.evaluate(year) << " \t|" << endl;
    }
    cout << "+-----------------------+" << endl << endl;

    return 0;
}