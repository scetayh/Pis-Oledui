#include "../../../include/polonium/Elements/TextElements.h"
#include <iostream>
extern "C"
{
#include "../../../include/pis-oledui/oled.h"
#include <wiringPi.h>
#include <wiringPiI2C.h>
#include "../../../include/pis-oledui/GCFK.h"
#include <stdio.h>
#include <string.h>
#include "stdlib.h"
}

void TextBase::Render()
{
    OLED_ShowString(X, Y, (unsigned char *)text_.c_str(), font_size_, 1);
    OLED_Refresh();
}

// int GetChar()
// {
//     fd_set rfds;
//     struct timeval tv;
//     int ch = 0;

//     FD_ZERO(&rfds);
//     FD_SET(0, &rfds);
//     tv.tv_sec = 0;
//     tv.tv_usec = 10; // 设置等待超时时间

//     // 检测键盘是否有输入
//     if (select(1, &rfds, NULL, NULL, &tv) > 0)
//     {
//         ch = getchar();
//     }
//     return ch;
// }

void InputTextBox::Test()
{
    ch_num = GetChar();
    if (ch_num == 13 || ch_num == 3)
        system(STTY_DEF TTY_PATH);
    if (ch_num == 127)
    {
        if(!cover_flag)
            (*(text_.end()-1)) = ' ',cover_flag = true;
        else
            text_.pop_back(),cover_flag = false;
    }
    else if (ch_num >= 32 && ch_num <= 126)
    {
        if(!cover_flag)
            text_.push_back(char(ch_num));
        else (*(text_.end()-1)) = char(ch_num) , cover_flag = false;
    }
        
    if (ch_num == 3)
        system(STTY_DEF TTY_PATH);
}