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
    while(true){
        char ch = source.peek();
        if(isdigit(ch)){
            int i;
            source >> i;
            Token T(Token::NUMBER, i);
            return T;
        }
        switch(ch){
        case EOF:
        {
            source.clear();
            std::string s;
            source>>s;
            return Token(EOF);
        }
        case 'F':
            source.get();
            return Token(Token::CHAR, 'F');
        case '+':
        case '-':
            source.get();
            return Token(Token::ADDOP, ch);
        case '*':
        case '/':
        case '\n':
        case '\r':
        case 'q':
        case ' ':
        case '\t':
        default:
            return Token();
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
