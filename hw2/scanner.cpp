#include "scanner.h"
#include "fraction.h"
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
        return Token(s);
    }
    if(isdigit(ch)){
        std::stringstream ss;
        double i;
        source >> i;
        std::string s;
        ss<<i;
        ss>>s;
        Token T(Token::NUMBER, s);
        return T;
    }else{
        while(true){
            std::stringstream ss;
            char c = source.get();
            std::string res;
            ss<<c;
            ss>>res;
            switch(c){
            case 'F':
                int num, den;
                source>>"(">>num>>"/">>den>>")";
                return Token(Token::FRACTION, Fraction(num, den));
            case '+':
            case '-':
                return Token(Token::ADDOP, res);
            case '*':
            case '/':
                return Token(Token::MULTOP, res);
            case '\n':
            case '\r':
                return Token(Token::EOL, res);
            case 'q':
                return Token(Token::END, res);
            case ' ':
            case '\t':
                break;


            default:
                return Token(res);
            }
        }
    }
    return Token();
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
