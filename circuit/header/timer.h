#pragma once
#include <iostream>
#include <string>
#include <time.h>

using namespace std;

class timer
{
private:
    clock_t startTime;

public:
    timer();
    ~timer();

    void Start();
    double Finish();
};
