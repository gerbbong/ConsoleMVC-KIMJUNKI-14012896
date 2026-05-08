#pragma once
#include "../Controller/ProductionController.h"

class ProductionView {
public:
    explicit ProductionView(ProductionController& controller);
    void run();
private:
    void showStatus();
    ProductionController& ctrl_;
};
