#ifndef DELETE_MODE_REACTION_H_INCLUDED
#define DELETE_MODE_REACTION_H_INCLUDED

    #include "includes.h"
    #include "feel_reaction.h"

    void delete_mode_mouse_pressed(int button, int state);
    void delete_mode_mouse_pressed_motion(double x1, double y1, double x2, double y2);
    bool can_delete(int i, int j);



#endif // DELETE_MODE_REACTION_H_INCLUDED

