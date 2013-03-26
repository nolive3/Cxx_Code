#include "calculator.h"
#include "scanner.h"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <sstream>
#include <iterator>

/*My grammar for this iteration
LINE => EXPR EOL | END
EXPR => TERM {ADDOP TERM}* | LVAR ASSIGN EXPR
TERM => FACTOR {MULOP FACTOR}*
FACTOR => NUMBER | (EXPR)
MULOP => * | /
ADDOP => + | -
NUMBER => int | FRACTION | RVAR
FRACTION => F(FACTOR/FACTOR)
RVAR => lower case char string MUST BE IN SYMBOL TABLE
LVAR => lower case char string MUST NOT BE IN SYMBOL TABLE
*/

int depth = 0; //for debug
bool val_comp(const Calculator::symbol_t& a, const Calculator::symbol_t& b);

bool val_comp(const Calculator::symbol_t& a, const Calculator::symbol_t& b){return a.val < b.val;}

int main(void){
    std::ifstream in;
    in.open("program.txt");
    std::ofstream log;
    log.open("calculator.log");
    std::ofstream err;
    err.open("debug.log");
    Scanner scan{in};
    Calculator calc{scan};
    std::streambuf *logbuff = std::clog.rdbuf(log.rdbuf());
    std::streambuf *errbuff = std::cerr.rdbuf(err.rdbuf());
    while(calc.run(std::cout, std::clog));

    auto vars = calc.get_table();
    auto var_end = remove_if(begin(vars), end(vars), [](Calculator::symbol_t& a){return !a.writen;});
    //std::cout << vars << std::endl;

    std::cout << std::endl << "Variable Statistics: " << std::endl;

    // print the things in alphabetical order
    sort(begin(vars), var_end);
    for_each(begin(vars), var_end, [](Calculator::symbol_t& a){std::cout << a << std::endl;});

    std::cout << "Number of variable names > m: " << count_if(begin(vars), var_end, [](Calculator::symbol_t& a){return a.name > "m";}) << std::endl;
    std::cout << "Minimum element value: "     << *min_element(begin(vars), var_end, val_comp)    << std::endl;
    std::cout << "Maximum element value: "     << *max_element(begin(vars), var_end, val_comp)    << std::endl;
    std::cout << "Any of the elements have a value > 50? " <<std::boolalpha<< any_of(begin(vars), var_end, [](Calculator::symbol_t& a){return a.val > 50;})  << std::endl;
    std::cout << "Print the first variable found between i and n: " << *find_if(begin(vars), var_end, [](Calculator::symbol_t& a){return a.name > "i"&&a.name<"n";}) << std::endl;
    std::cout << "Increase every value of the table by 5: "  << std::endl;// (hint transform)
    for_each(begin(vars), var_end, [](Calculator::symbol_t& a){a.val+=5;});
    for_each(begin(vars), var_end, [](Calculator::symbol_t& a){std::cout << a << std::endl;});
    std::cout << "Sort the table entries by value (not by variable name): "  << std::endl;
    sort(begin(vars), var_end, val_comp);
    for_each(begin(vars), var_end, [](Calculator::symbol_t& a){std::cout << a << std::endl;});
    std::cout << "Show the partial sum of all values in the table: " << std::endl;
    std::vector<Calculator::symbol_t> part_sums;
    partial_sum(begin(vars), var_end, back_inserter(part_sums));
    for_each(begin(part_sums), end(part_sums), [](Calculator::symbol_t& a){std::cout << a << std::endl;});


    in.close();
    log.close();
    err.close();
    std::clog.rdbuf(logbuff);
    std::cerr.rdbuf(errbuff);
    return 0;
}
