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
    string partNumber;
    string partDescription;
    int itemQuantity;
    int itemPrice;
    int totalAmount;
};

int main(){
    string number;
    string description;
    int quantity;
    int price;
    int total;
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