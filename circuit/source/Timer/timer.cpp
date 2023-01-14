#include "Timer.h"

Timer::Timer() {}

Timer::~Timer() {}

void Timer::Start() {
    startTime = clock();
}

double Timer::Finish() {
    return (double)(clock() - startTime) / CLOCKS_PER_SEC;
}