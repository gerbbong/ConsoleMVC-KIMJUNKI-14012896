#include "MainView.h"
#include "ConsoleHelper.h"
#include <iostream>
#include <iomanip>
#include <chrono>
#include <ctime>

namespace {
    std::string currentTimeStr() {
        auto now = std::chrono::system_clock::now();
        std::time_t t = std::chrono::system_clock::to_time_t(now);
        std::tm tm{};
        localtime_s(&tm, &t);
        char buf[32];
        std::strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", &tm);
        return buf;
    }
}

MainView::MainView(SampleView& sv, OrderView& ov, MonitorView& mv,
                   ProductionView& pv, ReleaseView& rv,
                   MonitorController& mc, ProductionController& pc)
    : sampleView_(sv), orderView_(ov), monitorView_(mv),
      productionView_(pv), releaseView_(rv),
      monitorCtrl_(mc), productionCtrl_(pc) {}

void MainView::run() {
    while (true) {
        productionCtrl_.update(); // 생산 완료 자동 처리
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

    // ── 현황 요약 ───────────────────────────────────
    int producing = productionCtrl_.hasCurrentJob() ? 1 : 0;
    int waiting   = productionCtrl_.getQueueSize();

    std::cout << "\n[현황]\n";
    Console::printLine(45);
    std::cout << std::left
              << "  현재 시각     : " << currentTimeStr() << '\n'
              << "  등록 시료     : " << monitorCtrl_.getTotalSampleCount() << " 종\n"
              << "  총 재고       : " << monitorCtrl_.getTotalStock()       << " ea\n"
              << "  전체 주문     : " << monitorCtrl_.getTotalOrderCount()  << " 건\n"
              << "  생산 라인     : " << producing << "건 생산중, "
                                      << waiting   << "건 대기중\n";

    // ── 메뉴 ────────────────────────────────────────
    std::cout << '\n';
    Console::printLine(45);
    std::cout << "  1. 시료 관리\n"
              << "  2. 주문 (접수 / 승인 / 거절)\n"
              << "  3. 모니터링\n"
              << "  4. 출고 처리\n"
              << "  5. 생산 라인\n"
              << "  0. 종료\n";
    Console::printLine(45);
}
