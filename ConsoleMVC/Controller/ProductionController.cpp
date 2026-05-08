#include "ProductionController.h"

ProductionController::ProductionController(ProductionLine& line, OrderRepository& orderRepo,
                                           SampleRepository& sampleRepo)
    : line_(line), orderRepo_(orderRepo), sampleRepo_(sampleRepo) {}

void ProductionController::update() {
    // 완료된 작업을 순서대로 처리 (연속 완료 케이스 포함)
    while (line_.hasCurrentJob()) {
        ProductionJob* job = line_.getCurrentJob();
        if (!job->isComplete()) break;
        finishJob(*job);
        line_.completeCurrentJob();
    }
}

void ProductionController::finishJob(ProductionJob& job) {
    Order* order = orderRepo_.findById(job.orderId);
    Sample* sample = sampleRepo_.findById(job.sampleId);
    if (order && sample) {
        sample->stock += job.actualQuantity;
        sample->stock -= order->quantity;
        if (sample->stock < 0) sample->stock = 0;
        order->status = OrderStatus::CONFIRMED;
    }
}

bool ProductionController::hasCurrentJob() const {
    return line_.hasCurrentJob();
}

const ProductionJob* ProductionController::getCurrentJob() const {
    return const_cast<ProductionLine&>(line_).getCurrentJob();
}

const std::deque<ProductionJob>& ProductionController::getQueue() const {
    return line_.getQueue();
}

int ProductionController::getQueueSize() const {
    return static_cast<int>(line_.getQueue().size());
}
