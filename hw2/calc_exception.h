#ifndef CALC_EXCEPTION_H
#define CALC_EXCEPTION_H

#include <stdexcept>
#include <string>
#include <iostream>
#include "debugvars.h"


class calc_exception : public std::logic_error
{
        friend std::ostream& operator<<(std::ostream& out, const calc_exception& ex);
    public:
        calc_exception(std::string msg, unsigned int col, unsigned int line);
        virtual ~calc_exception();
        unsigned int col() const { return m_col; }
        std::string message() const { return m_message; }
        unsigned int line() const { return m_line; }
    protected:
    private:
        std::string m_message;
        unsigned int m_col;
        unsigned int m_line;
};

#endif // CALC_EXCEPTION_H
