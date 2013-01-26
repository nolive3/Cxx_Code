#include "token.h"

Token::Token(std::string new_type) : token_type(new_type), token_value()
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
