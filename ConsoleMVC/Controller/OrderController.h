#pragma once
#include "../Model/OrderRepository.h"
#include "../Model/SampleRepository.h"
#include "../Model/ProductionLine.h"
#include <string>
#include <vector>

class OrderController {
public:
    OrderController(OrderRepository& orderRepo, SampleRepository& sampleRepo,
                    ProductionLine& productionLine);
    int placeOrder(const std::string& sampleId, const std::string& customerName, int qty);
    std::vector<Order*> getReservedOrders();
    bool approveOrder(int orderId);
    bool rejectOrder(int orderId);
    std::string getLastMessage() const;
private:
    OrderRepository& orderRepo_;
    SampleRepository& sampleRepo_;
    ProductionLine& productionLine_;
    std::string lastMessage_;
};
