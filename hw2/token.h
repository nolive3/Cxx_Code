#ifndef TOKEN_H
#define TOKEN_H
#include <string>
#include "fraction.h"
#include <iostream>

class Token
{
    public:
        union val_t {Fraction f; char s;};
        enum token_t {END, EOL, ADDOP, MULTOP, CHAR, FRACTION, NUMBER, TERM_FRACTION, EXPR_FRACTION, TERM, EXPR, LPAR, RPAR, INVALID};
        friend std::ostream& operator<<(std::ostream& output, const Token& t);
        friend std::ostream& operator<<(std::ostream& output, const Token::token_t& t);
        Token(token_t new_type);
        Token(token_t new_type, char new_val);
        Token(token_t new_type, Fraction new_val);
        Token(token_t new_type, int new_val);
        Token(char new_val);
        Token(Fraction new_val);
        Token(int new_val);
        Token();
        ~Token();
        Token(const Token& other);
        Token& operator=(const Token& other); // this is the only way to change the type of an existing token
        Token& operator=(const char& new_value); // assign a new value to the token
        Token& operator=(const Fraction& new_value); // assign a new value to the token
        Token& operator=(const int& new_value); // assign a new value to the token
        token_t type() { return token_type; }
        val_t& value() { return token_value; }
        bool valid();
    protected:
    private:

        token_t token_type;
        val_t token_value;
        void swap(Token&, Token&);
};

#endif // TOKEN_H
