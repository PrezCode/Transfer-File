//ENGR200 Week 6, Program 3 Assignment, Question 3.13 by Alex Gonzalez
#include <iostream>
#include <cmath>
#include <math.h>
#include <string>
using namespace std;

class Invoice{
    public:
    void setPartNumber(string number){
        partNumber = number;
    }
    void setPartDescription(string description){
        partDescription = description;
    }
    void setItemQuantity(int quantity){
        itemQuantity = quantity;
    }
    void setItemPrice(int price){
        itemPrice = price;
    }
    void setTotalAmount(int amount){
        totalAmount = amount;
    }
    string getPartNumber() const {
        return partNumber;
    }
    string getPartDescription() const {
        return partDescription;
    }
    int getItemQuantity() const {
        return itemQuantity;
    }
    int getItemPrice () const {
        return itemPrice;
    }
    int getInvoiceAmount() const {
        return totalAmount;
    }
    private:
    string partNumber, partDescription;
    int itemQuantity, itemPrice, totalAmount;
};

int main(){
    string number, description;
    int quantity, price, total;
    Invoice newInvoice;

    cout << "Invoice Creator\n";
    cout << "Please Enter a part number: ";
    cin >> number;
    newInvoice.setPartNumber(number);

    cout << "Part description: ";
    getline(cin, description);
    newInvoice.setPartDescription(description);

    cout << "Part Quantity: ";
    cin >> quantity;
    newInvoice.setItemQuantity(quantity);

    cout << "Part Price: ";
    cin >> price;
    newInvoice.setItemPrice(price);
    cout << endl;

    total = quantity*price;
    newInvoice.setTotalAmount(total);

    cout << "Invoice for Part#" << newInvoice.getPartNumber() << endl;
    cout << "[" << newInvoice.getPartDescription() << "]\n";
    cout << "Total Items: " << newInvoice.getItemQuantity() << endl;
    cout << "Individual Price: $" << newInvoice.getItemPrice() << endl;
    cout << "Total Charge: $" << newInvoice.getInvoiceAmount() << endl;  

    return 0;
}