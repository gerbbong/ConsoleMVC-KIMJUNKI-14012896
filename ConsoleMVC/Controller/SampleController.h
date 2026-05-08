#pragma once
#include "../Model/SampleRepository.h"
#include <string>
#include <vector>

class SampleController {
public:
    explicit SampleController(SampleRepository& repo);
    bool registerSample(const std::string& id, const std::string& name,
                        double avgTime, double yield);
    std::vector<Sample>& getAllSamples();
    Sample* findById(const std::string& id);
    std::vector<Sample*> searchByName(const std::string& keyword);
    std::string getLastMessage() const;
private:
    SampleRepository& repo_;
    std::string lastMessage_;
};
