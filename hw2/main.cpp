#include "calculator.h"
#include "scanner.h"
#include <iostream>

int main(void){
    Scanner scan{std::cin};
    Calculator calc{scan};
    std::cout<<"Welcome to the High Order Calculator (q to quit)"<<std::endl;
    while(calc.run(std::cout)){

    }
    return 0;
}
