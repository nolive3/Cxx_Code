#ifndef CALCULATOR_H
#define CALCULATOR_H


class Calculator
{
    public:
        Calculator(std::istream source = std::cin);
        ~Calculator();
        Calculator(const Calculator& other);
        Calculator& operator=(const Calculator& other);
    protected:
    private:
};

#endif // CALCULATOR_H
