#ifndef MessageBox_h
#define MessageBox_h

#ifdef _WIN32
#include "WINDOWS/MessageBoxForWindows.hpp"
#elif TARGET_OS_MAC
#include "MACOS/MessageBoxForMACOS.hpp"
#elif __linux__
//TO-DO
#endif

#endif