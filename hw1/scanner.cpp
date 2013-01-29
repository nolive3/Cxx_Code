#include "scanner.h"
#include <sstream>

Scanner::Scanner(std::istream& input) : source(input), ungot()
{
    //ctor
}

Scanner::Scanner() : Scanner(std::cin)
{
    //ctor
}

Scanner::~Scanner()
{
    //dtor
}

void Scanner::unget(Token t)
{
    ungot.push(t);
}

Token Scanner::getNewToken()
{
    char ch = source.peek();
    if(ch==EOF){
        source.clear();
        std::string s;
        source>>s;
        return Token("INVALID", s);
    }
    if(isdigit(ch)){
        std::stringstream ss;
        double i;
        source >> i;
        std::string s;
        ss<<i;
        ss>>s;
        Token T("NUMBER", s);
        return T;
    }else{
        while(true){
            std::stringstream ss;
            char c = source.get();
            std::string res;
            ss<<c;
            ss>>res;
            switch(c){
            case '+':
            case '-':
                return Token("ADDOP", res);
            case '*':
            case '/':
                return Token("MULTOP", res);
            case '\n':
            case '\r':
                return Token("EOL", res);
            case 'q':
                return Token("END", res);
            case ' ':
            case '\t':
                break;


            default:
                return Token("INVALID", res);
            }
        }
    }
    return Token("INVALID");
}

Token Scanner::getNextToken()
{
    if(ungot.size()>0){
        Token t = ungot.top();
        ungot.pop();
        return t;
    }
    Token t = getNewToken();
    return t;
}
