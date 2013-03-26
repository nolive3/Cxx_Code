#include "symbol_table.h"
#include <sstream>

std::ostream& operator<<(std::ostream& output, const Symbol_Table::symbol_t& t) {
    std::stringstream ss;
    ss << t.val;
    std::string s;
    ss >> s;
    output << "(" << t.name << ", " << (t.writen?s:"UNINITIALIZED") << ")";
    return output;
}
std::ostream& operator<<(std::ostream& output, const Symbol_Table& table) {
    output << "Symbol Table {";
    for(auto& t : table.table){
        output << t.second;
    }
    output << "}";
    return output;
}
