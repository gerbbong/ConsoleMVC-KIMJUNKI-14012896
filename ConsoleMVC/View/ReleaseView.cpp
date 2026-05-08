#include "ReleaseView.h"
#include "ConsoleHelper.h"
#include <iostream>
#include <iomanip>

ReleaseView::ReleaseView(ReleaseController& controller) : ctrl_(controller) {}

void ReleaseView::run() {
    Console::clearScreen();
    Console::printTitle("출고 처리");

    auto orders = ctrl_.getConfirmedOrders();
    if (orders.empty()) {
        std::cout << "  출고 처리할 주문이 없습니다. (CONFIRMED 상태 주문 없음)\n";
        Console::pause();
        return;
    }

    std::cout << std::left
              << std::setw(10) << "주문번호"
              << std::setw(10) << "시료ID"
              << std::setw(22) << "고객명"
              << std::setw(8)  << "수량" << '\n';
    Console::printLine(52);
    for (const auto* o : orders) {
        std::cout << std::left
                  << std::setw(10) << o->orderId
                  << std::setw(10) << o->sampleId
                  << std::setw(22) << o->customerName
                  << std::setw(8)  << o->quantity << '\n';
    }
    Console::printLine(52);

    int orderId = Console::readInt("출고할 주문번호 (0: 취소): ");
    if (orderId == 0) return;

    bool ok = ctrl_.release(orderId);
    std::cout << (ok ? "\n[성공] " : "\n[실패] ") << ctrl_.getLastMessage() << '\n';
    Console::pause();
}
