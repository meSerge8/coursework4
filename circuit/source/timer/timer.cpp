#include "timer.h"

timer::timer() {}

timer::~timer() {}

void timer::Start() {
    startTime = clock();
}

double timer::Finish() {
    return (double)(clock() - startTime) / CLOCKS_PER_SEC;
}