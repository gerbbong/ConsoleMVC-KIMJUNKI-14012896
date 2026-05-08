#include "ReleaseController.h"

ReleaseController::ReleaseController(OrderRepository& orderRepo, SampleRepository& sampleRepo)
    : orderRepo_(orderRepo), sampleRepo_(sampleRepo) {}

std::vector<Order*> ReleaseController::getConfirmedOrders() {
    return orderRepo_.findByStatus(OrderStatus::CONFIRMED);
}

bool ReleaseController::release(int orderId) {
    Order* order = orderRepo_.findById(orderId);
    if (!order || order->status != OrderStatus::CONFIRMED) {
        lastMessage_ = "출고 처리할 수 없는 주문입니다.";
        return false;
    }
    order->status = OrderStatus::RELEASE;
    lastMessage_ = "출고 처리 완료. 주문이 RELEASE 상태로 변경되었습니다.";
    return true;
}

std::string ReleaseController::getLastMessage() const {
    return lastMessage_;
}
