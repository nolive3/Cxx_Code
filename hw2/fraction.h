#ifndef FRACTION_H
#define FRACTION_H
#include <iostream>

class Fraction
{
    public:
        friend const Fraction operator+(const Fraction& lhs, const Fraction& rhs);
        friend const Fraction operator+(const Fraction& lhs, const int& rhs) {return lhs+Fraction(rhs);}
        friend const Fraction operator+(const int& lhs, const Fraction& rhs) {return Fraction(lhs)+rhs;}

        friend const Fraction operator-(const Fraction& lhs, const Fraction& rhs);
        friend const Fraction operator-(const Fraction& lhs, const int& rhs) {return lhs-Fraction(rhs);}
        friend const Fraction operator-(const int& lhs, const Fraction& rhs) {return Fraction(lhs)-rhs;}

        friend const Fraction operator*(const Fraction& lhs, const Fraction& rhs);
        friend const Fraction operator*(const Fraction& lhs, const int& rhs) {return lhs*Fraction(rhs);}
        friend const Fraction operator*(const int& lhs, const Fraction& rhs) {return Fraction(lhs)*rhs;}

        friend const Fraction operator/(const Fraction& lhs, const Fraction& rhs);
        friend const Fraction operator/(const Fraction& lhs, const int& rhs) {return lhs/Fraction(rhs);}
        friend const Fraction operator/(const int& lhs, const Fraction& rhs) {return Fraction(lhs)/rhs;}

        const Fraction& operator++();
        const Fraction& operator++(int);

        const Fraction& operator--();
        const Fraction& operator--(int);

        friend std::ostream& operator<<(std::ostream& out, const Fraction& frac);


        Fraction();
        Fraction(const int& num);
        Fraction(const int& num, const int& den);


        ~Fraction() = default;
        Fraction(const Fraction& other) = default;
        Fraction& operator=(const Fraction& other) = default;
    protected:
    private:
        int m_num;
        int m_den;
};

#endif // FRACTION_H
