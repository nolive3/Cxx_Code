#include "employee.h"
#include <iostream>

Employee::Employee(std::string newname, int newid):
    myname(newname), myid(newid)
{
    std::cout<<"Calling base contructor "<<this->myname<<std::endl;
}

Employee::~Employee()
{
    std::cout<<"Calling destructor "<<this->myname<<std::endl;
}

Employee::Employee(const Employee& other):
    myname(other.myname), myid(other.myid)
{
    std::cout<<"Calling copy contructor "<<this->myname<<std::endl;
}

Employee& Employee::operator=(const Employee& rhs)
{
    if (this == &rhs) return *this; // handle self assignment
    //assignment operator
    Employee tmp(rhs);
    swap(*this, tmp);
    std::cout<<"Calling assignment operator "<<this->myname<<std::endl;
    return *this;
}

void Employee::swap(Employee& a, Employee& b){
    std::swap(a.myname, b.myname);
    std::swap(a.myid, b.myid);
}
