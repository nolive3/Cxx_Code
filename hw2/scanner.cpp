#include "scanner.h"
#include "fraction.h"
#include <sstream>

Scanner::Scanner(std::istream& input) : line_no(1), col_no(1), prev_len(0), source(input), ungot()
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
    if(t.type() == Token::EOL){
        col_no = prev_len;
        line_no--;
        prev_len = 0;
    }else {
        col_no -= t.len();
    }
    ungot.push(t);
    for(int i = 0; i < depth; ++i) std::cerr << "\t"; std::cerr<< "Putting Back: " << t << std::endl;
}

Token Scanner::getNewToken()
{
    int s = 0;
    while(true){
        char ch = source.peek();
        if(isdigit(ch)){
            int i = 0;
            int len = 0;
            while(isdigit(ch)){
                i*=10;
                i+=ch-'0';
                len++;
                source.get();
                ch=source.peek();
            }
            Token T(Token::NUMBER, i, len+s);
            return T;
        }
        switch(ch){
        case EOF:
        {
            if(source.eof())
                return Token(Token::END, EOF);
            source.clear();
            return Token(EOF);
        }
        case '+':
        case '-':
            source.get();
            return Token(Token::ADDOP, ch, s+1);
        case '=':
            source.get();
            return Token(Token::ASSIGN, ch, s+1);
        case '*':
        case '/':
            source.get();
            return Token(Token::MULTOP, ch, s+1);
        case '\n':
        case '\r':
            source.get();
            return Token(Token::EOL, ch, s+1);
        case '(':
            source.get();
            return Token(Token::LPAR, ch, s+1);
        case ')':
            source.get();
            return Token(Token::RPAR, ch, s+1);
        case 'q':
            source.get();
            return Token(Token::END, ch, s+1);
        case ' ':
        case '\t':
            source.get();
            s++;
            continue;
        default:
            return Token(Token::CHAR, source.get(), s+1);
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
    if(t.type() == Token::EOL){
        prev_len = col_no;
        line_no++;
        col_no = 1;
    }else{
        col_no += t.len();
    }
    for(int i = 0; i < depth; ++i) std::cerr << "\t"; std::cerr<< "Returning: " << t << std::endl;
    return t;
}
