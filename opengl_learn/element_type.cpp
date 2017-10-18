#include "element_type.h"

bool voltmetr(GLuint t)
{
    return(t==left_menu_horizontal[1].tex || t==left_menu_vertical[1].tex);
}

bool ampermetr(GLuint t)
{
    return(t==left_menu_horizontal[3].tex || t==left_menu_vertical[3].tex);
}

bool rezistor(GLuint t)
{
    return(t==left_menu_horizontal[0].tex || t==left_menu_vertical[0].tex);
}

bool energy(GLuint t)
{
    return(t==left_menu_horizontal[5].tex || t==left_menu_vertical[5].tex
           || t==left_menu_horizontal[6].tex || t==left_menu_vertical[6].tex);
}

bool key(GLuint t)
{
    return(t==left_menu_horizontal[2].tex || t==left_menu_vertical[2].tex
           || t==close_hor || t==close_ver);
}

bool reostat(GLuint t)
{
    return(t==left_menu_horizontal[4].tex || t==left_menu_vertical[4].tex);
}

bool open_key(GLuint t)
{
    return(t==left_menu_horizontal[2].tex || t==left_menu_vertical[2].tex);
}

bool close_key(GLuint t)
{
    return(t==close_hor || t==close_ver);
}

bool con_point(GLuint t)
{
    return(t==connection_point);
}
