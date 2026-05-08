#pragma once
#include "Sample.h"
#include <vector>
#include <string>

class SampleRepository {
public:
    bool add(Sample sample);
    std::vector<Sample>& getAll();
    Sample* findById(const std::string& id);
    std::vector<Sample*> searchByName(const std::string& keyword);
    bool exists(const std::string& id) const;
private:
    std::vector<Sample> samples_;
};
