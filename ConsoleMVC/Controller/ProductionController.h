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
    bool hasCurrentJob() const;
    ProductionJob* getCurrentJob();
    const std::deque<ProductionJob>& getQueue() const;
    bool completeCurrentJob();
    std::string getLastMessage() const;
private:
    ProductionLine& line_;
    OrderRepository& orderRepo_;
    SampleRepository& sampleRepo_;
    std::string lastMessage_;
};
