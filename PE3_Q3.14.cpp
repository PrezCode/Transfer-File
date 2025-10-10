////ENGR200 Week 6, Program 3 Assignment, Question 3.14 by Alex Gonzalez
#include <iostream>
#include <string>
using namespace std;

class Employee{
    public:
    Employee(string name1, string name2, int pay):
        firstName(name1), lastName(name2), monthSalary(pay){
            if(monthSalary < 0){
                monthSalary = 0;
            }
            yearlySalary = monthSalary*12;
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
        return monthSalary;
    }
    private:
    string firstName, lastName;
    int monthSalary, yearlySalary;
};

int main(){
    string fName, lName, count;
    int salary, num;

    cout << "Enter number of employee files to create: "; cin >> num;
    cout << endl;
    for(int i = 0; i < num; ++i){
        count = i;
        cout << "Please enter employee " << i+1 << "'s information" << endl;
        cout << "First Name: "; cin >> fName;
        cout << "Last Name: "; cin >> lName;
        cout << "Current Monthly Salary: "; cin >> salary;        
        Employee count(fName, lName, salary);
    }
    cout << endl;
    cout << "Employees on file: " << endl;
    for(int i = 0; i < num; ++i){
    count = i;
    cout << "Employee: " << count.getFirstName() << " " << count.getLastName() << endl;
    cout << "Monthly Salary: " << count.getYearlySalary() << endl;
    cout << endl;
    }
    return 0;
}