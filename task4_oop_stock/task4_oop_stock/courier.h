#pragma once
class Courier {
public:
	int id;
	int deliveredOrders; // ���������� ������������ ������� �� ����

	Courier(int i) : id(i), deliveredOrders(0) {}
};