#include "ProductionView.h"
#include "ConsoleHelper.h"
#include <iostream>
#include <iomanip>
#include <conio.h>
#include <windows.h>

ProductionView::ProductionView(ProductionController& controller) : ctrl_(controller) {}

void ProductionView::run() {
    while (true) {
        ctrl_.update();
        showStatus();

        std::cout << "\n  [0] 메인 메뉴로  (1초마다 자동 갱신)\n";
        std::cout << "선택: " << std::flush;

        // 1초 동안 50ms 간격으로 키 입력 대기
        for (int i = 0; i < 20; ++i) {
            Sleep(50);
            ctrl_.update();
            if (_kbhit()) {
                char c = _getch();
                std::cout << c << '\n';
                if (c == '0') return;
                break; // 다른 키 → 화면 갱신
            }
        }
    }
}

void ProductionView::showStatus() {
    Console::clearScreen();
    Console::printTitle("생산 라인 현황");

    // ── 현재 생산 중 ────────────────────────────────
    std::cout << "\n[현재 생산 중]\n";
    Console::printLine(60);

    if (!ctrl_.hasCurrentJob()) {
        std::cout << "  현재 생산 중인 작업이 없습니다.\n";
    } else {
        const auto* job = ctrl_.getCurrentJob();
        double elapsed   = job->getElapsedSeconds();
        double remaining = job->getRemainingSeconds();
        int produced     = job->getProducedSoFar();

        // 진행률 바 (20칸)
        int barLen = (job->actualQuantity > 0)
            ? static_cast<int>(20.0 * produced / job->actualQuantity)
            : 0;
        std::string bar(barLen, '#');
        bar.resize(20, '-');

        std::cout << std::fixed << std::setprecision(1);
        std::cout << "  주문번호   : " << job->orderId        << '\n'
                  << "  시료 ID    : " << job->sampleId       << '\n'
                  << "  부족분     : " << job->shortage       << " ea\n"
                  << "  실생산량   : " << job->actualQuantity << " ea\n"
                  << "  총생산시간 : " << job->totalTime
                  << "초 (= " << job->totalTime << "분)\n"
                  << "  경과시간   : " << elapsed   << "s\n"
                  << "  남은시간   : " << remaining << "s\n"
                  << "  생산진행   : [" << bar << "] "
                  << produced << " / " << job->actualQuantity << " ea\n";
    }

    // ── 생산 대기 큐 (FIFO) ──────────────────────────
    std::cout << "\n[생산 대기 목록 (FIFO)]\n";
    Console::printLine(62);
    const auto& queue = ctrl_.getQueue();
    if (queue.empty()) {
        std::cout << "  대기 중인 작업이 없습니다.\n";
    } else {
        std::cout << std::left
                  << std::setw(10) << "주문번호"
                  << std::setw(10) << "시료ID"
                  << std::setw(10) << "부족분"
                  << std::setw(12) << "실생산량"
                  << std::setw(14) << "총시간(초=분)" << '\n';
        Console::printLine(58);
        for (const auto& j : queue) {
            std::cout << std::left
                      << std::setw(10) << j.orderId
                      << std::setw(10) << j.sampleId
                      << std::setw(10) << j.shortage
                      << std::setw(12) << j.actualQuantity
                      << std::fixed << std::setprecision(1)
                      << j.totalTime << '\n';
        }
    }
}
