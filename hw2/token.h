#ifndef TOKEN_H
#define TOKEN_H
#include <string>
#include "fraction.h"
#include <iostream>
#include "debugvars.h"

class Token
{
    public:
        union val_t {Fraction f; char s;};
        enum token_t {ASSIGN, END, EOL, ADDOP, MULTOP, CHAR, NUMBER, TERM, FACTOR, EXPR, LPAR, RPAR, INVALID, RVAR, LVAR};
        friend std::ostream& operator<<(std::ostream& output, const Token& t);
        friend std::ostream& operator<<(std::ostream& output, const Token::token_t& t);
        Token(token_t new_type);
        Token(token_t new_type, char new_val, int = 1);
        Token(token_t new_type, Fraction new_val, int = 1);
        Token(token_t new_type, int new_val, int len = 1);
        Token(char new_val);
        Token(Fraction new_val);
        Token(int new_val);
        Token();
        ~Token() = default;
        Token(const Token& other) = default;
        Token& operator=(const Token& other) = default; // this is the only way to change the type of an existing token
        Token& operator=(const char& new_value); // assign a new value to the token
        Token& operator=(const Fraction& new_value); // assign a new value to the token
        Token& operator=(const int& new_value); // assign a new value to the token
        token_t type() { return token_type; }
        val_t& value() { return token_value; }
        bool valid();
        int len() const { return m_len; }
        void len(int dif) { m_len+=dif; }
    protected:
    private:
        int m_len;
        token_t token_type;
        val_t token_value;
};

#endif // TOKEN_H
