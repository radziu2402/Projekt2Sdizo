#include "TimeCounter.h"

TimeCounter::TimeCounter() {
    duration = 0;
}

void TimeCounter::startTimer() {
    //Ustawiamy początkowy czas wykonywania.
    startTime = std::chrono::high_resolution_clock::now();
}

void TimeCounter::stopTimer() {
    //Ustawiamy końcowy czas wykonywania i zapisujemy różnicę do 'duration'.
    endTime = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::micro> time = endTime - startTime;
    duration = time.count();
}

double TimeCounter::getDuration() {
    return duration;
}