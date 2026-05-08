#pragma once
#include <string>
#include <chrono>
#include <algorithm>

struct ProductionJob {
    int orderId;
    std::string sampleId;
    int shortage;
    int actualQuantity;
    double totalTime;          // 총 생산시간 (콘솔에서 초 = 실제 분)
    double avgProductionTime;  // ea당 시간 (콘솔에서 초/ea = 실제 min/ea)

    bool hasStarted = false;
    std::chrono::steady_clock::time_point startTime;

    ProductionJob() : orderId(0), shortage(0), actualQuantity(0),
                      totalTime(0.0), avgProductionTime(0.0) {}

    ProductionJob(int orderId, std::string sampleId, int shortage,
                  int actual, double totalTime, double avgTime)
        : orderId(orderId), sampleId(std::move(sampleId)),
          shortage(shortage), actualQuantity(actual),
          totalTime(totalTime), avgProductionTime(avgTime) {}

    double getElapsedSeconds() const {
        if (!hasStarted) return 0.0;
        auto now = std::chrono::steady_clock::now();
        return std::chrono::duration<double>(now - startTime).count();
    }

    int getProducedSoFar() const {
        if (!hasStarted || avgProductionTime <= 0.0) return 0;
        int produced = static_cast<int>(getElapsedSeconds() / avgProductionTime);
        return produced < actualQuantity ? produced : actualQuantity;
    }

    double getRemainingSeconds() const {
        if (!hasStarted) return totalTime;
        double r = totalTime - getElapsedSeconds();
        return r < 0.0 ? 0.0 : r;
    }

    bool isComplete() const {
        return hasStarted && getElapsedSeconds() >= totalTime;
    }
};
