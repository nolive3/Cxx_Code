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
    cout<<"Fraction Test"<<endl;
    Fraction f1(2,3); //regular
    Fraction f2(4,8); //check reduce by gcd
    cout<<"f1 = ( F(2/3) ) : "<<f1<<endl;
    cout<<"f2 = ( F(1/2) ) : "<<f2<<endl;
    cout<<"f1 + f2 = ( F(7/6) ) : "<<f1+f2<<endl;
    cout<<"f1 - f2 = ( F(1/6) ) : "<<f1-f2<<endl;
    cout<<"f1 * f2 = ( F(1/3) ) : "<<f1*f2<<endl;
    cout<<"f1 / f2 = ( F(4/3) ) : "<<f1/f2<<endl;
    cout<<boolalpha<<"f1 == f2 (false) : "<<(f1==f2)<<endl;
    cout<<"f1 != f2 (true) : "<<(f1 != f2) << endl;
    Fraction f3(16, 32);
    cout<<"f2 == f3 (true) : "<<(f2 == f3) << endl;
    cout<<"f1 < f2 (false) : "<<(f1<f2) <<endl;
    cout<<"f2 < f3 (false) : "<<(f2<f3)<<endl;
    cout<<"f2 < f1 (true)  : "<<(f2<f1)<<endl;

    cout<<"++f1 ( F(5/3) ) : " << ++f1 << endl;
    cout<<"f1++ ( F(5/3) ) : " << f1++ << endl;
    cout<<"After incr ( F(8/3) ) : " <<f1 <<endl;

    cout<<"--f2 ( F(-1/2) ) : " << --f2 << endl;
    cout<<"f2-- ( F(-1/2) ) : " << f2-- << endl;
    cout<<"After decr ( F(-3/2) ) : " << f2 << endl;


    //definately missing junit about now
    Fraction f4(5,7);
    cout<<"f4 + 6 = ( F(47/7) ) : "<< f4+6 <<endl;
    Fraction f5(8, 19);
    cout<<"f5 * 8 = ( F(64/19) ) : "<< f5*8 <<endl;
    Fraction f6(18, 44);
    cout<<"5 - f6 =  ( F(101/22) ) : "<<5 - f6<<endl;
    cout<<"f6 / 18 = ( F ( 1 / 44) ) : "<<f6 / 18 <<endl;
    cout<<"double(f6) = (.40909) : " <<double(f6)<<endl;
    Fraction f7(99, 33);
    cout<<"int(f7) = (3) : " <<int(f7)<<endl;
    Scanner scan{std::cin};
    Calculator calc{scan};
    std::cout<<"Welcome to the High Order Calculator (q to quit)"<<std::endl;
    while(calc.run(std::cout)){

    }
    return 0;
}
