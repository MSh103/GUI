#ifndef MessageBoxForWindows_h
#define MessageBoxForWindows_h

#include <windows.h>
#include <string>


namespace Gui
{
class MessageBoxM {
private:
    int choice;

public:
    MessageBoxM(LPCSTR Title, LPCSTR Message, DWORD type)
    {
        choice = MessageBoxA(NULL, Message, Title, type);
    }

    int getChoice() { return choice; }
};
}

#endif