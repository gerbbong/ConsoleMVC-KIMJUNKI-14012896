#include "MonitorView.h"
#include "ConsoleHelper.h"
#include "../Model/OrderStatus.h"
#include <iostream>
#include <iomanip>
#include <vector>

MonitorView::MonitorView(MonitorController& controller) : ctrl_(controller) {}

void MonitorView::run() {
    showMonitor();
}

void MonitorView::showMonitor() {
    Console::clearScreen();
    Console::printTitle("모니터링");

    // ── 주문 현황 요약 ──────────────────────────────
    std::cout << "\n[주문 현황]\n";
    Console::printLine(30);
    auto counts = ctrl_.getOrderCountByStatus();
    std::cout << std::left << std::setw(14) << "상태" << "건수\n";
    Console::printLine(22);
    std::cout << std::setw(14) << "RESERVED"  << counts[OrderStatus::RESERVED]  << '\n';
    std::cout << std::setw(14) << "PRODUCING" << counts[OrderStatus::PRODUCING] << '\n';
    std::cout << std::setw(14) << "CONFIRMED" << counts[OrderStatus::CONFIRMED] << '\n';
    std::cout << std::setw(14) << "RELEASE"   << counts[OrderStatus::RELEASE]   << '\n';

    // ── 상태별 주문 목록 ────────────────────────────
    const std::vector<OrderStatus> statuses = {
        OrderStatus::RESERVED, OrderStatus::PRODUCING,
        OrderStatus::CONFIRMED, OrderStatus::RELEASE
    };
    auto ordersByStatus = ctrl_.getOrdersByStatus();

    for (auto status : statuses) {
        auto it = ordersByStatus.find(status);
        if (it == ordersByStatus.end() || it->second.empty()) continue;

        std::cout << "\n[" << statusToString(status) << " 주문 목록]\n";
        Console::printLine(55);
        std::cout << std::left
                  << std::setw(10) << "주문번호"
                  << std::setw(10) << "시료ID"
                  << std::setw(22) << "고객명"
                  << std::setw(8)  << "수량" << '\n';
        Console::printLine(55);
        for (const auto* o : it->second) {
            std::cout << std::left
                      << std::setw(10) << o->orderId
                      << std::setw(10) << o->sampleId
                      << std::setw(22) << o->customerName
                      << std::setw(8)  << o->quantity << '\n';
        }
    }

    // ── 재고 현황 ───────────────────────────────────
    std::cout << "\n[재고 현황]\n";
    Console::printLine(65);
    std::cout << std::left
              << std::setw(10) << "시료ID"
              << std::setw(26) << "시료명"
              << std::setw(8)  << "재고"
              << std::setw(12) << "주문대기량"
              << std::setw(8)  << "상태" << '\n';
    Console::printLine(65);
    auto stockList = ctrl_.getStockStatusList();
    for (const auto& ss : stockList) {
        std::cout << std::left
                  << std::setw(10) << ss.sampleId
                  << std::setw(26) << ss.sampleName
                  << std::setw(8)  << ss.stock
                  << std::setw(12) << ss.pendingQty
                  << std::setw(8)  << ss.label << '\n';
    }

    Console::pause();
}
