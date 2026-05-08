#pragma once
#include <string>
#include "OrderStatus.h"

struct Order {
    int orderId;
    std::string sampleId;
    std::string customerName;
    int quantity;
    OrderStatus status;

    Order() : orderId(0), quantity(0), status(OrderStatus::RESERVED) {}
    Order(int id, std::string sampleId, std::string customerName, int qty)
        : orderId(id), sampleId(std::move(sampleId)),
          customerName(std::move(customerName)),
          quantity(qty), status(OrderStatus::RESERVED) {}
};
