#include "fraction.h"
long gcd(long x, long y);

long gcd(long x, long y){
    if(y==0) return x;
    return gcd(y, x%y);
}

const Fraction operator+(const Fraction& lhs, const Fraction& rhs){
    Fraction res(lhs);
    res+=rhs;
    return res;
}

/*
    a/b + c/d =
    (ad+cb)/bd
*/
const Fraction& operator+=(Fraction& lhs, const Fraction& rhs){
    long num = lhs.m_den*rhs.m_num+lhs.m_num*rhs.m_den;
    long den = lhs.m_den*rhs.m_den;
    long div = gcd(num,den);
    lhs.m_num = num/div;
    lhs.m_den = den/div;
    return lhs;
}
const Fraction operator*(const Fraction& lhs, const Fraction& rhs){
    return Fraction(lhs.m_num*rhs.m_num, lhs.m_den*rhs.m_den);
}
const Fraction operator/(const Fraction& lhs, const Fraction& rhs){
    return Fraction(lhs.m_num*rhs.m_den, lhs.m_den*rhs.m_num);
}
const Fraction& Fraction::operator++(){
    m_num+=m_den;
    return *this;
}
const Fraction Fraction::operator++(int){
    Fraction res(*this);
    ++*this;
    return res;
}
const Fraction& Fraction::operator--(){
    m_num-=m_den;
    return *this;
}
const Fraction Fraction::operator--(int){
    Fraction res(*this);
    --*this;
    return res;
}
const Fraction Fraction::operator-() const{
    return Fraction(-m_num, m_den);
}
std::ostream& operator<<(std::ostream& out, const Fraction& frac){
    out<<"F("<<frac.m_num<<"/"<<frac.m_den<<")";
    return out;
}
bool operator==(const Fraction& lhs, const Fraction& rhs){
    return lhs.m_den==rhs.m_den&&lhs.m_num==lhs.m_num;
}

/*
WLOG assume the denominators are positive

 ln/ld < rn/rd
 ln*rd < rn*ld
*/
bool operator<(const Fraction& lhs, const Fraction& rhs){
    int ln = lhs.m_num, ld = lhs.m_den;
    int rn = rhs.m_num, rd = rhs.m_den;
    if(ld<0){
        ln=-ln;
        ld=-ld;
    }
    if(rd<0){
        rn=-rn;
        rd=-rd;
    }
    long l = ln*rd;
    long r = rn*ld;
    return l<r;
}
Fraction::Fraction() : Fraction(1){}
Fraction::Fraction(const int& num) : Fraction(num, 1) {}
Fraction::Fraction(const int& num, const int& den) : m_num(num), m_den(den) {
    int div = gcd(m_num, m_den);
    m_num/=div;
    m_den/=div;
}
