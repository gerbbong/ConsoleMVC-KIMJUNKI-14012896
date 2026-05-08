#include "OrderView.h"
#include "ConsoleHelper.h"
#include <iostream>
#include <iomanip>

OrderView::OrderView(OrderController& controller) : ctrl_(controller) {}

void OrderView::run() {
    while (true) {
        showMenu();
        int choice = Console::readInt("선택: ");
        switch (choice) {
            case 1: placeOrder();          break;
            case 2: listReservedOrders();  break;
            case 3: approveOrReject();     break;
            case 0: return;
            default:
                std::cout << "잘못된 선택입니다.\n";
                Console::pause();
        }
    }
}

void OrderView::showMenu() {
    Console::clearScreen();
    Console::printTitle("주문 관리");
    std::cout << "  1. 주문 접수\n";
    std::cout << "  2. 접수 목록 확인 (RESERVED)\n";
    std::cout << "  3. 주문 승인 / 거절\n";
    std::cout << "  0. 메인 메뉴로\n";
    Console::printLine();
}

void OrderView::placeOrder() {
    Console::clearScreen();
    Console::printTitle("주문 접수");

    std::string sampleId = Console::readString("시료 ID  : ");
    std::string customer = Console::readString("고객명   : ");
    int qty              = Console::readInt("주문 수량: ");

    int orderId = ctrl_.placeOrder(sampleId, customer, qty);
    if (orderId > 0)
        std::cout << "\n[성공] 주문 접수 완료 (주문번호: " << orderId << ", 상태: RESERVED)\n";
    else
        std::cout << "\n[실패] " << ctrl_.getLastMessage() << '\n';
    Console::pause();
}

void OrderView::listReservedOrders() {
    Console::clearScreen();
    Console::printTitle("접수 목록 (RESERVED)");

    auto orders = ctrl_.getReservedOrders();
    if (orders.empty())
        std::cout << "  접수된 주문이 없습니다.\n";
    else
        printOrderTable(orders);
    Console::pause();
}

void OrderView::approveOrReject() {
    Console::clearScreen();
    Console::printTitle("주문 승인 / 거절");

    auto orders = ctrl_.getReservedOrders();
    if (orders.empty()) {
        std::cout << "  처리할 접수 주문이 없습니다.\n";
        Console::pause();
        return;
    }

    printOrderTable(orders);
    Console::printLine();

    int orderId = Console::readInt("처리할 주문번호 (0: 취소): ");
    if (orderId == 0) return;

    std::cout << "  1. 승인 (APPROVE)   2. 거절 (REJECT)\n";
    int action = Console::readInt("선택: ");

    bool ok = false;
    if (action == 1)
        ok = ctrl_.approveOrder(orderId);
    else if (action == 2)
        ok = ctrl_.rejectOrder(orderId);
    else {
        std::cout << "취소되었습니다.\n";
        Console::pause();
        return;
    }

    std::cout << (ok ? "\n[성공] " : "\n[실패] ") << ctrl_.getLastMessage() << '\n';
    Console::pause();
}

void OrderView::printOrderTable(const std::vector<Order*>& orders) {
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
}
