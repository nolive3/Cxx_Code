#ifndef CALCUATOR_H
#define CALCUATOR_H
#include "scanner.h"
#include <iostream>
#include <vector>
#include <string>
#include "debugvars.h"



class Calculator
{

    public:
        struct symbol_t {std::string name = ""; Fraction val = 0; bool writen = false;};
        friend std::ostream& operator<<(std::ostream& output, const std::vector<symbol_t>& vec);
        friend std::ostream& operator<<(std::ostream& output, const symbol_t& vec);
        Calculator() = delete;
        Calculator(const Calculator&) = delete;
        Calculator operator=(const Calculator&) = delete;
        Calculator(Scanner& source);
        std::vector<symbol_t> get_table() {return symbol_table;};
        virtual ~Calculator() = default;
        bool run(std::ostream& output, std::ostream& err);   //read one expression from the stream, print result to output, return if the expression was exit
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
        Token var(); // Fraction // the index if an LVAR is returned, the value if and RVAR is returned
        std::vector<symbol_t> symbol_table;
        Scanner& scan_stream;
};

#endif // CALCUATOR_H
