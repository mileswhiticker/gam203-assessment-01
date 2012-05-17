// ------------------------------------------------------------------------------------------------------
//
//  File: Timer.h
//  Author: Tim Paech, (C) Qantm College 2007
//  Date: 18-09-07
//  About: Timer class functionality
//
// ------------------------------------------------------------------------------------------------------
#ifndef TIMER_H
#define TIMER_H

#include <windows.h>

class Timer
{
public:
  Timer();
  ~Timer()
  {}

  // Reset the timer
  void Reset();

  // Return time in seconds
  float GetTime();

private:
  LARGE_INTEGER m_freq;
  LARGE_INTEGER m_baseTime;
  LARGE_INTEGER m_lastTime;
  float m_deltaTime;
};

#endif // TIMER_H
