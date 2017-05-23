#include "bcui.h"
#include <algorithm>
#include <iostream>
#include <vector>



BCUI::BCUI()
{

}

BCUI::~BCUI()
{

}

#ifdef WIN32
bool BCUI::init()
{
    _handle = GetStdHandle(STD_OUTPUT_HANDLE);
    if (_handle == NULL || _handle == INVALID_HANDLE_VALUE)
    {
        return false;
    }
    CONSOLE_CURSOR_INFO cci;
    if (!GetConsoleCursorInfo(_handle, &cci))
    {

        return false;
    }
    cci.bVisible = FALSE;
    if (!SetConsoleCursorInfo(_handle, &cci))
    {
        return false;
    }

    PCONSOLE_FONT_INFOEX pcfi = new CONSOLE_FONT_INFOEX;

    return true;
}

bool BCUI::setPos(int x, int y, BCUI_PIXEL bp)
{
    if (_handle == NULL || _handle == INVALID_HANDLE_VALUE)
    {
        return false;
    }
    COORD pos;
    pos.X = (SHORT)x*2;
    pos.Y = (SHORT)y;
    if (!SetConsoleCursorPosition(_handle, pos))
    {
        return false;
    }
    DWORD bg = 0;
    DWORD fg = FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED;
    if (bp == BCUI_PIXEL_BLACK)
    {
        bg = 0;
    }
    else if (bp == BCUI_PIXEL_WHITE)
    {
        bg = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
    }
    else if (bp == BCUI_PIXEL_RED)
    {
        bg = BACKGROUND_RED;
    }
    else if (bp == BCUI_PIXEL_BLUE)
    {
        bg =  BACKGROUND_GREEN|BACKGROUND_BLUE;
    }
    else if (bp == BCUI_PIXEL_YELLOW)
    {
        bg = BACKGROUND_RED | BACKGROUND_GREEN ;
    }


    CONSOLE_SCREEN_BUFFER_INFO oldInfo;
    if (!GetConsoleScreenBufferInfo(_handle, &oldInfo))
    {
        return false;
    }
    SetConsoleTextAttribute(_handle, bg|fg);
    printf("%c%c", ' ', ' ');
    SetConsoleTextAttribute(_handle, oldInfo.wAttributes);



    return true;
}
#else
bool BCUI::init()
{
    printf("%s", "\033[?25l\033[0m");
    return true;
}

bool BCUI::setPos(int x, int y, BCUI_PIXEL bp)
{
    x = x * 2;
    std::string s;
    s += "\033[" + toString(y) + ";" + toString(x) + "H";
    //s += "\033[0m";

    if (bp == BCUI_PIXEL_BLACK)
    {
        s += "\033[40m";
    }
    else if (bp == BCUI_PIXEL_WHITE)
    {
        s += "\033[47m";
    }
    else if (bp == BCUI_PIXEL_RED)
    {
        s += "\033[41m";
    }
    else if (bp == BCUI_PIXEL_BLUE)
    {
        s += "\033[46m";
    }
    else if (bp == BCUI_PIXEL_YELLOW)
    {
        s += "\033[41;42m";
    }
    s += "  ";
    s += "\033[0m";
    printf("%s", s.c_str());
    return true;
}
#endif




