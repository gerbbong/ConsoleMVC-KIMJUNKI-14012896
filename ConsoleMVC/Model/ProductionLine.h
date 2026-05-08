#pragma once
#include "ProductionJob.h"
#include <deque>
#include <optional>

class ProductionLine {
public:
    void enqueue(ProductionJob job);
    bool hasCurrentJob() const;
    ProductionJob* getCurrentJob();
    const std::deque<ProductionJob>& getQueue() const;
    void completeCurrentJob();
    bool isEmpty() const;
private:
    std::optional<ProductionJob> current_;
    std::deque<ProductionJob> queue_;
};
