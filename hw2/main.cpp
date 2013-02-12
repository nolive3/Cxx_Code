#include "calculator.h"
#include "scanner.h"
#include <iostream>

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
    Scanner scan{std::cin};
    Calculator calc{scan};
    std::cout<<"Welcome to the High Order Calculator (q to quit)"<<std::endl;
    while(calc.run(std::cout)){

    }
    return 0;
}
