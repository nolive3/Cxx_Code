
#include <iostream>
#include "employee.h"

using std::cout;
using std::endl;

void printEmployee1 (Employee emp) {
   cout<<"Employee1: "<<emp.name()<<" number: "<<emp.id()<<endl;
}

void printEmployee2 (Employee& emp) {
   cout<<"Employee2: "<<emp.name()<<" number: "<<emp.id()<<endl;
}

int main()
{
    cout << "Spring 2013 Recitation 2" << endl;
    cout<<"***Making 3 employees****"<<endl;
    Employee e1("Bob", 123);
    Employee e2("Sally", 456);
    Employee e3("Chris", 678);
    cout<<"***Done making 3 employees***"<<endl;

    cout<<endl<<"***Printing an employee with printEmployee1"<<endl;
    printEmployee1(e1);
    cout<<endl<<"***Printing an employee with printEmployee2"<<endl;
    printEmployee2(e2);

    cout<<endl<<"***Doing an assignment***"<<endl;
    e1 = e3;
    cout<<"***Done with assignment"<<endl;

    cout<<endl<<"***Last line before return***"<<endl;
    return 0;
}
