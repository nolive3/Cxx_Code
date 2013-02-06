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
        return res = num.value().f;
    }
    Token par = scan_stream.getNextToken();
    if(par.type()==Token::LPAR){
        Token exp = expr();
        if(exp.valid()){
            Token par2 = scan_stream.getNextToken();
            if(par2.type()==Token::RPAR){
                return res = exp.value().f;
            }
            scan_stream.unget(par2);
            scan_stream.unget(exp);
        }
    }
    scan_stream.unget(par);
    return Token();
}
Token Calculator::addop()
{
    Token a = scan_stream.getNextToken();
    if(a.type() == Token::ADDOP){
        return a;
    }
    scan_stream.unget(a);
    return Token();
}
Token Calculator::mulop()
{
    Token m = scan_stream.getNextToken();
    if(m.type() == Token::MULTOP){
        return m;
    }
    scan_stream.unget(m);
    return Token();
}
Token Calculator::number()
{
    Token n = scan_stream.getNextToken();
    if(n.type() == Token::NUMBER){
        return n;
    }
    scan_stream.unget(n);
    n = fraction();
    if(n.valid()){
        return n;
    }
    return Token();
}
Token Calculator::fraction()
{
    Token f = scan_stream.getNextToken();
    if(f.type() == Token::CHAR && f.value().s == 'F'){
        Token par = scan_stream.getNextToken();
        if(par.type() == Token::LPAR){
            Token n1 = factor();
            if(n1.valid()){
                Token div = scan_stream.getNextToken();
                if(div.type() == Token::MULTOP && div.value().s == '/'){
                    Token n2 = factor();
                    if(n2.valid()){
                        Token par2 = scan_stream.getNextToken();
                        if(par2.type() == Token::RPAR){
                            return Token(Token::NUMBER, n1.value().f/n2.value().f);
                        }
                        scan_stream.unget(par2);
                        scan_stream.unget(n2);
                    }
                }
                scan_stream.unget(div);
                scan_stream.unget(n1);
            }
        }
        scan_stream.unget(par);
    }
    scan_stream.unget(f);
    return Token();
}
