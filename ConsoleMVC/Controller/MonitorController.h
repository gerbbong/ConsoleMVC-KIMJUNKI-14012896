#pragma once
#include "../Model/OrderRepository.h"
#include "../Model/SampleRepository.h"
#include <map>
#include <vector>
#include <string>

struct StockStatus {
    std::string sampleId;
    std::string sampleName;
    int stock;
    int pendingQty;       // RESERVED + PRODUCING 주문 수량 합계
    std::string label;    // 여유 / 부족 / 고갈
};

class MonitorController {
public:
    MonitorController(OrderRepository& orderRepo, SampleRepository& sampleRepo);
    std::map<OrderStatus, int> getOrderCountByStatus();
    std::map<OrderStatus, std::vector<Order*>> getOrdersByStatus();
    std::vector<StockStatus> getStockStatusList();
private:
    OrderRepository& orderRepo_;
    SampleRepository& sampleRepo_;
};
