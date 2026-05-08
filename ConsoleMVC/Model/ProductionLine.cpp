#include "ProductionLine.h"

static void startJob(ProductionJob& job) {
    job.startTime  = std::chrono::steady_clock::now();
    job.hasStarted = true;
}

void ProductionLine::enqueue(ProductionJob job) {
    if (!current_.has_value()) {
        startJob(job);
        current_ = std::move(job);
    } else {
        queue_.push_back(std::move(job));
    }
}

bool ProductionLine::hasCurrentJob() const {
    return current_.has_value();
}

ProductionJob* ProductionLine::getCurrentJob() {
    return current_.has_value() ? &current_.value() : nullptr;
}

const std::deque<ProductionJob>& ProductionLine::getQueue() const {
    return queue_;
}

void ProductionLine::completeCurrentJob() {
    if (!queue_.empty()) {
        current_ = std::move(queue_.front());
        queue_.pop_front();
        startJob(current_.value());
    } else {
        current_.reset();
    }
}

bool ProductionLine::isEmpty() const {
    return !current_.has_value() && queue_.empty();
}
