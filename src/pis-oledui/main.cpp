#include <iostream>
#include <cstring>
extern void oled_write_one_byte(uint8_t dat,uint8_t mode);
extern "C"
{
    #include <wiringPi.h>
    #include <wiringPiI2C.h>
    #include "../../include/pis-oledui/oled.h"
    #include "../../include/pis-oledui/GCFK.h"
    #include <stdio.h>
    #include <string.h>
    #include "stdlib.h"
}
using namespace std;

void InitScreen()	//画上四分之一部分的框
{
    OLED_DrawLine(0,0,127,0,1);
    OLED_DrawLine(0,15,127,15,1);
    OLED_DrawLine(0,0,0,15,1);
    OLED_DrawLine(127,0,127,15,1);
    OLED_Refresh();
}

void ClearInputScreen()
{
    for(int i = 1 ; i <= 126 ; i ++)
    {
        for(int j = 1 ; j <= 14 ; j ++)
        {
            OLED_DrawPoint(i,j,0);
        }
    }
}

string GSFK() //Get String From Keyboard
{
    string get_st;
    int ch_num;
    system(STTY_US TTY_PATH);
    while(true)
    {
        ch_num = GetChar();
        if(ch_num == 13)
        {
            system(STTY_DEF TTY_PATH);
            break;
        }
        if(ch_num == 127)
        {
            get_st.pop_back();
            ClearInputScreen();
	}
        else if(ch_num >= 32 && ch_num <= 126)
        {
            get_st.push_back(char(ch_num));
        }
        if(ch_num == 3)
        {
            system(STTY_DEF TTY_PATH);
            break;
        }
//	    cout << get_st << '\n';
        OLED_ShowString(1,1,(unsigned char *)get_st.c_str(),12,1);
        InitScreen();
        OLED_Refresh();
    }
    cout << get_st << '\n';
    return get_st;
}

int Init()
{
    if(wiringPiSetup() < 0) //当使用这个函数初始化树莓派引脚时，程序使用的是wiringPi 引脚编号表。
        return 1;
    int fd = wiringPiI2CSetup (SlaveAddress);
    if(fd < 0)
    {
        printf("IIC初始化失败\r\n");
        return fd;
    }
    FILE* pf = fopen("./oled_fd.ini","w");
    fprintf(pf,"%d",fd);
    fclose(pf);
    pf = NULL;
    return 0;
}

string ExecShell(string st) //执行语句并返回输出
{
    FILE *fp;
    const int MAXN = 1E5;
    char buffer[MAXN];
//    int top = 0;
    fp = popen(st.data(), "r");
//    while((buffer[top] = fgetc(fp)) != EOF) top++;
    fgets(buffer, sizeof(buffer), fp);
    printf("%s", buffer);
    pclose(fp);
    return buffer;
}

void ExecScreen()
{
    string st_input = GSFK(), st_output = "";
    st_output = ExecShell(st_input);
    OLED_ShowString(0,16,(unsigned char *)st_output.c_str(),12,1);
    OLED_Refresh();
}

int main()
{
    Init();
    OLED_Init();
    OLED_Clear();

    ExecScreen();

    return 0;
}
