#pragma once
#include "../Controller/MonitorController.h"

class MonitorView {
public:
    explicit MonitorView(MonitorController& controller);
    void run();
private:
    void showMonitor();
    MonitorController& ctrl_;
};
