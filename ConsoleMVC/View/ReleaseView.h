#pragma once
#include "../Controller/ReleaseController.h"

class ReleaseView {
public:
    explicit ReleaseView(ReleaseController& controller);
    void run();
private:
    ReleaseController& ctrl_;
};
