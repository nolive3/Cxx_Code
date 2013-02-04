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
        Token expr();
        Token term();
        Token factor();
        Token mulop();
        Token addop();
        Scanner& scan_stream;
};

#endif // CALCUATOR_H
