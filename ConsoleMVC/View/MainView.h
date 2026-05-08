#pragma once
#include "SampleView.h"
#include "OrderView.h"
#include "MonitorView.h"
#include "ProductionView.h"
#include "ReleaseView.h"
#include "../Controller/MonitorController.h"
#include "../Controller/ProductionController.h"

class MainView {
public:
    MainView(SampleView& sv, OrderView& ov, MonitorView& mv,
             ProductionView& pv, ReleaseView& rv,
             MonitorController& mc, ProductionController& pc);
    void run();
private:
    void showMenu();
    SampleView&         sampleView_;
    OrderView&          orderView_;
    MonitorView&        monitorView_;
    ProductionView&     productionView_;
    ReleaseView&        releaseView_;
    MonitorController&  monitorCtrl_;
    ProductionController& productionCtrl_;
};
