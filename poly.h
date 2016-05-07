// ------------------------------------------------ poly.h ------------------------------------------------------- -
// John Zoeller, CSS 343 A
// Creation Date : 1/6/16
// Date of Last Modification : 1/16/16
// -------------------------------------------------------------------------------------------------------------------- 
// Purpose - Outlines an abstract polynomial class
// -------------------------------------------------------------------------------------------------------------------- 
// Notes on specifications, special algorithms, and assumptions:
// -none
// --------------------------------------------------------------------------------------------------------------------

#ifndef POLY_H
#define POLY_H
#include <iostream>
using namespace std;

class Poly
{
    friend ostream &operator<<(ostream &, const Poly &);
    friend istream &operator>>(istream &, Poly &);
    friend void resize(int size, Poly &right);

    private:
        int *arr;                                                   //poly array
        int co;                                                      //most recent coefficient
        int po;                                                     //highest power

    public:
        //Constructors:  Default, Set Coefficient, Set Both, copy constuctor, destuctor
        Poly();
        Poly(int coef);
        Poly(int coef, int power);
        Poly(const Poly &obj);
        ~Poly();

        const Poly &operator=(const Poly &rhs);         //assignment operator

        //assignments
        Poly &operator+=(const Poly &);
        Poly &operator-=(const Poly &);
        Poly &operator*=(const Poly &);

        //bools
        bool operator==( const Poly &) const;
        bool operator!=( const Poly &) const;

        //math        
        Poly operator*(const Poly &);
        Poly operator-(const Poly &);
        Poly operator+(const Poly &);

        int getCoeff(int power);
        void setCoeff(int newCo, int index);
};

#endif