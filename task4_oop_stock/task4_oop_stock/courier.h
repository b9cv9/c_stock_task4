#pragma once
class Courier {
public:
	int id;
	int deliveredOrders; //  оличество доставленных заказов за день

	Courier(int i) : id(i), deliveredOrders(0) {}
};