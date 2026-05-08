#include "MonitorController.h"

MonitorController::MonitorController(OrderRepository& orderRepo, SampleRepository& sampleRepo)
    : orderRepo_(orderRepo), sampleRepo_(sampleRepo) {}

std::map<OrderStatus, int> MonitorController::getOrderCountByStatus() {
    std::map<OrderStatus, int> counts;
    counts[OrderStatus::RESERVED]  = 0;
    counts[OrderStatus::PRODUCING] = 0;
    counts[OrderStatus::CONFIRMED] = 0;
    counts[OrderStatus::RELEASE]   = 0;

    for (const auto& o : orderRepo_.getAll()) {
        if (o.status != OrderStatus::REJECTED)
            counts[o.status]++;
    }
    return counts;
}

std::map<OrderStatus, std::vector<Order*>> MonitorController::getOrdersByStatus() {
    std::map<OrderStatus, std::vector<Order*>> result;
    for (auto& o : orderRepo_.getAll()) {
        if (o.status != OrderStatus::REJECTED)
            result[o.status].push_back(&o);
    }
    return result;
}

std::vector<StockStatus> MonitorController::getStockStatusList() {
    std::vector<StockStatus> result;
    for (auto& sample : sampleRepo_.getAll()) {
        int pendingQty = 0;
        for (auto* order : orderRepo_.findBySampleId(sample.id)) {
            if (order->status == OrderStatus::RESERVED ||
                order->status == OrderStatus::PRODUCING)
                pendingQty += order->quantity;
        }

        StockStatus ss;
        ss.sampleId   = sample.id;
        ss.sampleName = sample.name;
        ss.stock      = sample.stock;
        ss.pendingQty = pendingQty;

        if (sample.stock == 0)              ss.label = "고갈";
        else if (sample.stock <= pendingQty) ss.label = "부족";
        else                                 ss.label = "여유";

        result.push_back(ss);
    }
    return result;
}
