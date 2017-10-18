#include "lab_mode.h"

void lab_mode_draw()
{
    statement_show.draw_state();
    answer_lab.draw_state();
}

void lab_mode_reaction(int button, int state)
{
    if (button==GLUT_LEFT_BUTTON && state==GLUT_DOWN)
    {
        if (statement_show.f.in())
        {
            statement_show.press_down();
            pressed_do=&statement_show;
        }
        if (answer_lab.f.in())
        {
            answer_lab.press_down();
            pressed_do=&answer_lab;
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

int show_statement()
{
    window_message=1;
    window_picture_used=1;
    window_picture.clear();
    window_picture.pb(Figure(350,WinWid-350,50,WinHei/2.0-25,choose_lab_tex[choosen_lab],1.0));
    window_picture.pb(Figure(400,WinWid-400,WinHei/2.0+25,WinHei-50,choose_labs_tex[choosen_lab],1.0));
}

int read_anses()
{
    input_info_mode=1;
    input_ok.to_do=&check_anses;
}
