#pragma once

#include <chrono>

struct TimeMeasurement {
    double first;
    double second;
};

class TimeCounter {
private:
    double duration;
    std::chrono::high_resolution_clock::time_point startTime;
    std::chrono::high_resolution_clock::time_point endTime;
public:
    TimeCounter();

    void startTimer();

    void stopTimer();

    double getDuration();
};