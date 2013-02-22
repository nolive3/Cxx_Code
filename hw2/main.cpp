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
    std::ifstream file;
    file.open("program.txt");
    Scanner scan{file};
    Calculator calc{scan};
    while(calc.run(std::cout, std::clog)){

    }
    file.close();
    return 0;
}
