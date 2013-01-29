#ifndef TOKEN_H
#define TOKEN_H
#include <string>
#include <iostream>

class Token
{
    friend std::ostream& operator<<(std::ostream& output, const Token& t);
    public:
        Token(std::string new_type);
        Token(std::string new_type, std::string new_val);
        Token();
        ~Token();
        Token(const Token& other);
        Token& operator=(const Token& other); // this is the only way to change the type of an existing token
        Token& operator=(const std::string& new_value); // assign a new value to the token
        std::string type() { return token_type; }
        std::string value() { return token_value; }
        bool valid();
    protected:
    private:
        std::string token_type;
        std::string token_value;
        void swap(Token&, Token&);
};

#endif // TOKEN_H
