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
    duration = std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime).count();
}

double TimeCounter::getDuration() {
    return duration;
}