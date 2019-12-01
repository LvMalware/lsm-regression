/*
 * regression.hpp - linear, logarithmic, exponential and potence regressions
 *
 * Copyright (C) 2019 Lucas V. Araujo <lucas.vieira.ar@disroot.org> .
 *
 * This is free software: you are free to change and redistribute it under the
 * terms of GNU GPL license version 3 or, at your choice, any later version.
 * You should have received a copy of the license along with this software. If
 * not, you can read the full text at https://gnu.org/licenses/gpl.html.
 * This software is offered AS IT IS, in hope that it will be usefull, but there
 * is NO WARRANTY, to the extent permitted by law.
 */


#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>

#ifndef  _REGRESSION_HPP
#define  _REGRESSION_HPP 1

/* 
 * Defining a constant with the type used to store the data is very usefull when
 * making changes to the code.
 */
#define numericType double

using std::vector;
using std::ifstream;

namespace regression
{
    /*
     * The struct point is used to store the data from each point (x, y) that is
     * being used.
     */
    
    struct point
    {
        numericType x;
        numericType y;
    };

    
    class Linear
    {
        /*
         * Declaring the members as protected make them inaccessible on other
         * classes context, while they still are avaiable to the child classes.
         */
        protected:

            vector<point> data;
            numericType   R2, sumX, sumY, sumX2, sumXY, coefA, coefB;

        public:

            Linear()  {}
            ~Linear() {}

            virtual
            void
            loadData(const char *filename)
            {
                /*
                 * Given a input filename, this function opens that file, loads
                 * the data and then close it.
                 * Note that the input file must contain only numerical data,
                 * arranged in such a way that each line contains an ordered
                 * pair x y (separated by a space), indicating a known point.
                 */
                
                ifstream file;
                /*
                 * The file will open in read-only mode.
                 */
                file.open(filename, std::ios_base::in);
                /*
                 * Keep reading a line while the end of the file if not reached.
                 */
                while (!file.eof())
                {
                    point p;
                    /* Reads the first numerical value on the file to p.x, and
                     * the second to p.y;
                     */
                    file >> p.x >> p.y;
                    /* Stores the point struct P on the data vector */
                    data.push_back(p);
                }
                /* closes the file */
                file.close();
                /*
                 * R2 (R square) is a metric of the curve setting. Initially we
                 * set it to -1 so we know we haven't calculated it yet.
                 */
                R2 = -1;
            }

            virtual
            void
            findCoefficients()
            {
                /*
                 * This function finds the coefficients A and B of the line that
                 * best describes the growth of the points, through the method
                 * of Least Squares. Read the documentation for more info.
                 */
                
                /* Initializing the variables with 0 to increment them later */
                sumX = sumY = sumX2 = sumXY = 0;
                /*
                 * Now we store the needed sums to the regression.
                 *         _n              _n
                 * sumX =  \ x[i] ; sumY = \ y[i] ; and so on...
                 *         /_              /_
                 *         i=1             i=1
                 */
                for (point p : data)
                {
                    sumX  += p.x;
                    sumY  += p.y;
                    sumX2 += p.x * p.x;
                    sumXY += p.x * p.y;
                }

                
                coefA = (data.size() * sumXY - sumX * sumY) /
                        (data.size() * sumX2 - sumX * sumX);

                coefB = (sumX * sumXY - sumY * sumX2) /
                        (sumX * sumX  - data.size() * sumX2);
            }

            numericType
            getA()
            {
                return coefA;
            }

            numericType
            getB()
            {
                return coefB;
            }

            numericType
            getSumX()
            {
                return sumX;
            }

            numericType
            getSumY()
            {
                return sumY;
            }

            numericType
            getSumXY()
            {
                return sumXY;
            }

            numericType
            getSumX2()
            {
                return sumX2;
            }

            vector<point>
            getData()
            {
                return data;
            }

            virtual
            void
            setData(const vector<point> &_data)
            {
                data = _data;
            }

            virtual
            numericType
            evaluate(numericType x)
            {
                return coefA * x + coefB;
            }

            virtual
            numericType
            getR2()
            {
                if (R2 == -1)
                {
                    numericType medY  = sumY / data.size();
                    numericType RegSS = 0;
                    numericType TotSS = 0;
                    for (point p : data)
                    {
                        RegSS += pow(Linear::evaluate(p.x) - medY, 2);                        
                        TotSS += pow(p.y - medY, 2);
                    }
                    R2 = RegSS / TotSS;
                }
                return R2;
            }
    };

    
    class Logarithmic : public Linear
    {
        public:
            
            virtual
            void
            loadData(const char *filename)
            {
                ifstream file;
                file.open(filename, std::ios_base::in);
                while (!file.eof())
                {
                    point p;
                    file >> p.x >> p.y;
                    p.x = log(p.x);
                    data.push_back(p);
                }
                file.close();
                R2 = -1;
            }

            virtual
            numericType
            evaluate(numericType x)
            {
                return coefA * log(x) + coefB;
            }
    };

    
    class Exponential : public Linear
    {
        public:
            Exponential()  {}
            
            ~Exponential() {}

            virtual
            void
            loadData(const char *filename)
            {
                ifstream file;
                file.open(filename, std::ios_base::in);
                while (!file.eof())
                {
                    point p;
                    file >> p.x >> p.y;
                    p.y = log(p.y);
                    data.push_back(p);
                }
                file.close();
                R2 = -1;
            }

            virtual
            void findCoefficients()
            {
                Linear::findCoefficients();
                //std::cout << "B: " << coefB << std::endl;
                //coefB = exp(coefB);
            }

            virtual
            numericType
            evaluate(numericType x)
            {
                return exp(coefB) * exp(coefA * x);
            }
    };

    class Power : public Linear
    {
        public:
            Power()  {}
            ~Power() {}
            virtual
            void
            loadData(const char *filename)
            {
                ifstream file;
                file.open(filename, std::ios_base::in);
                while (!file.eof())
                {
                    point p;
                    file >> p.x >> p.y;
                    p.x = log(p.x);
                    p.y = log(p.y);
                    data.push_back(p);
                }
                file.close();
                R2 = -1;
            }

            virtual
            void findCoefficients()
            {
                Linear::findCoefficients();
                //coefB = exp(coefB);
            }

            virtual
            numericType
            evaluate(numericType x)
            {
                return exp(coefB) * pow(x, coefA);
            }
    };

}

#endif /*REGRESSION_HPP*/