#include "OrderController.h"
#include <cmath>

OrderController::OrderController(OrderRepository& orderRepo, SampleRepository& sampleRepo,
                                 ProductionLine& productionLine)
    : orderRepo_(orderRepo), sampleRepo_(sampleRepo), productionLine_(productionLine) {}

int OrderController::placeOrder(const std::string& sampleId,
                                const std::string& customerName, int qty) {
    if (!sampleRepo_.findById(sampleId)) {
        lastMessage_ = "존재하지 않는 시료 ID입니다.";
        return -1;
    }
    if (qty <= 0) {
        lastMessage_ = "수량은 1 이상이어야 합니다.";
        return -1;
    }
    if (customerName.empty()) {
        lastMessage_ = "고객명을 입력하세요.";
        return -1;
    }
    Order order(0, sampleId, customerName, qty);
    return orderRepo_.add(order);
}

std::vector<Order*> OrderController::getReservedOrders() {
    return orderRepo_.findByStatus(OrderStatus::RESERVED);
}

bool OrderController::approveOrder(int orderId) {
    Order* order = orderRepo_.findById(orderId);
    if (!order || order->status != OrderStatus::RESERVED) {
        lastMessage_ = "처리할 수 없는 주문입니다.";
        return false;
    }
    Sample* sample = sampleRepo_.findById(order->sampleId);
    if (!sample) {
        lastMessage_ = "시료를 찾을 수 없습니다.";
        return false;
    }

    if (sample->stock >= order->quantity) {
        // 재고 충분 → 즉시 CONFIRMED
        sample->stock -= order->quantity;
        order->status = OrderStatus::CONFIRMED;
        lastMessage_ = "재고 충분. 즉시 CONFIRMED 처리되었습니다.";
    } else {
        // 재고 부족 → 생산라인 등록
        int shortage = order->quantity - sample->stock;
        int actualQty = static_cast<int>(
            std::ceil(static_cast<double>(shortage) / (sample->yield * 0.9)));
        double totalTime = sample->avgProductionTime * actualQty;

        productionLine_.enqueue(ProductionJob(orderId, sample->id, shortage, actualQty, totalTime));
        order->status = OrderStatus::PRODUCING;
        lastMessage_ = "재고 부족. 생산라인에 등록되었습니다. (PRODUCING)";
    }
    return true;
}

bool OrderController::rejectOrder(int orderId) {
    Order* order = orderRepo_.findById(orderId);
    if (!order || order->status != OrderStatus::RESERVED) {
        lastMessage_ = "처리할 수 없는 주문입니다.";
        return false;
    }
    order->status = OrderStatus::REJECTED;
    lastMessage_ = "주문이 거절되었습니다. (REJECTED)";
    return true;
}

std::string OrderController::getLastMessage() const {
    return lastMessage_;
}
