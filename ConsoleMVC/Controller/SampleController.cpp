#include "SampleController.h"

SampleController::SampleController(SampleRepository& repo) : repo_(repo) {}

bool SampleController::registerSample(const std::string& id, const std::string& name,
                                      double avgTime, double yield) {
    if (id.empty() || name.empty()) {
        lastMessage_ = "ID와 이름은 필수 입력값입니다.";
        return false;
    }
    if (avgTime <= 0.0) {
        lastMessage_ = "평균 생산시간은 0보다 커야 합니다.";
        return false;
    }
    if (yield <= 0.0 || yield > 1.0) {
        lastMessage_ = "수율은 0 초과 1 이하이어야 합니다.";
        return false;
    }
    if (!repo_.add(Sample(id, name, avgTime, yield, 0))) {
        lastMessage_ = "이미 존재하는 시료 ID입니다: " + id;
        return false;
    }
    lastMessage_ = "시료가 등록되었습니다.";
    return true;
}

std::vector<Sample>& SampleController::getAllSamples() {
    return repo_.getAll();
}

Sample* SampleController::findById(const std::string& id) {
    return repo_.findById(id);
}

std::vector<Sample*> SampleController::searchByName(const std::string& keyword) {
    return repo_.searchByName(keyword);
}

std::string SampleController::getLastMessage() const {
    return lastMessage_;
}
