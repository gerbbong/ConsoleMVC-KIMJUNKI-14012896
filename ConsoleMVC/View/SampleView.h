#pragma once
#include "../Controller/SampleController.h"

class SampleView {
public:
    explicit SampleView(SampleController& controller);
    void run();
private:
    void showMenu();
    void registerSample();
    void listSamples();
    void searchSamples();
    SampleController& ctrl_;
};
