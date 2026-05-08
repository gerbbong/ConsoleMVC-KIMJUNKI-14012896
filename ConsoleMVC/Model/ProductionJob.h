#pragma once
#include <string>

struct ProductionJob {
    int orderId;
    std::string sampleId;
    int shortage;        // 부족분 (주문수량 - 재고)
    int actualQuantity;  // 실생산량 = ceil(shortage / (yield * 0.9))
    double totalTime;    // 총생산시간 = avgTime * actualQuantity

    ProductionJob() : orderId(0), shortage(0), actualQuantity(0), totalTime(0.0) {}
    ProductionJob(int orderId, std::string sampleId, int shortage, int actual, double time)
        : orderId(orderId), sampleId(std::move(sampleId)),
          shortage(shortage), actualQuantity(actual), totalTime(time) {}
};
