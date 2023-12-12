#pragma once
#include "medicine.h"
#include "order.h"
#include "customer.h"
#include "courier.h"

struct DeliveryInfo {
    Medicine medicine;
    int quantity;
    int daysToDelivery;
};

class DeliveryService {
public:
	vector<Medicine> medicines; // ��������� �� ������
	vector<Order> orders; // ������
	vector<Customer> customers; // ���������� ����������
	vector<Courier> couriers; // �������

    vector<DeliveryInfo> deliveries;

	float retailMarkup; // ��������� �������
	float discountPercentage; // ������� ������ �� ���������� �����

	DeliveryService(float markup, float discount)
		: retailMarkup(markup), discountPercentage(discount) {}

	void checkAndOrderMedicines(); // ���������� ������
    void addDelivery(Medicine& medicine, int quantity, int daysToDelivery);
    void checkAndDiscountExpiringMedicines();
    void generateRandomExpirationDaysForMedicines();
    void ucenka();
    void OneDayLeft();


private:
    bool isUcenka;
    bool isMedicineInDelivery;
};

void DeliveryService::checkAndOrderMedicines() {
    for (Medicine& medicine : medicines) {
        if (medicine.quantity < 0.2 * medicine.initialQuantity && isMedicineInDelivery != 1) {
            // ���������� ����� ���������� ��������� � ���������������� �����
            int daysToDelivery = rand() % 3 + 1; // ������ ��� �������, ����� ������������ �� ������
            cout << "������� ������ �� ��������� " << medicine.name << ". ������� �������� � ������� " << daysToDelivery << " ����." << endl;
            isMedicineInDelivery = 1;
            medicine.expiryDate = 90;
            // ��������� ���������� � �������� � ������
            deliveries.push_back({ medicine, medicine.initialQuantity - medicine.quantity, daysToDelivery });

            // ����� ����� �������� ������ ��� �������� � ������������ ������� � ���������������� �����
            // ��������, ����� ������� ����� ����� ��� ������������ ������� ��� ������������ ���������� ��������� ������
        }
        else {
            isMedicineInDelivery = 0;
        }
    }
}

void DeliveryService::addDelivery(Medicine& medicine, int quantity, int daysToDelivery) {
    auto it = find_if(deliveries.begin(), deliveries.end(),
        [&](const DeliveryInfo& d) { return d.medicine.name == medicine.name && d.daysToDelivery > 0; });

    if (it != deliveries.end()) {
        // ������ �� ��� ��������� ��� ���������� � �� ���������, ������� ��
        it->quantity += quantity;
    }
    else {
        // ������� ����� ������
        deliveries.push_back({ medicine, quantity, daysToDelivery });
    }
}

void DeliveryService::checkAndDiscountExpiringMedicines() {
    for (auto& medicine : medicines) {
        if (medicine.expiryDate <= 30 && medicine.expiryDate > 0 && medicine.isCutPrice != 1) {
            cout << "��������� " << medicine.name << " ����� ���� �������� ����� ������. ������ � 2 ����." << endl;
            medicine.price *= 0.5;  // ������ � ��� ����
            medicine.isCutPrice = 1;
        }
        else if (medicine.expiryDate <= 0) {
            cout << "��������� " << medicine.name << " � �������� ������ ��������. ��������." << endl;
            medicine.isCutPrice = 0;
            medicine.quantity = 0;  // �������� ���������
        }
        //cout << "���� �������� ��������� " << medicine.name  << "    " << medicine.expiryDate << endl;
    }
}

void DeliveryService::generateRandomExpirationDaysForMedicines() {
    srand(time(0)); // �������������� ��������� ��������� �����

    for (auto& medicine : medicines) {
        medicine.generateRandomExpirationDays();
    }
}

//void DeliveryService::ucenka() {
//    for (auto& medicine : medicines) {
//        if (medicine.expiryDate <= 30 and isUcenka != 1) {
//            medicine.price /= 2;
//            isUcenka = 1;
//        }
//    }
//}


void DeliveryService::OneDayLeft() {
    for (auto& medicine : medicines) {
        medicine.expiryDate -= 1;
    }
}
