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

    Token t = line();

    if(t.type() == Token::END){
        output<<"Good bye!"<<std::endl;
        return false;
    }

    if(t.type() == Token::EXPR){
        Fraction res = t.value().f;

        if(res.is_integer()){
            output<<"The result is: "<<(int)res<<std::endl;
        } else {
            output<<"The result is: "<<res<<std::endl;
        }
        return true;
    }
    output<<"bad input! D:"<<std::endl;
    Token clr;
    while((clr=scan_stream.getNextToken()).type()!=Token::EOL){
    }
    return true;
}


Token Calculator::line()
{
    Token t = expr();
    if(t.valid()){
        Token next = scan_stream.getNextToken();
        if(next.type() == Token::EOL){
            return t;
        }
        scan_stream.unget(next);
        scan_stream.unget(t);
    }
    t = scan_stream.getNextToken();
    if(t.type() == Token::END){
        return t;
    }
    scan_stream.unget(t);
    return Token();
}
Token Calculator::expr()
{
    Token res(Token::EXPR);
    Token t = scan_stream.getNextToken();
    if(t.type() != Token::EXPR){
        scan_stream.unget(t);
        t = term();
    }
    if(t.valid()){
        Token a = addop();
        res = t.value().f;
        while(a.valid()){
            t = term();
            if(!t.valid()){
                scan_stream.unget(a);
                scan_stream.unget(res);
                return Token();
            }
            switch(a.value().s){
            case '+':
                res = res.value().f + t.value().f;
                break;
            case '-':
                res = res.value().f - t.value().f;
                break;
            default:
                scan_stream.unget(t);
                scan_stream.unget(a);
                scan_stream.unget(res);
                return Token();
            }
            a = addop();
        }
        return res;
    }
    return Token();
}
Token Calculator::term()
{
    Token res(Token::TERM);
    Token f = scan_stream.getNextToken();
    if(f.type() != Token::TERM){
        scan_stream.unget(f);
        f = factor();
    }
    if(f.valid()){
        Token m = mulop();
        res = f.value().f;
        while(m.valid()){
            f = factor();
            if(!f.valid()){
                scan_stream.unget(m);
                scan_stream.unget(res);
                return Token();
            }
            switch(m.value().s){
            case '*':
                res = res.value().f * f.value().f;
                break;
            case '/':
                res = res.value().f / f.value().f;
                break;
            default:
                scan_stream.unget(f);
                scan_stream.unget(m);
                scan_stream.unget(res);
                return Token();
            }
            m = mulop();
        }
        return res;
    }
    return Token();
}
Token Calculator::factor()
{
    Token res(Token::FACTOR);
    Token num = number();
    if(num.valid()){
        res = num.value().f;
        return res;
    }
    Token par = scan_stream.getNextToken();
    if(par.type()==Token::LPAR){

    }
    return Token();
}
Token Calculator::addop()
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
