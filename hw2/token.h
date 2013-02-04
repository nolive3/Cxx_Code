#ifndef TOKEN_H
#define TOKEN_H
#include <string>
#include "fraction.h"
#include <iostream>

class Token
{
    public:
        enum token_t {END, EOL, ADDOP, MULTOP, FRACTION, NUMBER, TERM, EXPR, INVALID};
        friend std::ostream& operator<<(std::ostream& output, const Token& t);
        friend std::ostream& operator<<(std::ostream& output, const Token::token_t& t);
        Token(token_t new_type);
        Token(token_t new_type, std::string new_val);
        Token(std::string new_val);
        Token();
        ~Token();
        Token(const Token& other);
        Token& operator=(const Token& other); // this is the only way to change the type of an existing token
        Token& operator=(const std::string& new_value); // assign a new value to the token
        token_t type() { return token_type; }
        std::string value() { return token_value; }
        bool valid();
    protected:
    private:

        token_t token_type;
        std::string token_value;
        void swap(Token&, Token&);
};

#endif // TOKEN_H
