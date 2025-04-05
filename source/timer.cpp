#include <iostream>
#include <string>
#include "../headers/timer.hpp"
using namespace std;

// constructor
Timer::Timer() {
    startTime = 0;
    endTime = 0;
}

// access startTime
int Timer::getStartTime() const {
    return this->startTime;
}

// access endTime
int Timer::getEndTime() const {
    return this->endTime;
}

// let user set the end time
void Timer::setEndTime(int end) {
    this->endTime = end;
}

// reset times to 0
void Timer::resetTime() {
    this->startTime = 0;
    this->endTime = 0;
}

// calculate remaining time
int Timer::calculateTime() {
    return this->endTime - this->startTime;
}