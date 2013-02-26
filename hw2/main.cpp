#include "calculator.h"
#include "scanner.h"
#include <iostream>
#include <fstream>

/*My grammar for this iteration
LINE => EXP EOL | END
EXPR => TERM {ADDOP TERM}*
TERM => FACTOR {MULOP FACTOR}*
FACTOR => NUMBER | (EXPR)
MULOP => * | /
ADDOP => + | -
NUMBER => int | FRACTION
FRACTION => F(FACTOR/FACTOR)
*/

int main(void){
    std::ifstream in;
    in.open("program.txt");
    std::ofstream err;
    err.open("calculator.log");
    Scanner scan{in};
    Calculator calc{scan};
    std::streambuf *logbuff = std::clog.rdbuf(err.rdbuf());
    while(calc.run(std::cout, std::clog)){

    }
    in.close();
    err.close();
    std::clog.rdbuf(logbuff);
    return 0;
}
