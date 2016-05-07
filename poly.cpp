// ------------------------------------------------ poly.cpp ------------------------------------------------------- -
// John Zoeller, CSS 343 A
// Creation Date : 1/6/16
// Date of Last Modification : 1/16/16
// -------------------------------------------------------------------------------------------------------------------- 
// Purpose - Implementation file for poly.h, implements an abstract polynomial class
// -------------------------------------------------------------------------------------------------------------------- 
// Notes on specifications, special algorithms, and assumptions.
// -1. If a user inputs a negative value for an exponent, that number is treated as an absolute value
// -2. Assumed to be compiled and ran on Linux
// --------------------------------------------------------------------------------------------------------------------

#include "poly.h"

// ------------------------------------Default Constructor----------------------------------------------- 
// Description: Instatiates  0x^0 Polynomial
// -------------------------------------------------------------------------------------------------------------
Poly::Poly()                   
{
    po = 1;                                                                     //initialize power of class instance to 0
    co = 0;                                                                             //initialize coefficient of class instance to 0
    arr = new int[po];                                                               //make a new array of size one 
    arr[0] = co;                                                                             //save the value of co to the first element
}

// ------------------------------------Dual Constructor----------------------------------------------- 
// Description: Instantiates Polynomial according to user input
//  Negative exponents treated as absolute value
// -------------------------------------------------------------------------------------------------------------
Poly::Poly(int coef, int power) 
{
    (power < 0) ? po = -(power - 1) : po = power + 1;           //abs value of a negative exponent
    co = coef;                                                                              //sets coef to user
    arr = new int[po]();                                                              //recieves B(3, 4) so should be at element subscript 4
    arr[po - 1] = co;
}

// ------------------------------------Coefficient Constructor----------------------------------------------- 
// Description: Instantiates user Coefficient to the 0th power.
// -------------------------------------------------------------------------------------------------------------
Poly::Poly(int coef)          
{
    co = coef;
    po = 1;
    arr = new int[po]();
    arr[0] = co;
}

// ------------------------------------Copy Constructor----------------------------------------------- 
// Description: Deep copy of calling Polynomial
// -------------------------------------------------------------------------------------------------------------
Poly::Poly(const Poly &obj) 
{
    po = obj.po;
    arr = new int[po];

    for(int i = 0; i < po; i++)                                                         //deep copy
        arr[i] = obj.arr[i];   
}

// ------------------------------------Destructor----------------------------------------------- 
// Description: Deletes contents of arr
// -------------------------------------------------------------------------------------------------------------
Poly::~Poly()
{
    delete [] arr;
}

// ------------------------------------Overloaded <<----------------------------------------------- 
// Description: Displays entire polynomial
//  Displays only 0 if every coefficient is zero
// -------------------------------------------------------------------------------------------------------------
ostream &operator<<(ostream &out, const Poly &rhs)    
{ 
    bool pZero = false;

    for(int i = rhs.po -1; i > -1; i--)
    {
        if(rhs.arr[i] != 0)
        {
            pZero = true;
            (rhs.arr[i] < 0) ? out << " " : out << " +";
            out << rhs.arr[i];

            if(i == 0)
                continue;
            else if(i == 1)
                out << "x";
            else out << "x^" << i; 
        }
        else continue;
    }
    if(pZero == false)
        out << 0;

    return out;
} 

// ------------------------------------Overloaded >>----------------------------------------------- 
// Description: Takes two ints and saves them to corresponding location in specified polynomial
//  int John : represents the coefficient of the power "zoeller"
//   int Zoeller : represents the power, or the subscript, of the inputted polynomial
//    resize(int, Poly&) : called if the newest power is greater than the previous greatest (see resize comments)
//     if zoeller is any negative number (including -1, so long as john is not also -1) assumed to be absolute value
// -------------------------------------------------------------------------------------------------------------
istream &operator>>(istream &in, Poly &rhs)     
{
    int john, zoeller;

    while(in.peek()) 
    {
        in >> john >> zoeller;

        if(john == -1 && zoeller == -1) 
            break;

        if(zoeller < 0)
            zoeller = -zoeller; //absolute value for negative exponent

        if(zoeller >= rhs.po)   
            resize(zoeller + 1, rhs);

        rhs.co = john;
        rhs.arr[zoeller] = john;
    }
    return in;
}

