#include "calc_exception.h"

calc_exception::calc_exception(std::string msg, unsigned int ncol, unsigned int nline) : std::logic_error("Calculator Exception"), m_message(msg), m_col(ncol), m_line(nline)
{
    //ctor
}

calc_exception::~calc_exception()
{
    //dtor
}

std::ostream& operator<<(std::ostream& out, const calc_exception& ex)
{
    out << "Error at Line " << ex.line() << ", Column " << ex.col() << ": " << ex.message();
    return out;
}
