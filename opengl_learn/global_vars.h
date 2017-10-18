#ifndef GLOBAL_VARS_H_INCLUDED
#define GLOBAL_VARS_H_INCLUDED

    #include "includes.h"
    #include "basik_classes.h"
    //#include <bits/stdc++.h>

    using namespace std;

    extern double WinWid;
    extern double WinHei;











    extern double ky;
    extern double kx;

    extern double speed_scrol;
    extern double speed_move;
    extern double startx;
    extern double starty;
    extern double feel_seg_size;
    extern int feel_size;
    extern double scrol;
    extern double mousex;
    extern double mousey;
    extern GLuint ok_tex;
    extern GLuint bad_tex;

    extern int last_event;
    extern GLuint feel_background_texture[2];
    extern GLuint empty_;
    extern double left_menu_size;
    extern bool in_feel;
    extern bool something_taken;
    extern GLuint put;
    extern bool direction;
    extern GLuint connection_point;
    extern vector<pair<int,int> > choosen_point;
    extern GLuint choosen_point_tex;
    extern GLuint left_menu_background_tex;
    extern GLuint line_mode_tex;
    extern GLuint point_mode_tex;
    extern pair<int,int> choosen_object;
    extern bool object_menu_used;
    extern pair<int,int> pred_pos;
    extern GLuint undo_tex;
    extern GLuint redo_tex;
    extern bool choosen_reb[31][31][31][31];
    extern GLuint shade_button_tex1,shade_button_tex2;
    extern void* currentfont;
    extern bool input_info_mode;
    extern int info_i,info_j;
    extern string info_zn;
    extern GLuint delete_mode_tex;
    extern GLuint rotate_tex;

    extern bool window_message;
    extern string window_message_write;



#endif // GLOBAL_VARS_H_INCLUDED
