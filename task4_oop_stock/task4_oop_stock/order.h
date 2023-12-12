#pragma once
#include <iostream>
#include "medicine.h"
using namespace std;
class Order {
public:
    string phoneNumber;
    string address;
    string discountCardNumber;
    vector<pair<Medicine, int>> medicines; // Перечень заказываемых лекарств и их количества
    void generateRandomOrder(vector<Medicine>& medicines);
    Order(string phone, string addr, string cardNumber)
        : phoneNumber(phone), address(addr), discountCardNumber(cardNumber) {}

private:
    vector<pair<Medicine, int>> medicinesOrdered;
    float probabilityOfDiscountedMedicine = 0.6;
};

void Order::generateRandomOrder(vector<Medicine>& medicines) {
    // Генерация случайного количества заказанных товаров
    int numMedicines = rand() % 10 + 1;  // От 1 до 10 единиц товара

    for (int i = 0; i < numMedicines; ++i) {
        int medicineIndex = rand() % medicines.size();
        int quantity = rand() % 10 + 1;  // От 1 до 10 единиц товара

        // Проверка повышенной вероятности заказа уцененных товаров
        float probability = static_cast<float>(rand()) / RAND_MAX;  // Случайное число от 0 до 1
        if (probability < probabilityOfDiscountedMedicine) {
            // Если случайное число меньше вероятности, то заказываем уцененный товар
            // Добавление случайно выбранного товара в заказ
            medicinesOrdered.push_back(make_pair(medicines[medicineIndex], quantity));
        }
        else {
            // Иначе заказываем обычный товар
            // Добавление случайно выбранного товара в заказ
            medicinesOrdered.push_back(make_pair(medicines[medicineIndex], quantity));
        }
    }
}