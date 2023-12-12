#pragma once
#include <iostream>
using namespace std;

class Medicine {
public:
    string name;//��������
    int quantity;//���-��
    float dosage;//���������
    string type;//���
    int expiryDate;//���� ��������
    float price;// ����
    string group;//������
    int initialQuantity = quantity;
    bool inDelivery;
    bool isCutPrice = 0;
    Medicine(string n, int q, float d, string t, int e, float wp, string g)
        : name(n), quantity(q), dosage(d), type(t), expiryDate(e), price(wp), group(g) {}

    void generateRandomExpirationDays();
};

void Medicine::generateRandomExpirationDays() {
    expiryDate = rand() % (5-1+1) + 1;  // ���������� ��������� ����� �� 40 �� 50 ����
}