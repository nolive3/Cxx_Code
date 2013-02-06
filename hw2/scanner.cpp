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
            return Token(EOF);
        }
        case '+':
        case '-':
            source.get();
            return Token(Token::ADDOP, ch);
        case '*':
        case '/':
            source.get();
            return Token(Token::MULTOP, ch);
        case '\n':
        case '\r':
            source.get();
            return Token(Token::EOL, ch);
        case '(':
            source.get();
            return Token(Token::LPAR, ch);
        case ')':
            source.get();
            return Token(Token::RPAR, ch);
        case 'q':
            source.get();
            return Token(Token::END, ch);
        case ' ':
        case '\t':
            source.get();
            continue;
        default:
            return Token(Token::CHAR, source.get());
        }
    }
    return Token();
}

Token Scanner::getNextToken()
{
    Token t;
    do{
        if(ungot.size()>0){
            t = ungot.top();
            ungot.pop();
        }else{
            t = getNewToken();
        }
    }while(!t.valid());
    return t;
}
