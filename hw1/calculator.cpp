#include "calculator.h"

Calculator::Calculator(std::istream source = std::cin)
{
    //ctor
}

Calculator::~Calculator()
{
    //dtor
}

Calculator::Calculator(const Calculator& other)
{
    //copy ctor
}

Calculator& Calculator::operator=(const Calculator& rhs)
{
    if (this == &rhs) return *this; // handle self assignment
    //assignment operator
    return *this;
}
