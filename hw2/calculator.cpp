#include "calculator.h"
#include <sstream>

Calculator::Calculator(Scanner& source) : scan_stream(source)
{
    //ctor
}

Calculator::~Calculator()
{
    //dtor
}

bool Calculator::run(std::ostream& output)
{
    output<<"Enter a formula: ";
    Token clr;
    while((clr=scan_stream.getNextToken()).type()!=Token::EOL){
    }
    return true;
}


Token Calculator::line()
{
    return Token();
}
Token Calculator::expr()
{
    return Token();
}
Token Calculator::term()
{
    return Token();
}
Token Calculator::factor()
{
    return Token();
}
Token Calculator::mulop()
{
    return Token();
}
Token Calculator::number()
{
    return Token();
}
Token Calculator::fraction()
{
    return Token();
}
