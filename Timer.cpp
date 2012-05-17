// ------------------------------------------------------------------------------------------------------
//
//  File: Utils.cpp
//  Author: Tim Paech, (C) Qantm College 2007
//  Date: 18-09-07
//  About: Timer class functionality
//
// ------------------------------------------------------------------------------------------------------

#include "Timer.h"


Timer::Timer()
{
  QueryPerformanceFrequency(&m_freq);
  Reset();
  m_deltaTime = 0.0f;
}

void Timer::Reset()
{
  QueryPerformanceCounter(&m_baseTime);
  QueryPerformanceCounter(&m_lastTime);
}

float Timer::GetTime()
{
  LARGE_INTEGER curTime;
  QueryPerformanceCounter(&curTime);

  return (float)(curTime.QuadPart - m_baseTime.QuadPart) / (float)m_freq.QuadPart;
}
