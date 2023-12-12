#pragma once
#include <iostream>
using namespace std;
class Customer {
public:
    string lastName;
    string phoneNumber;
    string address;
    string discountCardNumber;
    vector<string> regularMedicines; // –егул€рно закупаемые лекарства
    int purchaseFrequency; // ѕериодичность закупки в дн€х

    Customer(string last, string phone, string addr, string cardNumber, vector<string> medicines, int frequency)
        : lastName(last), phoneNumber(phone), address(addr), discountCardNumber(cardNumber),
        regularMedicines(medicines), purchaseFrequency(frequency) {}
};