// ------------------------------------Overloaded Assignment----------------------------------------------- 
// Description: Avoids self assignment, sets object to exact copy of Poly & right
// -------------------------------------------------------------------------------------------------------------
const Poly &Poly::operator=(const Poly &right)   
{
    if(this != &right)
    {
        po = right.po;
        arr = new int[po];

        for(int i = 0; i < po; i++)       
            arr[i] = right.arr[i];
    }
    return *this;
}

// ------------------------------------Overloaded +=----------------------------------------------- 
// Description: Adds rhs to *this by calling the overloaded + operator (see + notes)
// -------------------------------------------------------------------------------------------------------------
Poly &Poly::operator+=(const Poly &rhs)        
{
    *this = *this + rhs;
    return *this;
}

// ------------------------------------Overloaded -=----------------------------------------------- 
// Description: Subtracts Poly rhs from *this via the overloaded - operator
// -------------------------------------------------------------------------------------------------------------
Poly &Poly::operator-=(const Poly &rhs)
{
    *this = *this - rhs;
    return *this;
}

// ------------------------------------Overloaded *=----------------------------------------------- 
// Description:  Mulitplies *this and rhs via the overloaded * operator
// -------------------------------------------------------------------------------------------------------------
Poly &Poly::operator*=(const Poly &rhs)   
{
    *this = *this * rhs;
    return *this;
}

// ------------------------------------Overloaded +----------------------------------------------- 
// Description: returns Poly sum (result of adding two polynomials)
//  Poly sum is allocated based on the larger of the two Poly objects being added
//   Poly sum is filled based on the same principle, after the smaller object has exhausted its elements...
//    ...another for loop is used to exhaust all the elements of the larger.
//     I did this to ensure that i would not access non-existent elements
//      The first outer for loop covers the right object being larger, The second Outer covers the opposite...
//       ... and the third is called if the two are the same size
// -------------------------------------------------------------------------------------------------------------
Poly Poly::operator+(const Poly &right)    
{
    Poly sum;

    (right.po >= po) ? sum.arr = new int[sum.po = right.po] : sum.arr = new int[sum.po = po];

    if(right.po < po)
    {
        for(int i = 0; i < right.po; i++)
        {
            sum.arr[i] = right.arr[i] + arr[i];
            if(i == right.po - 1)
                for(int j = i + 1; j < po; j++)
                    sum.arr[j] = arr[j];
        }}                                                                         //end if, for
    else if(right.po > po)
    {
        for(int i = 0; i < po; i++)
        {
            sum.arr[i] = right.arr[i] + arr[i];
            if(i == po -1)
                for(int j = i + 1; j < right.po; j++)
                    sum.arr[j] = right.arr[j];
        }}                                                                             //end if, for, if
    else
        for(int i = 0; i < sum.po; i++)
            sum.arr[i] = arr[i] + right.arr[i];

    return sum;
}

// ------------------------------------Overloaded -   ----------------------------------------------- 
// Description: Returns Poly diff (the result of subtracting right from calling Polynomial)
//  Poly diff is filled in almost the exact same manner as the overloaded + operator 
//   The only difference being that elements are obviously being subtracted and not added. 
// -------------------------------------------------------------------------------------------------------------
Poly Poly::operator-(const Poly &right)     
{
    Poly diff;

    (right.po >= po) ? diff.arr = new int[diff.po = right.po] : diff.arr = new int[diff.po = po];

    if(right.po < po)
    {
        for(int i = 0; i < right.po; i++)
        {
            diff.arr[i] = arr[i] - right.arr[i];
            if(i == right.po - 1)
                for(int j = i + 1; j < po; j++)
                    diff.arr[j] = arr[j];
        }}
    else if(right.po > po)
    {
        for(int i = 0; i < po; i++)
        {
            diff.arr[i] = arr[i] - right.arr[i];
            if(i == po - 1)
                for(int j = i + 1; j < right.po; j++)
                    diff.arr[j] = -right.arr[j];
        }}
    else 
        for(int i = 0; i < diff.po; i++)
            diff.arr[i] = arr[i] - right.arr[i];

    return diff;
}

