#include "SampleRepository.h"

bool SampleRepository::add(Sample sample) {
    if (exists(sample.id)) return false;
    samples_.push_back(std::move(sample));
    return true;
}

std::vector<Sample>& SampleRepository::getAll() {
    return samples_;
}

Sample* SampleRepository::findById(const std::string& id) {
    for (auto& s : samples_)
        if (s.id == id) return &s;
    return nullptr;
}

std::vector<Sample*> SampleRepository::searchByName(const std::string& keyword) {
    std::vector<Sample*> result;
    for (auto& s : samples_)
        if (s.name.find(keyword) != std::string::npos)
            result.push_back(&s);
    return result;
}

bool SampleRepository::exists(const std::string& id) const {
    for (const auto& s : samples_)
        if (s.id == id) return true;
    return false;
}
