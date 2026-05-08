#include "MainView.h"
#include "ConsoleHelper.h"
#include <iostream>
#include <iomanip>

MainView::MainView(SampleView& sv, OrderView& ov, MonitorView& mv,
                   ProductionView& pv, ReleaseView& rv, MonitorController& mc)
    : sampleView_(sv), orderView_(ov), monitorView_(mv),
      productionView_(pv), releaseView_(rv), monitorCtrl_(mc) {}

void MainView::run() {
    while (true) {
        showMenu();
        int choice = Console::readInt("선택: ");
        switch (choice) {
            case 1: sampleView_.run();     break;
            case 2: orderView_.run();      break;
            case 3: monitorView_.run();    break;
            case 4: releaseView_.run();    break;
            case 5: productionView_.run(); break;
            case 0:
                std::cout << "\n시스템을 종료합니다.\n";
                return;
            default:
                std::cout << "잘못된 선택입니다.\n";
                Console::pause();
        }
    }
}

void MainView::showMenu() {
    Console::clearScreen();
    Console::printTitle("반도체 시료 생산 주문 관리 시스템");

    // 요약 정보
    auto counts    = monitorCtrl_.getOrderCountByStatus();
    auto stockList = monitorCtrl_.getStockStatusList();

    std::cout << "\n[시스템 현황 요약]\n";
    Console::printLine(40);
    std::cout << "  주문 접수(RESERVED)  : " << counts[OrderStatus::RESERVED]  << " 건\n";
    std::cout << "  생산 중  (PRODUCING) : " << counts[OrderStatus::PRODUCING] << " 건\n";
    std::cout << "  출고 대기(CONFIRMED) : " << counts[OrderStatus::CONFIRMED] << " 건\n";
    std::cout << "  출고 완료(RELEASE)   : " << counts[OrderStatus::RELEASE]   << " 건\n";

    if (!stockList.empty()) {
        std::cout << "\n[재고 요약]\n";
        Console::printLine(40);
        for (const auto& ss : stockList)
            std::cout << "  " << std::left << std::setw(20) << ss.sampleName
                      << " 재고: " << std::setw(5) << ss.stock
                      << " [" << ss.label << "]\n";
    }

    std::cout << '\n';
    Console::printLine();
    std::cout << "  1. 시료 관리\n";
    std::cout << "  2. 주문 (접수 / 승인 / 거절)\n";
    std::cout << "  3. 모니터링\n";
    std::cout << "  4. 출고 처리\n";
    std::cout << "  5. 생산 라인\n";
    std::cout << "  0. 종료\n";
    Console::printLine();
}
