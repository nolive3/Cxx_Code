#include "calculator.h"
#include "calc_exception.h"
#include <sstream>

Calculator::Calculator(Scanner& source) : scan_stream(source)
{
    //ctor
}

Calculator::~Calculator()
{
    //dtor
}

bool Calculator::run(std::ostream& output, std::ostream& err)
{
    std::cerr << "---- ---- ---- Starting Line " << scan_stream.line() << " ---- ---- ----" << std::endl;
    try{
        Token t = line();
        if(t.type() == Token::END){
            output<<"Good bye!"<<std::endl;
            return false;
        }
        if(t.type() == Token::EXPR){
            Fraction res = t.value().f;

            if(res.is_integer()){
                output<<(int)res<<std::endl;
            } else {
                output<<res<<std::endl;
            }
        }
    } catch (calc_exception& e) {
        err << e << std::endl;
    }
    Token clr;
    while((clr=scan_stream.getNextToken()).type()!=Token::EOL){
            std::cerr << "Destroying: " << clr << std::endl;
    }
    return true;
}


Token Calculator::line()
{
    Token t;
    t = scan_stream.getNextToken();
    if(t.type() == Token::END){
        return t;
    }
    scan_stream.unget(t);
    t = expr();
    if(t.valid()){
        Token next = scan_stream.getNextToken();
        if(next.type() == Token::EOL || (next.type() == Token::CHAR && next.value().s == '#')){
            scan_stream.unget(next);
            return t;
        }
        scan_stream.unget(next);
        throw calc_exception("Additional input after expression", scan_stream.col(), scan_stream.line());
    }
    scan_stream.unget(t);
    throw calc_exception("Bad expression", scan_stream.col(), scan_stream.line());
    return Token();
}
Token Calculator::expr()
{
    Token res(Token::EXPR, 0, 0);
    Token t = scan_stream.getNextToken();
    if(t.type() != Token::EXPR){
        scan_stream.unget(t);
        t = term();
    }
    if(t.valid()){
        Token a = addop();
        res = t.value().f;
        res.len(t.len());
        while(a.valid()){
            t = term();
            if(!t.valid()){
                throw calc_exception("Expecting TERM", scan_stream.col(), scan_stream.line());
            }
            switch(a.value().s){
            case '+':
                res = res.value().f + t.value().f;
                break;
            case '-':
                res = res.value().f - t.value().f;
                break;
            default:
                throw calc_exception("Invalid ADDOP type", scan_stream.col(), scan_stream.line());
            }
            res.len(t.len()+a.len());
            a = addop();
        }
        return res;
    }
    throw calc_exception("Expecting TERM", scan_stream.col(), scan_stream.line());
}
Token Calculator::term()
{
    Token res(Token::TERM, 0, 0);
    Token f = scan_stream.getNextToken();
    if(f.type() != Token::TERM){
        scan_stream.unget(f);
        f = factor();
    }
    if(f.valid()){
        Token m = mulop();
        res = f.value().f;
        res.len(f.len());
        while(m.valid()){
            f = factor();
            if(!f.valid()){
                throw calc_exception("Expecting FACTOR", scan_stream.col(), scan_stream.line());
            }
            switch(m.value().s){
            case '*':
                res = res.value().f * f.value().f;
                break;
            case '/':
                res = res.value().f / f.value().f;
                break;
            default:
                throw calc_exception("Invalid MULTOP type", scan_stream.col(), scan_stream.line());
            }
            res.len(f.len()+m.len());
            m = mulop();
        }
        return res;
    }
    return Token();
}
Token Calculator::factor()
{
    Token res(Token::FACTOR, 0, 0);
    Token num = number();
    if(num.valid()){
        res.len(num.len());
        return res = num.value().f;
    }
    Token par = scan_stream.getNextToken();
    if(par.type()==Token::LPAR){
        Token exp;
        try{
             exp = expr();
        } catch (calc_exception& e) {
            throw calc_exception("Expecting EXPRESSION", scan_stream.col(), scan_stream.line());
        }
        Token par2 = scan_stream.getNextToken();
        if(par2.type()==Token::RPAR){
            res.len(par.len()+exp.len()+par2.len());
            return res = exp.value().f;
        }
        scan_stream.unget(par2);
        throw calc_exception("Expecting ')'", scan_stream.col(), scan_stream.line());
    }
    scan_stream.unget(par);
    throw calc_exception("No Valid FACTOR", scan_stream.col(), scan_stream.line());
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
    int col;
    if(f.type() == Token::CHAR && f.value().s == 'F'){
        Token par = scan_stream.getNextToken();
        if(par.type() == Token::LPAR){
            Token n1;
            try{
                n1 = factor();
            } catch (calc_exception& e) {
                throw calc_exception("Fraction format requires FACTOR", scan_stream.col(), scan_stream.line());
            }
            Token div = scan_stream.getNextToken();
            if(div.type() == Token::MULTOP && div.value().s == '/'){
                Token n2;
                try{
                    n2 = factor();
                } catch (calc_exception& e) {
                    throw calc_exception("Fraction format requires FACTOR", scan_stream.col(), scan_stream.line());
                }
                    Token par2 = scan_stream.getNextToken();
                    if(par2.type() == Token::RPAR){
                        return Token(Token::NUMBER, n1.value().f/n2.value().f, f.len()+par.len()+n1.len()+div.len()+n2.len()+par2.len());
                    }
                    scan_stream.unget(par2);
                    col = scan_stream.col();
                    scan_stream.unget(n2);
                    throw calc_exception("Fraction format requires ')'", col, scan_stream.line());
            }
            scan_stream.unget(div);
            col = scan_stream.col();
            scan_stream.unget(n1);
            throw calc_exception("Fraction format requires '/'", col, scan_stream.line());
        }
        col = scan_stream.col();
        scan_stream.unget(par);
        throw calc_exception("Fraction format requires '('", col, scan_stream.line());
    }
    scan_stream.unget(f);
    return Token();
}
