#include "choose_lab.h"

void choose_lab_draw()
{
    back_to_main.watch();
    lab_background0.draw_state();
    for (int i=0;i<16;i++)
    {
        if (back_to_main.light>0.0001)
            choose_lab[i].light=0.0; else
            choose_lab[i].watch();
        choose_lab[i].draw_state();
    }


    back_to_main.draw_state();
}

void choose_lab_reaction(int button, int state)
{
    if (button==GLUT_LEFT_BUTTON && state==GLUT_DOWN)
    {
        if (back_to_main.f.in())
        {
            back_to_main.press_down();
            pressed_do=&back_to_main;
        } else
        for (int i=0;i<16;i++)
            if (choose_lab[i].f.in())
            {
                choosen_lab=i;
                choose_lab[i].press_down();
                pressed_do=&choose_lab[i];
            }
    }

    if (button==GLUT_LEFT_BUTTON && state==GLUT_UP)
    {
        if (pressed_do!=NULL)
        {
            (*pressed_do).press_up();
            pressed_do=NULL;
        }
    }
}
