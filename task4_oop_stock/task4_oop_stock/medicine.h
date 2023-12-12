#pragma once
#include <iostream>
using namespace std;

class Medicine {
public:
    string name;//название
    int quantity;//кол-во
    float dosage;//дозировка
    string type;//тип
    int expiryDate;//срок годности
    float price;// цена
    string group;//группа
    int initialQuantity = quantity;
    bool inDelivery;
    bool isCutPrice = 0;
    Medicine(string n, int q, float d, string t, int e, float wp, string g)
        : name(n), quantity(q), dosage(d), type(t), expiryDate(e), price(wp), group(g) {}

    void generateRandomExpirationDays();
};

void Medicine::generateRandomExpirationDays() {
    expiryDate = rand() % (5-1+1) + 1;  // Генерируем случайное число от 40 до 50 дней
}