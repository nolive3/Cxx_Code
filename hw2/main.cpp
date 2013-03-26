#include "calculator.h"
#include "scanner.h"
#include <iostream>
#include <fstream>
#include <algorithm>

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
    remove_if(begin(vars), end(vars), [](Calculator::symbol_t& a){return !a.writen;});
    std::cout << vars << std::endl;

    in.close();
    log.close();
    err.close();
    std::clog.rdbuf(logbuff);
    std::cerr.rdbuf(errbuff);
    return 0;
}
