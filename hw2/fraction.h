#ifndef FRACTION_H
#define FRACTION_H
#include <iostream>

class Fraction
{
    public:
        friend const Fraction operator+(const Fraction& lhs, const Fraction& rhs);
        friend const Fraction operator+(const Fraction& lhs, const int& rhs) {return lhs+Fraction(rhs);}
        friend const Fraction operator+(const int& lhs, const Fraction& rhs) {return Fraction(lhs)+rhs;}

        friend const Fraction& operator+=(Fraction& lhs, const Fraction& rhs);
        friend const Fraction& operator+=(Fraction& lhs, const int& rhs) {return lhs+=Fraction(rhs);}

        const Fraction operator-() const;

        friend const Fraction operator-(const Fraction& lhs, const Fraction& rhs) {return lhs+(-rhs);}
        friend const Fraction operator-(const Fraction& lhs, const int& rhs) {return lhs-Fraction(rhs);}
        friend const Fraction operator-(const int& lhs, const Fraction& rhs) {return Fraction(lhs)-rhs;}

        friend const Fraction operator*(const Fraction& lhs, const Fraction& rhs);
        friend const Fraction operator*(const Fraction& lhs, const int& rhs) {return lhs*Fraction(rhs);}
        friend const Fraction operator*(const int& lhs, const Fraction& rhs) {return Fraction(lhs)*rhs;}

        friend const Fraction operator/(const Fraction& lhs, const Fraction& rhs);
        friend const Fraction operator/(const Fraction& lhs, const int& rhs) {return lhs/Fraction(rhs);}
        friend const Fraction operator/(const int& lhs, const Fraction& rhs) {return Fraction(lhs)/rhs;}

        const Fraction& operator++();
        const Fraction operator++(int);

        const Fraction& operator--();
        const Fraction operator--(int);

        friend std::ostream& operator<<(std::ostream& out, const Fraction& frac);

        friend bool operator==(const Fraction& lhs, const Fraction& rhs);
        friend bool operator==(const int& lhs, const Fraction& rhs) {return Fraction(lhs)==rhs;}
        friend bool operator==(const Fraction& lhs, const int& rhs) {return lhs==Fraction(rhs);}

        friend bool operator!=(const Fraction& lhs, const Fraction& rhs) {return !(lhs==rhs);}
        friend bool operator!=(const int& lhs, const Fraction& rhs) {return Fraction(lhs)!=rhs;}
        friend bool operator!=(const Fraction& lhs, const int& rhs) {return lhs!=Fraction(rhs);}

        friend bool operator<(const Fraction& lhs, const Fraction& rhs);
        friend bool operator<(const int& lhs, const Fraction& rhs) {return Fraction(lhs)<rhs;}
        friend bool operator<(const Fraction& lhs, const int& rhs) {return lhs<Fraction(rhs);}

        operator double() const {return (double)m_num/(double)m_den;}

        operator int() const {return m_num/m_den;}

        bool is_integer() const {return m_den==1;}


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
