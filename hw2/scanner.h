#ifndef SCANNER_H
#define SCANNER_H
#include <iostream>
#include <stack>
#include "token.h"
#include "debugvars.h"

class Scanner
{
    public:
        Scanner(const Scanner& other) = delete; // cant copy an istream, so no copying Scanners
        Scanner();                     // need to know what stream to read from, use single optional argument constructor
        Scanner& operator=(const Scanner& other) = delete; // no assignment of istreams, so no assignment of Scanners, use a referance instead.
        Scanner(std::istream& source); // the selected stream will become unstable, continuing to use it afthe giving it to me would be inadvisable
        ~Scanner();
        Token getNextToken();
        void unget(Token);
        long line() const { return line_no; }
        long col() const { return col_no; }
    protected:
    private:
        long line_no;
        long col_no;
        long prev_len;
        Token getNewToken();
        std::istream& source;
        std::stack<Token> ungot;
};

#endif // SCANNER_H
