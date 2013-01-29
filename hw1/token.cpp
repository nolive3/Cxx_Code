#include "token.h"

Token::Token(token_t new_type) : Token(new_type, "nothing")
{
    //ctor
}

Token::Token(std::string new_val) : Token(INVALID, new_val)
{
    //ctor
}

Token::Token(token_t new_type, std::string new_val) : token_type(new_type), token_value(new_val)
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

std::ostream& operator<<(std::ostream& output, const Token::token_t& t) {
    switch(t){
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
    case Token::TERM:
        output<<"TERM";
        break;
    case Token::EXPR:
        output<<"EXPR";
        break;
    case Token::INVALID:
        output<<"INVALID";
        break;
    default:
        output<<"BAD_TYPE";
        break;
    }
    return output;
}
