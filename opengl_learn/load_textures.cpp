#include "load_textures.h"

GLuint Load(std::string b)
{
    GLuint temp = ilLoadImage(b.data());
    glGenTextures(1, &temp);
    glBindTexture (GL_TEXTURE_2D, temp);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, ilGetInteger(IL_IMAGE_WIDTH), ilGetInteger(IL_IMAGE_HEIGHT), 0, ilGetInteger(IL_IMAGE_FORMAT), ilGetInteger(IL_IMAGE_TYPE), ilGetData());
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    return temp;
}

string parse(int u)
{
    string res="";
    while (u!=0)
    {
        res+=u%10+'0';
        u/=10;
    }
    reverse(res.begin(),res.end());
    return(res);
}

void load_all()
{
    feel_background_texture[0]=Load("textures/e1.jpg");
    feel_background_texture[1]=Load("textures/e2.jpg");
    empty_=Load("textures/white_circle.png");
    connection_point=Load("textures/black_circle.png");
    line_mode_tex=Load("textures/line_mode_tex.png");
    point_mode_tex=Load("textures/point_mode_tex.png");
    choosen_point_tex=Load("textures/blue_circle.png");
    left_menu_background_tex=Load("textures/left_menu_background.png");
    delete_mode_tex=Load("textures/delete_mode.png");


    left_menu_vertical[0].tex=Load("textures/left_menu_vertical_0.png");
    left_menu_vertical[1].tex=Load("textures/left_menu_vertical_1.png");
    left_menu_vertical[2].tex=Load("textures/left_menu_vertical_2.png");
    left_menu_vertical[3].tex=Load("textures/left_menu_vertical_3.png");
    left_menu_vertical[4].tex=Load("textures/left_menu_vertical_4.png");
    left_menu_vertical[5].tex=Load("textures/left_menu_vertical_5.png");
    left_menu_vertical[6].tex=Load("textures/left_menu_vertical_6.png");

    left_menu_horizontal[0].tex=Load("textures/left_menu_horizontal_0.png");
    left_menu_horizontal[1].tex=Load("textures/left_menu_horizontal_1.png");
    left_menu_horizontal[2].tex=Load("textures/left_menu_horizontal_2.png");
    left_menu_horizontal[3].tex=Load("textures/left_menu_horizontal_3.png");
    left_menu_horizontal[4].tex=Load("textures/left_menu_horizontal_4.png");
    left_menu_horizontal[5].tex=Load("textures/left_menu_horizontal_5.png");
    left_menu_horizontal[6].tex=Load("textures/left_menu_horizontal_6.png");
    shade_button_tex1=Load("textures/black_button1.png");
    shade_button_tex2=Load("textures/black_button2.png");
    window_shade.tex=Load("textures/black_square.png");
    undo_tex=Load("textures/undo.png");
    redo_tex=Load("textures/redo.png");
    move_tex=Load("textures/move_tex.png");
    rotate_tex=Load("textures/rotate.png");
    ok_tex=Load("textures/ok_button_tex.png");
    bad_tex=Load("textures/bad_button_tex.png");
    info_background=Load("textures/info_background.png");
    menu_background=Load("textures/menu_background.png");

    back_button_tex=Load("textures/back_button_tex.png");
    change_tex=Load("textures/change_tex.png");
    u_mode=Load("textures/u_mode.png");
    show_statements_tex=Load("textures/show_statements_tex.png");
    save_tex=Load("textures/save_tex.png");
    lab_background=Load("textures/lab_background.png");
    info_khm=Load("textures/info_khm.png");
    p_mode=Load("textures/p_mode.png");
    ok_lab_tex=Load("textures/ok_lab_tex.png");

    text_line=Load("textures/text_line.png");
    close_hor=Load("textures/key_hor.png");
    close_ver=Load("textures/key_ver.png");

    lab_tex=Load("textures/lab_tex.png");
    exit_tex=Load("textures/exit_tex.png");
    photo_tex=Load("textures/photo_tex.png");
    new_file_tex=Load("textures/new_file_tex.png");
    old_file_tex=Load("textures/old_file_tex.png");
    window_light=Load("textures/window_light.png");
    key_tex=Load("textures/key_tex.png");

    for (int i=0;i<16;i++)
    {
        string way="textures/labs/lab";
        way+=parse(i+1);
        way+=".png";
        choose_lab_tex[i]=Load(way);

        way="textures/labs/labs";
        way+=parse(i+1);
        way+=".png";
        choose_labs_tex[i]=Load(way);
    }



    light_exit=Load("textures/shade_exit_tex.png");
    light_line=Load("textures/line_shade_tex.png");
    light_lab=Load("textures/lab_shade.png");
    light_ok=Load("textures/white_circle.png");

    shade_lab=Load("textures/black_button4.png");
    shade_circle=Load("textures/black_circle.png");
}
