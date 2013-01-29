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
        output<<"The answer is: "<<res.value()<<std::endl;
    }else{
        Token END = scan_stream.getNextToken();
        if(END.type()=="END"){
            output<<"Goodbye!"<<std::endl;
            return false;
        }else{
            output<<"Invalid input!"<<std::endl;
        }
        scan_stream.unget(END);
    }
    Token clr;
    while((clr=scan_stream.getNextToken()).type()!="EOL"){
    }
    return true;
}


Token Calculator::expr()
{
    Token T = term();
    if(T.valid()){
        Token A = addop();
        if(A.valid()){
            Token E = expr();
            if(E.valid()){
                Token END = scan_stream.getNextToken();
                if(END.type() == "EOL"){
                    std::stringstream slop;
                    std::stringstream srop;
                    std::stringstream sres;
                    slop<<T.value();
                    double lop;
                    slop>>lop;
                    srop<<E.value();
                    double rop;
                    srop>>rop;
                    if(A.value()=="+"){
                        sres<<lop+rop;
                    }else{
                        sres<<lop-rop;
                    }
                    std::string res;
                    sres>>res;
                    Token exp("EXPR", res);
                    scan_stream.unget(END);
                    return exp;
                }else{
                    scan_stream.unget(END);
                    scan_stream.unget(E);
                    scan_stream.unget(A);
                    scan_stream.unget(T);
                }
            }else{
                scan_stream.unget(A);
                scan_stream.unget(T);
            }
        }else{
            Token END = scan_stream.getNextToken();
            if(END.type() == "EOL"){
                scan_stream.unget(END);
                return T;
            }else{
                scan_stream.unget(END);
                scan_stream.unget(T);
            }
        }
    }
    return Token();
}
Token Calculator::term()
{
    Token F = factor();
    if(F.valid()){
        Token M = mulop();
        if(M.valid()){
            Token T = term();
            if(T.valid()){
                std::stringstream slop;
                std::stringstream srop;
                std::stringstream sres;
                slop<<F.value();
                double lop;
                slop>>lop;
                srop<<T.value();
                double rop;
                srop>>rop;
                if(M.value()=="*"){
                    sres<<lop*rop;
                }else{
                    sres<<lop/rop;
                }
                std::string res;
                sres>>res;
                Token ter("TERM", res);
                return ter;
            }else{
                scan_stream.unget(M);
                scan_stream.unget(F);
            }
        }else{
            return F;
        }
    }
    return Token();
}
Token Calculator::factor()
{
    Token N = scan_stream.getNextToken();
    if(N.type()=="NUMBER"){
        return N;
    }else{
        scan_stream.unget(N);
    }
    return Token();
}
Token Calculator::mulop()
{
    Token M = scan_stream.getNextToken();
    if(M.type()=="MULTOP"){
        return M;
    }else{
        scan_stream.unget(M);
    }
    return Token();
}
Token Calculator::addop()
{
    Token A = scan_stream.getNextToken();
    if(A.type()=="ADDOP"){
        return A;
    }else{
        scan_stream.unget(A);
    }
    return Token();
}
