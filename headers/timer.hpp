#ifndef TIMER_HPP
#define TIMER_HPP
#include <iostream>
#include <string>
using namespace std;

class Timer {
    protected:
        int startTime;
        int endTime;

    public:
        Timer();
        int getStartTime() const;
        int getEndTime() const;
        void setEndTime(int end);
        void resetTime();
        int calculateTime();
};

#endif