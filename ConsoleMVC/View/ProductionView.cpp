#include "ProductionView.h"
#include "ConsoleHelper.h"
#include <iostream>
#include <iomanip>

ProductionView::ProductionView(ProductionController& controller) : ctrl_(controller) {}

void ProductionView::run() {
    while (true) {
        showStatus();
        Console::printLine();
        std::cout << "  1. 현재 생산 완료 처리\n";
        std::cout << "  0. 메인 메뉴로\n";
        int choice = Console::readInt("선택: ");
        if (choice == 0) return;
        if (choice == 1) {
            bool ok = ctrl_.completeCurrentJob();
            std::cout << (ok ? "\n[성공] " : "\n[실패] ") << ctrl_.getLastMessage() << '\n';
            Console::pause();
        } else {
            std::cout << "잘못된 선택입니다.\n";
            Console::pause();
        }
    }
}

void ProductionView::showStatus() {
    Console::clearScreen();
    Console::printTitle("생산 라인 현황");

    // ── 현재 생산 중 ────────────────────────────────
    std::cout << "\n[현재 생산 중]\n";
    Console::printLine(55);
    if (!ctrl_.hasCurrentJob()) {
        std::cout << "  현재 생산 중인 작업이 없습니다.\n";
    } else {
        const auto* job = ctrl_.getCurrentJob();
        std::cout << "  주문번호   : " << job->orderId      << '\n';
        std::cout << "  시료 ID    : " << job->sampleId     << '\n';
        std::cout << "  부족분     : " << job->shortage     << " ea\n";
        std::cout << "  실생산량   : " << job->actualQuantity << " ea\n";
        std::cout << "  총생산시간 : " << std::fixed << std::setprecision(1)
                  << job->totalTime << " min\n";
    }

    // ── 생산 대기 큐 ─────────────────────────────────
    std::cout << "\n[생산 대기 목록]\n";
    Console::printLine(65);
    const auto& queue = ctrl_.getQueue();
    if (queue.empty()) {
        std::cout << "  대기 중인 작업이 없습니다.\n";
    } else {
        std::cout << std::left
                  << std::setw(10) << "주문번호"
                  << std::setw(10) << "시료ID"
                  << std::setw(10) << "부족분"
                  << std::setw(12) << "실생산량"
                  << std::setw(14) << "총생산시간(min)" << '\n';
        Console::printLine(60);
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
