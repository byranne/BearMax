#include <iostream>
#include <string>
#include "../headers/timer.hpp"
using namespace std;

Timer::Timer() {
    startTime = 0;
    endTime = 0;
}

int Timer::getStartTime() const {
    return this->startTime;
}

int Timer::getEndTime() const {
    return this->endTime;
}

int Timer::resetTime() {
    return this->startTime = 0;
}

int Timer::calculateTime() {
    return this->startTime - this->endTime;
}