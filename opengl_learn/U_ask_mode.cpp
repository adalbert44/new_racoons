#include "U_ask_mode.h"
#include "feel_draw.h"
#include "get_power.h"

bool use_[30][30];

void dfs_(int a, int b)
{

    if (use_[a][b]) return;
    use_[a][b]=1;
    if (object[a][b].R>1e7) return;
    for (auto i:object[a][b].reb)
        if (!(bad_R(power[a][b][i.fir][i.sec])) && !(object[i.fir][i.sec].R>1e7))
            dfs_(i.fir,i.sec);
}

void write_res()
{
    vector<long double> vec;
    for (int i=1;i<feel_size;i++)
        for (int j=1;j<feel_size;j++)
            if (object[i][j].f.tex==choosen_point_tex)
            {
                object[i][j].f.tex=connection_point;
                vec.pb(potential[i][j]);
            }
    if (vec.size()==2)
    {
        window_message=1;
        window_message_write="U=";
        window_message_write+=parse_to_string(abs(vec[0]-vec[1]));
    }
}

void try_add(int x, int y)
{
    if (object[x][y].f.tex!=connection_point) return;
    int ii=-1;
    int jj=-1;
    int cnt=0;
    for (int i=1;i<feel_size;i++)
        for (int j=1;j<feel_size;j++)
        {
            use_[i][j]=0;
            if (object[i][j].f.tex==choosen_point_tex)
        {

            ii=i;
            jj=j;
            cnt++;
        }
        }


    if (ii==-1)
    {
        object[x][y].f.tex=choosen_point_tex;
    } else
    if (cnt==1)
    {
        dfs_(ii,jj);
        if (use_[x][y])
            object[x][y].f.tex=choosen_point_tex;
    }
}

const double pi=acos(-1);

double dist_to_seg(double x1, double y1, double x2, double y2, double x3, double y3)
{

    if (angle({x1,y1},{x2,y2},{x3,y3})>pi/2.0) return(dist_(x1,y1,x2,y2));
    if (angle({x1,y1},{x3,y3},{x2,y2})>pi/2.0) return(dist_(x1,y1,x3,y3));

    ld a=y2-y3;
    ld b=x3-x2;
    ld c=-a*x2-b*y2;

    return(abs(a*x1+b*y1+c)/sqrt(sqr(a)+sqr(b)));
}

void U_ask_mouse_pressed_motion(double x1, double y1, double x2, double y2)
{
    for (int i=1;i<feel_size;i++)
        for (int j=1;j<feel_size;j++)
        {
            double x=((object[i][j].f.x1+object[i][j].f.x2)/2.0-startx)*scrol;
            double y=((object[i][j].f.y1+object[i][j].f.y2)/2.0-starty)*scrol;
            if (dist_to_seg(x,y,x1,y1,x2,y2)<20)
            {
                try_add(i,j);
            }
        }
}

void U_ask_mouse_pressed(int button, int state)
{
    if (button==GLUT_LEFT_BUTTON && state==GLUT_UP)
    {
        write_res();
    }

    if (button==GLUT_LEFT_BUTTON && state==GLUT_DOWN)
    {
        if (U_ask_mode.f.in())
        {

            U_ask_mode.press_down();
            pressed=&U_ask_mode;
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
