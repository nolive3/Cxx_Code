#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H
#include <unordered_map>
#include "fraction.h"

class Symbol_Table
{
    public:
        struct symbol_t {std::string name = ""; Fraction val = 0; bool writen = false;};
        friend symbol_t operator+(const symbol_t& a, const symbol_t& b){
                                Symbol_Table::symbol_t res;
                                res.writen = true;
                                res.val = a.val+b.val;
                                res.name = a.name + "+" + b.name;
                                return res;
                               };
        Symbol_Table() = default;
        friend std::ostream& operator<<(std::ostream& output, const Symbol_Table::symbol_t& t);
        friend std::ostream& operator<<(std::ostream& output, const Symbol_Table& table);
    protected:
    private:
        std::unordered_map<std::string, symbol_t> table;
};

#endif // SYMBOL_TABLE_H
