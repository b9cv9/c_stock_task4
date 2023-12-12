#pragma once
#include <iostream>
#include "medicine.h"
using namespace std;
class Order {
public:
    string phoneNumber;
    string address;
    string discountCardNumber;
    vector<pair<Medicine, int>> medicines; // �������� ������������ �������� � �� ����������
    void generateRandomOrder(vector<Medicine>& medicines);
    Order(string phone, string addr, string cardNumber)
        : phoneNumber(phone), address(addr), discountCardNumber(cardNumber) {}

private:
    vector<pair<Medicine, int>> medicinesOrdered;
    float probabilityOfDiscountedMedicine = 0.6;
};

void Order::generateRandomOrder(vector<Medicine>& medicines) {
    // ��������� ���������� ���������� ���������� �������
    int numMedicines = rand() % 10 + 1;  // �� 1 �� 10 ������ ������

    for (int i = 0; i < numMedicines; ++i) {
        int medicineIndex = rand() % medicines.size();
        int quantity = rand() % 10 + 1;  // �� 1 �� 10 ������ ������

        // �������� ���������� ����������� ������ ��������� �������
        float probability = static_cast<float>(rand()) / RAND_MAX;  // ��������� ����� �� 0 �� 1
        if (probability < probabilityOfDiscountedMedicine) {
            // ���� ��������� ����� ������ �����������, �� ���������� ��������� �����
            // ���������� �������� ���������� ������ � �����
            medicinesOrdered.push_back(make_pair(medicines[medicineIndex], quantity));
        }
        else {
            // ����� ���������� ������� �����
            // ���������� �������� ���������� ������ � �����
            medicinesOrdered.push_back(make_pair(medicines[medicineIndex], quantity));
        }
    }
}