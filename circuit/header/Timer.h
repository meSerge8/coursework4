#pragma once
#include <time.h>

#include <iostream>
#include <string>

using namespace std;

class Timer {
   private:
    clock_t startTime;

   public:
    Timer();
    ~Timer();

    void Start();
    double Finish();
};
