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
    Token res = expr();
    if(res.valid()){
        Token END = scan_stream.getNextToken();
        if(END.type()==Token::EOL)
            output<<"The answer is: "<<res.value()<<std::endl;
        else
            output<<"Valid input was followed by garbage!"<<std::endl;
        scan_stream.unget(END);
    }else{
        Token END = scan_stream.getNextToken();
        if(END.type()==Token::END){
            output<<"Goodbye!"<<std::endl;
            return false;
        }else{
            output<<"Invalid input!"<<std::endl;
        }
        scan_stream.unget(END);
    }
    Token clr;
    while((clr=scan_stream.getNextToken()).type()!=Token::EOL){
    }
    return true;
}


Token Calculator::expr()
{
    Token E = Token(Token::EXPR);
    Token T = term();
    if(T.valid()){
            double lhs;
            std::string res;
            std::stringstream lhs_con;
            lhs_con<<T.value();
            lhs_con>>lhs;
            E = T.value();
            Token A = addop();
            while(A.valid()){
                std::stringstream res_con;
                std::stringstream rhs_con;
                double rhs;
                T = term();
                if(!T.valid()){
                    scan_stream.unget(A);
                    return E;
                }
                rhs_con<<T.value();
                rhs_con>>rhs;
                if(A.value() == "+"){
                    lhs+=rhs;
                }else{
                    lhs-=rhs;
                }
                res_con<<lhs;
                res_con>>res;
                E = res;
                A = addop();
            }
            return E;
    }
    return Token();
}
Token Calculator::term()
{
    Token T = Token(Token::TERM);
    Token F = factor();
    if(F.valid()){
            double lhs;
            std::string res;
            std::stringstream lhs_con;
            lhs_con<<F.value();
            lhs_con>>lhs;
            T = F.value();
            Token M = mulop();
            while(M.valid()){
                std::stringstream res_con;
                std::stringstream rhs_con;
                double rhs;
                F = factor();
                if(!F.valid()){
                    scan_stream.unget(M);
                    return T;
                }
                rhs_con<<F.value();
                rhs_con>>rhs;
                if(M.value() == "*"){
                    lhs*=rhs;
                }else{
                    lhs/=rhs;
                }
                res_con<<lhs;
                res_con>>res;
                T = res;
                M = mulop();
            }
            return T;
    }
    return Token();
}
Token Calculator::factor()
{
    Token N = scan_stream.getNextToken();
    if(N.type()==Token::NUMBER){
        return N;
    }else{
        scan_stream.unget(N);
    }
    return Token();
}
Token Calculator::mulop()
{
    Token M = scan_stream.getNextToken();
    if(M.type()==Token::MULTOP){
        return M;
    }else{
        scan_stream.unget(M);
    }
    return Token();
}
Token Calculator::addop()
{
    Token A = scan_stream.getNextToken();
    if(A.type()==Token::ADDOP){
        return A;
    }else{
        scan_stream.unget(A);
    }
    return Token();
}
