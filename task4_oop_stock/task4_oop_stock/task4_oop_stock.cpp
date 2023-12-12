#pragma once
#include <iostream>
#include <vector>
#include <list>
#include <ctime>
#include <string>
#include "medicine.h"
#include "order.h"
#include "customer.h"
#include "courier.h"
#include "delivery.h"
#include <locale>
#include <SFML/Graphics.hpp>

using namespace std;


int main() {
    setlocale(LC_ALL, "rus");
    int N = 15; // дни моделирования
    int M = 5; // курьеры
    int K = 21; // различных лекарств на складе
    float retailMarkup = 0.25;
    float discountPercentage = 0.05;
    float summaryCost = 0.0;
    // Инициализация службы доставки
    DeliveryService deliveryService(retailMarkup, discountPercentage);

    // Инициализация лекарств на складе
    deliveryService.medicines.push_back(Medicine("Аспирин", 100, 500, "Таблетки", 60, 100.0, "Анальгетики"));
    deliveryService.medicines.push_back(Medicine("Ибупрофен", 50, 200, "Таблетки", 60, 150.0, "Анальгетики"));
    deliveryService.medicines.push_back(Medicine("Парацетамол", 80, 300, "Таблетки", 60, 120.0, "Анальгетики"));
    deliveryService.medicines.push_back(Medicine("Амоксициллин", 30, 500, "Капсулы", 90, 250.0, "Антибиотики"));
    deliveryService.medicines.push_back(Medicine("Левомицетин", 20, 100, "Таблетки", 75, 80.0, "Антибиотики"));
    deliveryService.medicines.push_back(Medicine("Метформин", 70, 850, "Таблетки", 120, 70.0, "Гипогликемические"));
    deliveryService.medicines.push_back(Medicine("Энап", 45, 5, "Таблетки", 2023.12, 45, "Антигипертензивные"));
    deliveryService.medicines.push_back(Medicine("Фурасемид", 30, 40, "Таблетки", 90, 40.0, "Диуретики"));
    deliveryService.medicines.push_back(Medicine("Амлодипин", 40, 10, "Таблетки", 120, 90.0, "Антигипертензивные"));
    deliveryService.medicines.push_back(Medicine("Кларитромицин", 20, 250, "Таблетки", 45, 200.0, "Антибиотики"));
    deliveryService.medicines.push_back(Medicine("Леводопа", 15, 200, "Таблетки", 60, 180.0, "Антипаркинсоники"));
    deliveryService.medicines.push_back(Medicine("Триметазидин", 25, 35, "Таблетки", 60, 120.0, "Противовоспалительные"));
    deliveryService.medicines.push_back(Medicine("Флурбипрофен", 30, 100, "Таблетки", 90, 160.0, "Антигипертензивные"));
    deliveryService.medicines.push_back(Medicine("Пиритон", 50, 15, "Таблетки", 90, 30.0, "Антигистаминики"));
    deliveryService.medicines.push_back(Medicine("Мидазолам", 10, 5, "Инъекция", 90, 50.0, "Седативные"));
    deliveryService.medicines.push_back(Medicine("Эритромицин", 40, 500, "Капсулы", 45, 180.0, "Антибиотики"));
    deliveryService.medicines.push_back(Medicine("Азитромицин", 25, 250, "Капсулы", 60, 150.0, "Антибиотики"));
    deliveryService.medicines.push_back(Medicine("Олопатадин", 15, 20, "Глазные капли", 365, 40.0, "Антигистаминики"));
    deliveryService.medicines.push_back(Medicine("Имипрамин", 20, 75, "Таблетки", 120, 80.0, "Антидепрессанты"));
    deliveryService.medicines.push_back(Medicine("Бисопролол", 30, 10, "Таблетки", 90, 60.0, "Антигипертензивные"));
    deliveryService.medicines.push_back(Medicine("Моксифлоксацин", 15, 400, "Таблетки", 180, 220.0, "Антибиотики"));

    deliveryService.generateRandomExpirationDaysForMedicines();

    // Начало моделирования
    srand(time(0));
    for (int day = 1; day <= N; ++day) {
        cout << "\n\n\n\n\n\n\n\n\n" << "День " << day << endl;
        // Генерация случайных заказов
        int numOrders = rand() % 10 + 5;
        for (int i = 0; i < numOrders; ++i) {
            Order order("987654321", "Улица Лермонтова, 5", "54321");

            int medicineIndex = rand() % K;
            int quantity = rand() % 10 + 1; // Заказываем от 1 до 10 единиц товара

            order.medicines.push_back(make_pair(deliveryService.medicines[medicineIndex], quantity));

            deliveryService.orders.push_back(order);
        }

        // Обработка заказов
        for (Order& order : deliveryService.orders) {
            float totalCost = 0.0;

            cout << "Обработка заказа для клиента с номером телефона " << order.phoneNumber << endl;

            for (auto& medicinePair : order.medicines) {
                const Medicine& orderedMedicine = medicinePair.first;
                int orderedQuantity = medicinePair.second;

                cout << "   - Лекарство: " << orderedMedicine.name << ", Количество: " << orderedQuantity << endl;

                auto it = find_if(deliveryService.medicines.begin(), deliveryService.medicines.end(),
                    [&](const Medicine& m) { return m.name == orderedMedicine.name; });

                if (it != deliveryService.medicines.end() && it->quantity >= orderedQuantity) {
                    totalCost += it->price * (1 + deliveryService.retailMarkup) * orderedQuantity;
                    it->quantity -= orderedQuantity;

                    cout << "      Изменение остатка на складе: -" << orderedQuantity << " " << it->name << endl;
                }
                else {
                    cout << "      Недостаточно товара " << orderedMedicine.name << " на складе." << endl;
                }
            }

            if (!order.discountCardNumber.empty()) {
                totalCost *= (1 - deliveryService.discountPercentage);
            }
            else if (totalCost > 1000) {
                totalCost *= 0.97;
            }

            // Вывод суммы заказа
            cout << "   Общая стоимость заказа: " << totalCost << " рублей." << endl;
            summaryCost += totalCost;
        }

        // Очистка списка заказов
        deliveryService.orders.clear();

        // Обработка заявок
        auto it = deliveryService.deliveries.begin();
        while (it != deliveryService.deliveries.end()) {
            auto& delivery = *it;
            if (delivery.quantity > 0 && delivery.daysToDelivery > 0) {
                --delivery.daysToDelivery;
            }
            else {
                // Удаляем завершенную или неполностью обработанную заявку
                auto medicineIt = find_if(deliveryService.medicines.begin(), deliveryService.medicines.end(),
                    [&](const Medicine& m) { return m.name == delivery.medicine.name; });

                if (medicineIt != deliveryService.medicines.end()) {
                    medicineIt->quantity += delivery.quantity;
                    cout << "Поставка завершена. Поставлено " << delivery.quantity << " " << medicineIt->name << " на склад." << endl;
                }

                it = deliveryService.deliveries.erase(it);
                continue;
            }

            ++it;
        }

        deliveryService.checkAndDiscountExpiringMedicines();//проверка на срок годности
        // Заказ лекарств у фармацевтической фирмы
        deliveryService.checkAndOrderMedicines();
        deliveryService.OneDayLeft();
        //deliveryService.ucenka();

        
    }

    // Вывод остатка лекарств на складе
    cout << "Остаток лекарств на складе:" << endl;
    for (const Medicine& medicine : deliveryService.medicines) {
        cout << medicine.name << ": " << medicine.quantity << " штук" << endl;
    }
    cout << "Общая выручка составила: " << summaryCost << endl;
    return 0;
}