#ifndef MessageBoxForWindows_h
#define MessageBoxForWindows_h

#include <windows.h>
#include <string>

class MessageBoxM {
private:
    int choice;

public:
    MessageBoxM(LPCSTR Title, LPCSTR Message, DWORD type);

    int getChoice() { return choice; }
};

#endif