#ifndef SCANNER_H
#define SCANNER_H
#include <iostream>
#include "token.h"

class Scanner
{
    public:
        Scanner(std::istream& source = std::cin); // the selected stream will become unstable, continuing to use it afthe giving it to me would be inadvisable
        ~Scanner();
        Scanner(const Scanner& other) = delete; // cant copy an istream, so no copying Scanners
        Scanner() = delete;                     // need to know what stream to read from, use single optional argument constructor
        Scanner& operator=(const Scanner& other) = delete; // no assignment of istreams, so no assignment of Scanners, use a referance instead.
        Token getNextToken();
    protected:
    private:
        std::istream& source;
};

#endif // SCANNER_H
