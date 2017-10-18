#include "potential_mode.h"

void potential_mode_reaction(int button, int state)
{
    if (button==GLUT_LEFT_BUTTON && state==GLUT_DOWN)
    {
        if (potential_mode.f.in())
        {

            potential_mode.press_down();
            pressed=&potential_mode;
        }
    }


    if (button==GLUT_LEFT_BUTTON && state==GLUT_UP && pressed!=NULL)
    {
        if ((*pressed).f.in())
        {
            (*pressed).press_up();
            pressed=NULL;
        } else
        {
            if ((*pressed).used) (*pressed).shade=0.16; else
                (*pressed).shade=0.0;
            pressed=NULL;
        }
    }
}

void potential_mode_draw()
{
    ld mn=1e9;
    ld mx=-1e9;
    for (int i=1;i<feel_size;i++)
        for (int j=1;j<feel_size;j++)
        if (abs(potential[i][j])<1e8 && object[i][j].f.tex!=empty_)
        {
            mn=min(mn,potential[i][j]);
            mx=max(mx,potential[i][j]);
        }

    ld mxcol=1.0;
    ld mncol=0.3;

    for (int i=1;i<feel_size;i++)
        for (int j=1;j<feel_size;j++)
        if (object[i][j].f.tex!=empty_ && abs(potential[i][j])<1e8 && !energy(object[i][j].f.tex))
        {
            Figure draw=object[i][j].f;
            draw.tex=choosen_point_tex;
            draw.resize_(50);
            if (abs(mn-mx)<1e-2)
            {
                draw.alpha=(mxcol+mncol)/2.0;
            } else
            {
                draw.alpha=mncol+(mxcol-mncol)*((potential[i][j]-mn)/(mx-mn));
            }
            draw.draw();
        }
}
