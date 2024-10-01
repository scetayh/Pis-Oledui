#include "../../include/polonium/Element.h"
#include <iostream>
extern "C"
{
    #include "../../include/pis-oledui/oled.h"
    #include <wiringPi.h>
    #include <wiringPiI2C.h>
    #include "../../include/pis-oledui/GCFK.h"
    #include <stdio.h>
    #include <string.h>
    #include "stdlib.h"
}


void SingleRenderWrapper::Render()
{
    if(Render_Needed)
    {
        element_.Render();
        Render_Needed = false;
    }
}