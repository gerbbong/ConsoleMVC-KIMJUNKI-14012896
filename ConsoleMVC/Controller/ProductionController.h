#pragma once
#include "../Model/ProductionLine.h"
#include "../Model/OrderRepository.h"
#include "../Model/SampleRepository.h"
#include <string>
#include <deque>

class ProductionController {
public:
    ProductionController(ProductionLine& line, OrderRepository& orderRepo,
                         SampleRepository& sampleRepo);

    // 경과 시간을 확인해 완료된 작업을 자동 처리
    void update();

    bool hasCurrentJob() const;
    const ProductionJob* getCurrentJob() const;
    const std::deque<ProductionJob>& getQueue() const;
    int getQueueSize() const;

private:
    void finishJob(ProductionJob& job);

    ProductionLine& line_;
    OrderRepository& orderRepo_;
    SampleRepository& sampleRepo_;
};
