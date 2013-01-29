#include "token.h"

Token::Token(std::string new_type) : token_type(new_type), token_value()
{
    //ctor
}

Token::Token(std::string new_type, std::string new_val) : token_type(new_type), token_value(new_val)
{
    //ctor
}

Token::Token() : Token("INVALID")
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
    return token_type != "INVALID";
}

Token& Token::operator=(const Token& rhs)
{
    if (this == &rhs) return *this; // handle self assignment
    Token tmp(rhs);
    Token::swap(*this,tmp);
    return *this;
}

Token& Token::operator=(const std::string& val)
{
    token_value = val;
    return *this;
}

void Token::swap(Token& a, Token& b){
    std::swap(a.token_type, b.token_type);
    std::swap(a.token_value, b.token_value);
}

std::ostream& operator<<(std::ostream& output, const Token& t) {
    output <<  t.token_type << "(" << t.token_value <<")";
    return output;
}
