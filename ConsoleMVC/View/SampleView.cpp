#include "SampleView.h"
#include "ConsoleHelper.h"
#include <iostream>
#include <iomanip>

SampleView::SampleView(SampleController& controller) : ctrl_(controller) {}

void SampleView::run() {
    while (true) {
        showMenu();
        int choice = Console::readInt("선택: ");
        switch (choice) {
            case 1: registerSample(); break;
            case 2: listSamples();    break;
            case 3: searchSamples();  break;
            case 0: return;
            default:
                std::cout << "잘못된 선택입니다.\n";
                Console::pause();
        }
    }
}

void SampleView::showMenu() {
    Console::clearScreen();
    Console::printTitle("시료 관리");
    std::cout << "  1. 시료 등록\n";
    std::cout << "  2. 시료 조회\n";
    std::cout << "  3. 시료 검색\n";
    std::cout << "  0. 메인 메뉴로\n";
    Console::printLine();
}

void SampleView::registerSample() {
    Console::clearScreen();
    Console::printTitle("시료 등록");
    std::cout << "  예) ID: S-001 / 이름: 실리콘 웨이퍼-8인치 / 생산시간: 0.5 / 수율: 0.92\n\n";

    std::string id   = Console::readString("시료 ID        : ");
    std::string name = Console::readString("시료 이름      : ");
    double time      = Console::readDouble("평균 생산시간  (min/ea): ");
    double yield     = Console::readDouble("수율           (0~1)  : ");

    if (ctrl_.registerSample(id, name, time, yield))
        std::cout << "\n[성공] " << ctrl_.getLastMessage() << '\n';
    else
        std::cout << "\n[실패] " << ctrl_.getLastMessage() << '\n';
    Console::pause();
}

void SampleView::listSamples() {
    Console::clearScreen();
    Console::printTitle("시료 목록");

    auto& samples = ctrl_.getAllSamples();
    if (samples.empty()) {
        std::cout << "  등록된 시료가 없습니다.\n";
    } else {
        std::cout << std::left
                  << std::setw(10) << "ID"
                  << std::setw(28) << "이름"
                  << std::setw(16) << "생산시간(min)"
                  << std::setw(8)  << "수율"
                  << std::setw(8)  << "재고" << '\n';
        Console::printLine(70);
        for (const auto& s : samples) {
            std::cout << std::left
                      << std::setw(10) << s.id
                      << std::setw(28) << s.name
                      << std::setw(16) << s.avgProductionTime
                      << std::setw(8)  << s.yield
                      << std::setw(8)  << s.stock << '\n';
        }
    }
    Console::pause();
}

void SampleView::searchSamples() {
    Console::clearScreen();
    Console::printTitle("시료 검색");

    std::string keyword = Console::readString("검색어 (이름): ");
    auto results = ctrl_.searchByName(keyword);

    if (results.empty()) {
        std::cout << "  검색 결과가 없습니다.\n";
    } else {
        std::cout << "\n검색 결과: " << results.size() << "건\n";
        Console::printLine(70);
        std::cout << std::left
                  << std::setw(10) << "ID"
                  << std::setw(28) << "이름"
                  << std::setw(16) << "생산시간(min)"
                  << std::setw(8)  << "수율"
                  << std::setw(8)  << "재고" << '\n';
        Console::printLine(70);
        for (const auto* s : results) {
            std::cout << std::left
                      << std::setw(10) << s->id
                      << std::setw(28) << s->name
                      << std::setw(16) << s->avgProductionTime
                      << std::setw(8)  << s->yield
                      << std::setw(8)  << s->stock << '\n';
        }
    }
    Console::pause();
}
