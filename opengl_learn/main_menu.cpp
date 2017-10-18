#include "main_menu.h"
#include "choose_lab.h"

int back_to_main_do()
{
    choose_lab_mode=0;
    in_feel=0;
    lab_mode_used=0;
    in_main_menu=1;

}

int not_create()
{
    input_text_mode=0;
    info_name="";
}

int create()
{
    if (in_all_files(info_name) || info_name=="")
    {
        ///message
        return(0);
    }
    in_feel=1;
    in_main_menu=0;
    now_file_name=info_name;
    add_all_files(info_name);
    write(info_name);
    info_name="";
    input_text_mode=0;
}

void clear_feel()
{
    for (int i=1;i<feel_size;i++)
        for (int j=1;j<feel_size;j++)
        {
            object[i][j].f.tex=empty_;
            object[i][j].f.resize_(40);
            object[i][j].reb.clear();
            object[i][j].R=0;
            object[i][j].U=0;
            object[i][j].shade=0;
        }
}

int create_lab()
{
    in_feel=1;
    lab_mode_used=1;
    choose_lab_mode=0;
    in_main_menu=0;
    last_ans=0;
    info_name="lab_work";
    now_file_name=info_name;
    read(info_name);
    info_name="";
    clear_feel();
    input_text_mode=0;
    solve();
}

int choose_lab_select()
{
    choose_lab_mode=1;
}

int create_new_file()
{
    input_text_mode=1;
    input_ok.to_do=&create;
    input_bad.to_do=&not_create;
}

int load()
{
    if (!in_all_files(info_name) || info_name=="")
    {
        ///message
        return(0);
    }
    in_feel=1;
    in_main_menu=0;
    now_file_name=info_name;
    read(info_name);
    info_name="";
    input_text_mode=0;
    solve();
}

int load_old_file()
{
    input_text_mode=1;
    input_ok.to_do=&load;
    input_bad.to_do=&not_create;
}

int exit_()
{
    exit(0);
}

void main_menu_draw()
{
    main_menu_background.draw_state();
    if (choose_lab_mode)
    {
        choose_lab_draw();
        return;
    }



    new_file.draw_state();
    old_file.draw_state();
    lab.draw_state();
    photo.draw_state();
    exit_b.draw_state();

    if (input_text_mode)
        input_text_draw();
}


void main_menu_reaction(int button, int state)
{
    if (choose_lab_mode)
    {
        choose_lab_reaction(button,state);
        return;
    }

    if (input_text_mode)
    {
        input_text_reaction(button,state);
        return;
    }

    if (button==GLUT_LEFT_BUTTON && state==GLUT_DOWN)
    {
        if (new_file.f.in())
        {
            new_file.press_down();
            pressed_do=&new_file;
        } else
        if (old_file.f.in())
        {
            old_file.press_down();
            pressed_do=&old_file;
        } else
        if (lab.f.in())
        {
            lab.press_down();
            pressed_do=&lab;
        } else
        if (photo.f.in())
        {
            photo.press_down();
            pressed_do=&photo;
        } else
        if (exit_b.f.in())
        {
            exit_b.press_down();
            pressed_do=&exit_b;
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
