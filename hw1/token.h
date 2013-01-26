#ifndef TOKEN_H
#define TOKEN_H
#include <string>

class Token
{
    public:
        Token(std::string new_type = "INVALID");
        Token() = delete;
        ~Token();
        Token(const Token& other);
        Token& operator=(const Token& other); // this is the only way to change the type of an existing token
        Token& operator=(const std::string& new_value); // assign a new value to the token
        std::string type() { return token_type; }
        std::string value() { return token_value; }
    protected:
    private:
        std::string token_type;
        std::string token_value;
        void swap(Token&, Token&);
};

#endif // TOKEN_H
