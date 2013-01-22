#ifndef EMPLOYEE_H
#define EMPLOYEE_H
#include <string>

class Employee
{
    public:
        Employee(std::string, int);
        ~Employee();
        Employee(const Employee& other);
        Employee& operator=(const Employee& other);
        void swap(Employee&, Employee&);
        std::string name() { return myname; }
        int id() { return myid; }
    protected:
    private:
        std::string myname;
        int myid;
};

#endif // EMPLOYEE_H
