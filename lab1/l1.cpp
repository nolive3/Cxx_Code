#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Person {
   public:
       Person() : myname(std::string("none")) { }
       Person(std::string n) : myname(n) {cout<<"Making a new Person named: " << myname << endl;}
       Person(const Person& p) : myname(p.myname) {cout<<"Copying a new Person named: " << myname << endl;}
       Person& operator=(const Person& p) { myname = p.myname; cout<<"Assigning a new person named: " << myname <<endl; return *this;}

       std::string name() const { return myname;}
       void name(std::string n) { myname = n; }
   private:
       std::string myname;
};

int main()
{
    cout << "Recitation 1" << endl;
    vector<Person> people{4};
    cout<<"Making some people"<<endl;
    Person p1{"bob"};
    Person p2{"sally"};
    Person p3("Edna");
    Person p4("George");

    cout<<endl<<"Putting them into the vector"<<endl;
    people.push_back(p1);
    people.push_back(p2);
    people.push_back(p3);
    people.push_back(p4);

    //Question 1:  Look at output, why are these objects getting created/copied do you think?

    //Try number 1 to set all the names to burdell
    cout<<"Looping to set all names to burdell, try 1"<<endl;
    for (Person p : people) {
       p.name("Burdell");
    }

    //Question 2 : What is up with all these copies this time?
    cout<<endl<<"dumping the people vector -- try 1:"<<endl;
    for (Person p : people) {
       cout<<p.name()<<", ";
    }
    //Question 3 : Whoa, why aren't any names changed?

    //Try 2 to set all the names to burdell
    cout<<endl<<"Looping to set all names to burdell try 2"<<endl;
    for (Person& p : people) {
       p.name("Burdell");
    }

    //Question 4 : Why no copies this time.  Its an almost identical loop to try 1?

    cout<<endl<<"dumping the people vector -- try 2: "<<endl;
    for (Person& p : people) {
       cout<<p.name()<<", ";
    }

    //Question 5 : Success, why were the names changed in the vector this time?

    //Last thing to check, let's look at original items that we put into the vector.
    cout<<endl<<endl<<"Print some original data"<<endl;
    cout<<"Person p1 = " << p1.name()<<endl;
    cout<<"Person p2 = " << p2.name()<<endl;

    //Question 6: Why weren't the original names changed if they are changed in the vector?

    //Now we are going to do something bad!!!
    //Question 7: The system fails.  Why does this happen?
    Person p5{"Dilbert"};
   // people[10] = p5;
    return 0;
}
