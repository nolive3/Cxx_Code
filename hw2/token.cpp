#include "token.h"

Token::Token(token_t new_type) : Token(new_type, '\0')
{
    //ctor
}

Token::Token(char new_val) : Token(INVALID, new_val)
{
    //ctor
}

Token::Token(Fraction new_val) : Token(INVALID, new_val)
{
    //ctor
}

Token::Token(int new_val) : Token(INVALID, new_val)
{
    //ctor
}

Token::Token(token_t new_type, char new_val) : token_type(new_type), token_value{new_val}
{
}

Token::Token(token_t new_type, Fraction new_val) : token_type(new_type), token_value{new_val}
{
    //ctor
}

Token::Token(token_t new_type, int new_val) : token_type(new_type), token_value{Fraction(new_val)}
{
    //ctor
}

Token::Token() : Token(INVALID)
{
    //ctor
}

Token::~Token()
{
    //dtor
}

Token::Token(const Token& other) : token_type(other.token_type), token_value(other.token_value)
{
    //copy ctor
}

bool Token::valid()
{
    return token_type != Token::INVALID;
}

Token& Token::operator=(const Token& rhs)
{
    if (this == &rhs) return *this; // handle self assignment
    Token tmp(rhs);
    Token::swap(*this,tmp);
    return *this;
}

Token& Token::operator=(const char& val)
{
    token_value.s = val;
    return *this;
}
Token& Token::operator=(const int& val)
{
    token_value.f = val;
    return *this;
}
Token& Token::operator=(const Fraction& val)
{
    token_value.f = val;
    return *this;
}



void Token::swap(Token& a, Token& b){
    std::swap(a.token_type, b.token_type);
    std::swap(a.token_value, b.token_value);
}

std::ostream& operator<<(std::ostream& output, const Token& t) {
    output <<  t.token_type << "(";
    switch(t.token_type){
    case Token::INVALID:
        output<<"INVALID";
        break;
    case Token::END:
        output<<"END";
        break;
    case Token::EOL:
        output<<"EOL";
        break;
    case Token::ADDOP:
        output<<t.token_value.s;
        break;
    case Token::MULTOP:
        output<<t.token_value.s;
        break;
    case Token::NUMBER:
        output<<t.token_value.f;
        break;
    case Token::FACTOR:
        output<<t.token_value.f;
        break;
    case Token::TERM:
        output<<t.token_value.f;
        break;
    case Token::EXPR:
        output<<t.token_value.f;
        break;
    case Token::LPAR:
        output<<t.token_value.s;
        break;
    case Token::RPAR:
        output<<t.token_value.s;
        break;
    case Token::CHAR:
        output<<t.token_value.s;
        break;
    default:
        output<<"BAD_TYPE";
        break;
    }
    output <<")";
    return output;
}

std::ostream& operator<<(std::ostream& output, const Token::token_t& t) {
    switch(t){
    case Token::INVALID:
        output<<"INVALID";
        break;
    case Token::END:
        output<<"END";
        break;
    case Token::EOL:
        output<<"EOL";
        break;
    case Token::ADDOP:
        output<<"ADDOP";
        break;
    case Token::MULTOP:
        output<<"MULTOP";
        break;
    case Token::NUMBER:
        output<<"NUMBER";
        break;
    case Token::FACTOR:
        output<<"FACTOR";
        break;
    case Token::TERM:
        output<<"TERM";
        break;
    case Token::EXPR:
        output<<"EXPR";
        break;
    case Token::LPAR:
        output<<"LPAR";
        break;
    case Token::RPAR:
        output<<"RPAR";
        break;
    case Token::CHAR:
        output<<"CHAR";
        break;
    default:
        output<<"BAD_TYPE";
        break;
    }
    return output;
}
