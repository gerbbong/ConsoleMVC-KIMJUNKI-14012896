#include "OrderRepository.h"

int OrderRepository::add(Order order) {
    order.orderId = nextId_++;
    orders_.push_back(std::move(order));
    return orders_.back().orderId;
}

std::vector<Order>& OrderRepository::getAll() {
    return orders_;
}

Order* OrderRepository::findById(int orderId) {
    for (auto& o : orders_)
        if (o.orderId == orderId) return &o;
    return nullptr;
}

std::vector<Order*> OrderRepository::findByStatus(OrderStatus status) {
    std::vector<Order*> result;
    for (auto& o : orders_)
        if (o.status == status) result.push_back(&o);
    return result;
}

std::vector<Order*> OrderRepository::findBySampleId(const std::string& sampleId) {
    std::vector<Order*> result;
    for (auto& o : orders_)
        if (o.sampleId == sampleId) result.push_back(&o);
    return result;
}
