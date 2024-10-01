#include <wiringPi.h>
#include <stdio.h>
#include <string.h>
#include <wiringPiI2C.h>
#include "../../include/pis-oledui/oled.h"
#include "../../include/pis-oledui/GCFK.h"
 
int fd;

void oled_write_one_byte(uint8_t dat,uint8_t mode)
{
    wiringPiI2CWriteReg8(fd,mode,dat);
}

void InitScreen()	//画上四分之一部分的框
{
//	OLED_Clear();
	OLED_DrawLine(0,0,127,0,1);
	OLED_DrawLine(0,15,127,15,1);
	OLED_DrawLine(0,0,0,15,1);
	OLED_DrawLine(127,0,127,15,1);
	OLED_Refresh();
}

int main(void)
{ 
    if(wiringPiSetup() < 0) //当使用这个函数初始化树莓派引脚时，程序使用的是wiringPi 引脚编号表。
        return 1;
    fd = wiringPiI2CSetup (SlaveAddress);
    if(fd < 0)
    {
        printf("IIC初始化失败\r\n");
        return fd;
    }
    printf("%f\n",fd);
    OLED_Init();
    OLED_Clear();
    //InitScreen();
    //OLED_ShowString(1,1,(char *)"Hello World!",12,1);
    InitScreen();
    OLED_Refresh();

    while(1)
    {
	int ch = 0, top = 0;
	char get_st[1000] = "";
    system(STTY_US TTY_PATH);
    // esc=27 d
    while(1)
    {
        ch = GetChar();
        if(ch == 127)
        {
            get_st[top-1] = ' ';
            top --;
        }
        else if(ch >= 32 && ch <= 126)
        {
            get_st[top++] += (char)ch;
        }
        if(ch == 3)
        {
            system(STTY_DEF TTY_PATH);
        }
        for(int i = 0 ; i <= top ; i ++)
        {
            printf("%c",get_st[i]);
        }
        printf("\n");
        OLED_ShowString(1,1,(char *)get_st,12,1);
        InitScreen();
        OLED_Refresh();
        }
    }

 
    return 0;
}
 
