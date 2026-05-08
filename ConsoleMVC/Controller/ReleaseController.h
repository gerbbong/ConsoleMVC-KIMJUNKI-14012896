#pragma once
#include "../Model/OrderRepository.h"
#include "../Model/SampleRepository.h"
#include <string>
#include <vector>

class ReleaseController {
public:
    ReleaseController(OrderRepository& orderRepo, SampleRepository& sampleRepo);
    std::vector<Order*> getConfirmedOrders();
    bool release(int orderId);
    std::string getLastMessage() const;
private:
    OrderRepository& orderRepo_;
    SampleRepository& sampleRepo_;
    std::string lastMessage_;
};
