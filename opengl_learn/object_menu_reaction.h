#ifndef OBJECT_MENU_REACTION_H_INCLUDED
#define OBJECT_MENU_REACTION_H_INCLUDED

    #include "includes.h"
    #include "delete_mode_reaction.h"
    #include "element_type.h"
    #include "input_info.h"

    int object_delete_func();
    int object_rotate_func();
    int object_change_state_func();
    int object_change_R_func();
    bool get_dir(GLuint tex);
    void object_menu_mouse_pressed(int button, int state);
    void object_menu_keyboard(unsigned char c, int x, int y);

#endif // OBJECT_MENU_REACTION_H_INCLUDED



