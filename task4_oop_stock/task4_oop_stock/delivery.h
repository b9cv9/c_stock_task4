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
	vector<Medicine> medicines; // Лекарства на складе
	vector<Order> orders; // Заказы
	vector<Customer> customers; // Постоянные покупатели
	vector<Courier> couriers; // Курьеры

    vector<DeliveryInfo> deliveries;

	float retailMarkup; // Розничная наценка
	float discountPercentage; // Процент скидки по дисконтной карте

	DeliveryService(float markup, float discount)
		: retailMarkup(markup), discountPercentage(discount) {}

	void checkAndOrderMedicines(); // Декларация метода
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
            // Заказываем новое количество лекарства у фармацевтической фирмы
            int daysToDelivery = rand() % 3 + 1; // Просто для примера, можно адаптировать по вашему
            cout << "Создана заявка на лекарство " << medicine.name << ". Ожидаем поставку в течение " << daysToDelivery << " дней." << endl;
            isMedicineInDelivery = 1;
            medicine.expiryDate = 90;
            // Добавляем информацию о поставке в вектор
            deliveries.push_back({ medicine, medicine.initialQuantity - medicine.quantity, daysToDelivery });

            // Здесь можно добавить логику для создания и отслеживания заказов у фармацевтической фирмы
            // Например, можно создать новый класс для отслеживания заказов или использовать встроенные структуры данных
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
        // Заявка на это лекарство уже существует и не завершена, обновим ее
        it->quantity += quantity;
    }
    else {
        // Создаем новую заявку
        deliveries.push_back({ medicine, quantity, daysToDelivery });
    }
}

void DeliveryService::checkAndDiscountExpiringMedicines() {
    for (auto& medicine : medicines) {
        if (medicine.expiryDate <= 30 && medicine.expiryDate > 0 && medicine.isCutPrice != 1) {
            cout << "Лекарство " << medicine.name << " имеет срок годности менее месяца. Уценка в 2 раза." << endl;
            medicine.price *= 0.5;  // Уценка в два раза
            medicine.isCutPrice = 1;
        }
        else if (medicine.expiryDate <= 0) {
            cout << "Лекарство " << medicine.name << " с истекшим сроком годности. Списание." << endl;
            medicine.isCutPrice = 0;
            medicine.quantity = 0;  // Списание лекарства
        }
        //cout << "Срок годности лекарства " << medicine.name  << "    " << medicine.expiryDate << endl;
    }
}

void DeliveryService::generateRandomExpirationDaysForMedicines() {
    srand(time(0)); // Инициализируем генератор случайных чисел

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
