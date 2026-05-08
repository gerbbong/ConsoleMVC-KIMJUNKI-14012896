#pragma once
#include <iostream>
#include <string>
#include <limits>

namespace Console {

    inline void clearScreen() {
        system("cls");
    }

    inline void pause() {
        std::cout << "\n계속하려면 Enter를 누르세요...";
        std::cin.get();
    }

    inline void printLine(int len = 55) {
        std::cout << std::string(len, '-') << '\n';
    }

    inline void printTitle(const std::string& title) {
        printLine();
        std::cout << "  " << title << '\n';
        printLine();
    }

    inline int readInt(const std::string& prompt) {
        int val;
        while (true) {
            std::cout << prompt;
            if (std::cin >> val) {
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                return val;
            }
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "올바른 정수를 입력하세요.\n";
        }
    }

    inline double readDouble(const std::string& prompt) {
        double val;
        while (true) {
            std::cout << prompt;
            if (std::cin >> val) {
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                return val;
            }
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "올바른 숫자를 입력하세요.\n";
        }
    }

    inline std::string readString(const std::string& prompt) {
        std::cout << prompt;
        std::string val;
        std::getline(std::cin, val);
        return val;
    }

}
