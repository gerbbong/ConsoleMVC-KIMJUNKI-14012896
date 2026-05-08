#include <windows.h>
#include "Model/SampleRepository.h"
#include "Model/OrderRepository.h"
#include "Model/ProductionLine.h"
#include "Controller/SampleController.h"
#include "Controller/OrderController.h"
#include "Controller/MonitorController.h"
#include "Controller/ProductionController.h"
#include "Controller/ReleaseController.h"
#include "View/MainView.h"
#include "View/SampleView.h"
#include "View/OrderView.h"
#include "View/MonitorView.h"
#include "View/ProductionView.h"
#include "View/ReleaseView.h"

int main() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    // Model (데이터 저장소)
    SampleRepository sampleRepo;
    OrderRepository  orderRepo;
    ProductionLine   productionLine;

    // Controller (비즈니스 로직)
    SampleController    sampleCtrl(sampleRepo);
    OrderController     orderCtrl(orderRepo, sampleRepo, productionLine);
    MonitorController   monitorCtrl(orderRepo, sampleRepo);
    ProductionController productionCtrl(productionLine, orderRepo, sampleRepo);
    ReleaseController   releaseCtrl(orderRepo, sampleRepo);

    // View (화면 출력 및 입력)
    SampleView     sampleView(sampleCtrl);
    OrderView      orderView(orderCtrl);
    MonitorView    monitorView(monitorCtrl);
    ProductionView productionView(productionCtrl);
    ReleaseView    releaseView(releaseCtrl);

    MainView mainView(sampleView, orderView, monitorView,
                      productionView, releaseView, monitorCtrl);
    mainView.run();

    return 0;
}
