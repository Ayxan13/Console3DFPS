//
// Created by Ayxan Haqverdili on 2021-04-22.
//

#pragma once
#include <chrono>

class StopWatch final {
private:
    using clock = std::chrono::system_clock;
    clock::time_point _lastChecked;
public:
    StopWatch()
        : _lastChecked{ clock::now() }
    { }

    [[nodiscard]] std::chrono::duration<float> Ellapsed() noexcept {
        auto const now = clock::now();
        return now - std::exchange(_lastChecked, now);
    }
};