#pragma once
#include <string>

struct Sample {
    std::string id;
    std::string name;
    double avgProductionTime;  // min/ea
    double yield;              // 0~1
    int stock;

    Sample() : avgProductionTime(0.0), yield(0.0), stock(0) {}
    Sample(std::string id, std::string name, double avgTime, double yield, int stock = 0)
        : id(std::move(id)), name(std::move(name)),
          avgProductionTime(avgTime), yield(yield), stock(stock) {}
};
