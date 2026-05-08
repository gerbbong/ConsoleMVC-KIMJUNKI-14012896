#pragma once
#include "Order.h"
#include <vector>

class OrderRepository {
public:
    int add(Order order);
    std::vector<Order>& getAll();
    Order* findById(int orderId);
    std::vector<Order*> findByStatus(OrderStatus status);
    std::vector<Order*> findBySampleId(const std::string& sampleId);
private:
    std::vector<Order> orders_;
    int nextId_ = 1;
};
