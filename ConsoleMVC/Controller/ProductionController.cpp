#include "ProductionController.h"

ProductionController::ProductionController(ProductionLine& line, OrderRepository& orderRepo,
                                           SampleRepository& sampleRepo)
    : line_(line), orderRepo_(orderRepo), sampleRepo_(sampleRepo) {}

bool ProductionController::hasCurrentJob() const {
    return line_.hasCurrentJob();
}

ProductionJob* ProductionController::getCurrentJob() {
    return line_.getCurrentJob();
}

const std::deque<ProductionJob>& ProductionController::getQueue() const {
    return line_.getQueue();
}

bool ProductionController::completeCurrentJob() {
    ProductionJob* job = line_.getCurrentJob();
    if (!job) {
        lastMessage_ = "현재 생산 중인 작업이 없습니다.";
        return false;
    }

    Order* order = orderRepo_.findById(job->orderId);
    Sample* sample = sampleRepo_.findById(job->sampleId);

    if (order && sample) {
        // 생산된 수량을 재고에 추가 후 주문 수량 차감
        // 잔여재고 = actualQuantity - shortage (수율 고려 추가분)
        sample->stock += job->actualQuantity;
        sample->stock -= order->quantity;
        if (sample->stock < 0) sample->stock = 0;
        order->status = OrderStatus::CONFIRMED;
        lastMessage_ = "생산 완료. 주문이 CONFIRMED 상태로 변경되었습니다.";
    }

    line_.completeCurrentJob();
    return true;
}

std::string ProductionController::getLastMessage() const {
    return lastMessage_;
}
