////ENGR200 Week 6, Program 3 Assignment, Question 3.14 by Alex Gonzalez
#include <iostream>
#include <string>
using namespace std;

class Employee{
    public:
    Employee(string name1, string name2, int pay):  //constructs an employee object with required variables
        firstName(name1), lastName(name2), monthSalary(pay){
            if(monthSalary < 0){    //forces a negative salary value to equal 0
                monthSalary = 0;
            }
            yearlySalary = monthSalary*12;  //generate the yearly salary amount given the monthly salary input
            raise = yearlySalary*1.10;      //generate the yearly salary with a 10% raise
        }
    void setFirstName(string name){
        firstName = name;
    }
    void setLastName(string name){
        lastName = name;
    }
    void setMonthlySalary(int pay){
        monthSalary = pay;
    }
    string getFirstName() const {
        return firstName;
    }
    string getLastName() const {
        return lastName;
    }
    int getYearlySalary() const {
        return yearlySalary;
    }
    int getRaise() const {
        return raise;
    }
    private:
    string firstName, lastName;
    int monthSalary, yearlySalary, raise;
};

int main(){
    string fName, lName, count;
    int salary;
    cout << "Please enter employee 1's information" << endl;
    cout << "First Name: "; cin >> fName;
    cout << "Last Name: "; cin >> lName;
    cout << "Current Monthly Salary: "; cin >> salary;        
    Employee employee1(fName, lName, salary);   //create first employee object with user input
    cout << endl;
    cout << "Please enter employee 2's information" << endl;
    cout << "First Name: "; cin >> fName;
    cout << "Last Name: "; cin >> lName;
    cout << "Current Monthly Salary: "; cin >> salary;        
    Employee employee2(fName, lName, salary);   //create second employee object with user input
    cout << endl;
    //print out all the information with necessary calculations
    cout << "Employees on file: " << endl;
    cout << "Employee: " << employee1.getFirstName() << " " << employee1.getLastName() << endl;
    cout << "Yearly Salary: " << employee1.getYearlySalary() << endl;
    cout << "Salary with 10% raise: " << employee1.getRaise() << endl;
    cout << endl;
    cout << "Employee: " << employee2.getFirstName() << " " << employee2.getLastName() << endl;
    cout << "Yearly Salary: " << employee2.getYearlySalary() << endl;
    cout << "Salary with 10% raise: " << employee2.getRaise() << endl;
    cout << endl;
    system("PAUSE");
    return 0;
}