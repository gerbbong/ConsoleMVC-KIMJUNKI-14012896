#pragma once
#include "../Controller/OrderController.h"

class OrderView {
public:
    explicit OrderView(OrderController& controller);
    void run();
private:
    void showMenu();
    void placeOrder();
    void listReservedOrders();
    void approveOrReject();
    void printOrderTable(const std::vector<Order*>& orders);
    OrderController& ctrl_;
};
