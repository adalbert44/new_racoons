#include "input_text.h"

void input_text_draw()
{
    window_shade.alpha=0.1;
    window_shade.draw_state();
    input_info_background.draw_state();
    input_feel.draw_state();
    input_ok.draw_state();
    input_bad.draw_state();

    drawstring(input_feel.x1,input_feel.y2,1.0,info_name);
}

void input_text_reaction(int button, int state)
{
    if (button==GLUT_LEFT_BUTTON && state==GLUT_DOWN)
    {
        if (input_ok.f.in())
        {
            input_ok.press_down();
            pressed_do=&input_ok;
        }

        if (input_bad.f.in())
        {
            input_bad.press_down();
            pressed_do=&input_bad;
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

void input_text_keyboard(char c)
{
    if (c>='a' && c<='z')
        info_name+=c;

    if (c>='A' && c<='Z')
        info_name+=c;

    if (c=='_')
        info_name+=c;

    if (c>='0' && c<='9')
        info_name+=c;

    if (c=='.')
        info_name+=c;

    if (info_name.size()>15)
        info_name.pop_back();
}

void input_text_skeyboard(char c)
{
    if (c==GLUT_KEY_LEFT)
        if (!info_name.empty())
        info_name.pop_back();
}
