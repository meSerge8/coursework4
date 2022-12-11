#pragma once
#include <time.h>

#include <iostream>
#include <string>

using namespace std;

class timer {
   private:
    clock_t startTime;

   public:
    timer();
    ~timer();

    void Start();
    double Finish();
};