// ------------------------------------Overloaded  * ----------------------------------------------- 
// Description: Poly product allocated based on the addition of the largest powers of its multipliers
//  The sum of this addition minus 1 (or else the largest exponent would be 1 larger than it should be)...
//   ... determines the max power of Poly prod
//    The for loops work through each element of each multiplier without accessing non-existent elements
// -------------------------------------------------------------------------------------------------------------
Poly Poly::operator*(const Poly &right)  
{
    Poly prod;
    prod.po = (right.po + po) - 1; 
    prod.arr = new int[prod.po];

    for(int i = 0; i < po; i++)
        for(int j = 0; j < right.po; j++)
            prod.arr[j + i] += arr[i] * right.arr[j]; 

    return prod;
}

// ------------------------------------Overloaded == ----------------------------------------------- 
// Description: Almost exact same logic as the + and - operators.  Works through the entire contents of...
//  ...whichever Poly is smaller, comparing it to the larger Poly's coefficients along the way. If at any point...
//   ... these two values differ, return false. 
//    KEY: As soon as one of the arrays is exhausted, I check the rest of the contents of the other array to make...
//      ... sure there are no remaining non-zero coefficients.  If there are I return false. 
//       I REALIZE that this is inefficient if the larger array has 200 elements with zero coefficients. However...
//        ...if a user makes a poly that looks like this "5x^7" with a constructor that looks like this "A(0, 200)"
//         it would be impossible for the compiler to know if one of those extra 193 elements wasnt a zero without 
//         checking all of them.  
//          ALSO if I just did this "if(rhs.po != po) return false" I could end up calling the above example not equal 
//           to an identical one without 197 extra elements.   Example:  0000000051 == 51 
// -------------------------------------------------------------------------------------------------------------
bool Poly::operator==( const Poly &rhs) const   
{
    if(po > rhs.po)
    {
        for(int i = 0; i < rhs.po; i++)
        {
            if(arr[i] != rhs.arr[i])
                return false;
            if(i == rhs.po - 1)
                for(int j = i + 1; j < po; j++)
                    if(arr[j] != 0)
                        return false;
        }
    }
    else if(rhs.po > po)
    {
        for(int i = 0; i < po; i++)
        {
            if(arr[i] != rhs.arr[i])
                return false;
            if(i == po - 1)
                for(int j = i + 1; j < rhs.po; j++)
                    if(rhs.arr[j] != 0)
                        return false;
        }
    }
    else
        for (int i = 0; i < po; i++)
            if(arr[i] != rhs.arr[i])
                return false;

    return true;
}

// ------------------------------------Overloaded != ----------------------------------------------- 
// Description: Calls overloaded == .  returns opposite of that result.
// -------------------------------------------------------------------------------------------------------------
bool Poly::operator!=( const Poly &rhs) const     
{
    if(*this == rhs)
        return false; 
    else return true;
}

// ------------------------------------SetCoeff----------------------------------------------- 
// Description: Sets the coefficient of a user entered power.  If user enters a negative power...
//  ...it is treated as its absolute value.  Resize is called if the new element is bigger than the current size of the Poly.
// -------------------------------------------------------------------------------------------------------------
void Poly::setCoeff(int newCoeff, int power) 
{
    int elem;

    (power >= 0) ? elem = power : elem = -power;

    if(elem >= po)
        resize(elem + 1, *this);

    arr[power] = newCoeff;
}

// ------------------------------------GetCoeff----------------------------------------------- 
// Description: negatives powers treated as absolute values, as long as the requested power is not....
//  ... bigger than the highest power of the calling Poly, its coefficient is returned. Otherwise return NULL
// -------------------------------------------------------------------------------------------------------------
int Poly::getCoeff(int power) 
{
    int elem;

    (power >= 0) ? elem = power : elem = -power;

    if(elem < po)
        return arr[elem];
    else return NULL;
}

// ------------------------------------resize----------------------------------------------- 
// Description: Uses assignment operator to copy contents of right into a temp Poly
//  Resets rights elements to all zeros with the new appropriate size.  Right is then refilled with its...
//   ... old elements from temp.  The coefficient of the new size is then set in either setCoeff, or the >> operator
//    depending on which called resize(). 
// -------------------------------------------------------------------------------------------------------------
void resize(int size, Poly &right)    
{
    Poly temp = right;
    right.po = size;
    right.arr = new int[right.po]();

    for(int i = 0; i < temp.po; i++)
        right.arr[i] = temp.arr[i];
}













