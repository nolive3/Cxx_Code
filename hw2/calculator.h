#ifndef CALCUATOR_H
#define CALCUATOR_H
#include "scanner.h"
#include <iostream>


class Calculator
{
    public:
        Calculator() = delete;
        Calculator(const Calculator&) = delete;
        Calculator operator=(const Calculator&) = delete;
        Calculator(Scanner& source);
        virtual ~Calculator();
        bool run(std::ostream& output);   //read one expression from the stream, print result to output, return if the expression was exit
    protected:
    private:
        Token line(); // Fraction
        Token expr(); // Fraction
        Token term(); // Fraction
        Token factor(); // Fraction
        Token mulop(); // char
        Token addop(); // char
        Token number(); // Fraction
        Token fraction(); // Fraction
        Scanner& scan_stream;
};

#endif // CALCUATOR_H
