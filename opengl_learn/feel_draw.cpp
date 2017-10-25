#include "feel_draw.h"
#include "basik_classes.h"
#include "potential_mode.h"
#include "lab_mode.h"

const double pi=acos(-1);

double angle (pair<double,double> p1, pair<double,double> p2, pair<double,double> p3)
{
    ld c=dist_(p1,p2);
    ld b=dist_(p2,p3);
    ld a=dist_(p1,p3);
    return(acos((sqr(b)+sqr(c)-sqr(a))/(2.0*b*c)));
}

double dist_to_seg(double x1, double y1, int i1, int j1, int i2, int j2)
{
    double x2=((object[i1][j1].f.x1+object[i1][j1].f.x2)/2.0-startx)*scrol;
    double y2=((object[i1][j1].f.y1+object[i1][j1].f.y2)/2.0-starty)*scrol;
    double x3=((object[i2][j2].f.x1+object[i2][j2].f.x2)/2.0-startx)*scrol;
    double y3=((object[i2][j2].f.y1+object[i2][j2].f.y2)/2.0-starty)*scrol;

    if (angle({x1,y1},{x2,y2},{x3,y3})>pi/2.0) return(dist_(x1,y1,x2,y2));
    if (angle({x1,y1},{x3,y3},{x2,y2})>pi/2.0) return(dist_(x1,y1,x3,y3));

    ld a=y2-y3;
    ld b=x3-x2;
    ld c=-a*x2-b*y2;

    return(abs(a*x1+b*y1+c)/sqrt(sqr(a)+sqr(b)));
}

void draw_electron()
{
ld speed=5;

    ld mx_power=0.001;

    for (int i=1;i<feel_size;i++)
        for (int j=1;j<feel_size;j++)
            for (int i1=1;i1<feel_size;i1++)
                for (int j1=1;j1<feel_size;j1++)
                    if (power[i][j][i1][j1]>0.001)
                    {
                        if (power[i][j][i1][j1]>0.001 && power[i][j][i1][j1]<1e9)
                            mx_power=max(mx_power,power[i][j][i1][j1]);
                    }




    for (int i=1;i<feel_size;i++)
        for (int j=1;j<feel_size;j++)
            for (int i1=1;i1<feel_size;i1++)
                for (int j1=1;j1<feel_size;j1++)
                    if (power[i][j][i1][j1]>0.001)
                    {
                        len[i][j][i1][j1]=100-(100-20)*(power[i][j][i1][j1]/mx_power);
                    }

    for (int i=1;i<feel_size;i++)
        for (int j=1;j<feel_size;j++)
            for (int i1=1;i1<feel_size;i1++)
                for (int j1=1;j1<feel_size;j1++)
                    if (power[i][j][i1][j1]>0.001 && power[i][j][i1][j1]<1e9)
                    {
                        start[i][j][i1][j1]+=5;


                        if (start[i][j][i1][j1]>len[i][j][i1][j1])
                            start[i][j][i1][j1]-=len[i][j][i1][j1];
                    }
    for (int i=1;i<feel_size;i++)

        for (int j=1;j<feel_size;j++)
        {
            for (auto r:object[i][j].reb)
            {
                int i1=r.fir;
                int j1=r.sec;
                if (power[i][j][i1][j1]>0.001 && power[i][j][i1][j1]<1e9)
                {
                    ld now=start[i][j][i1][j1];

                    ld x1=(object[i][j].f.x1+object[i][j].f.x2)/2.0;
                    ld x2=(object[i1][j1].f.x1+object[i1][j1].f.x2)/2.0 ;
                    ld y1=(object[i][j].f.y1+object[i][j].f.y2)/2.0;
                    ld y2=(object[i1][j1].f.y1+object[i1][j1].f.y2)/2.0 ;

                    ld d=dist_(x1,y1,x2,y2);

                    while (now<=d)
                    {
                        ld X=x1+(x2-x1)*now/d;
                        ld Y=y1+(y2-y1)*now/d;

                        Figure electron=Figure(X-8,X+8,Y-8,Y+8,choosen_point_tex,1.0);
                        electron.draw();
                        now+=len[i][j][i1][j1];
                    }
                }
            }

        }
}

bool can_put(int i, int j)
{
    if ((object[i][j].f.x2-startx)*scrol<=left_menu_size) return(0);
    if (object[i][j].f.tex!=empty_) return(0);
    if (i-1!=0)
        if (object[i-1][j].f.tex!=empty_ && object[i-1][j].f.tex!=connection_point) return(0);
    if (i+1!=feel_size)
        if (object[i+1][j].f.tex!=empty_ && object[i+1][j].f.tex!=connection_point) return(0);
    if (j-1!=0)
        if (object[i][j-1].f.tex!=empty_ && object[i][j-1].f.tex!=connection_point) return(0);
    if (j+1!=feel_size)
        if (object[i][j+1].f.tex!=empty_ && object[i][j+1].f.tex!=connection_point) return(0);
    return(1);
}


void draw_feel()
{



    for (int i=0;i<int(feel_background.size());i++)
        feel_background[i].draw();

    double mn=100000;
    int imn=0;
    int jmn=0;

    for (int i=1;i<feel_size;i++)
        for (int j=1;j<feel_size;j++)
        {
            if (object[i][j].f.tex==empty_)
                object[i][j].f.alpha=0.12;
            if (object[i][j].f.centre_dist()<mn)
            {
                imn=i;
                jmn=j;
                mn=object[i][j].f.dist();
            }
        }
    if (can_put(imn,jmn) && mousex>left_menu_size)
        object[imn][jmn].f.alpha=0.5;

    draw_electron();

    for (int i=1;i<feel_size;i++)
        for (int j=1;j<feel_size;j++)
        {
            if ((object[i][j].f.tex==empty_ && (!can_put(i,j) || !(something_taken || point_mode_used || taken_point))) || object[i][j].f.tex==connection_point || object[i][j].f.tex==choosen_point_tex)
                continue;
            object[i][j].draw();
        }


    for (int i=1;i<feel_size;i++)
        for (int j=1;j<feel_size;j++)
        {
            if (object[i][j].f.tex==connection_point || object[i][j].f.tex==choosen_point_tex)
            {
                object[i][j].draw();
            }
            //drawstring((object[i][j].f.x1-startx)*scrol,(object[i][j].f.y1-starty)*scrol,1,parse_to_string(object[i][j].R));
        }


    if (something_taken)
    {
        Figure now=Figure(mousex-feel_seg_size*scrol/2.0,mousex+feel_seg_size*scrol/2.0,
                          mousey-feel_seg_size*scrol/2.0,mousey+feel_seg_size*scrol/2.0,taken,0.2);
        now.draw_state();
    }


    if (taken_point)
    {
            Figure now=Figure(mousex-10*scrol,mousex+10*scrol,
                          mousey-10*scrol,mousey+10*scrol,connection_point,0.2);
        now.draw_state();
    }

    if (mousex>left_menu_size && !something_taken && !taken_point && !line_mode_used && !delete_mode_used &&
        !point_mode_used && !object_menu_used && !input_info_mode && !U_ask_mode_used && !window_message)
        {
            pair<pair<int,int>,pair<int,int> > r={mp(0,0),mp(0,0)};
            for (int i=1;i<feel_size;i++)
                for (int j=1;j<feel_size;j++)
                    for (auto to:object[i][j].reb)
                    {
                        if (dist_to_seg(mousex,mousey,i,j,to.fir,to.sec)<10)
                            r={mp(i,j),to};
                    }
            if (r.fir.fir!=0)
            {
                text_back_ground=Figure(mousex,mousex+120,mousey-25,mousey,text_line,1.0);
                text_back_ground.draw_state();

                string to_draw;

                if (abs(power[r.fir.fir][r.fir.sec][r.sec.fir][r.sec.sec])!=inf)
                    to_draw=parse_to_string(abs(power[r.fir.fir][r.fir.sec][r.sec.fir][r.sec.sec])); else
                    to_draw="inf";

                drawstring(mousex+3,mousey-2,1.0,to_draw);
            }

        }

    if (potential_mode_used)
        potential_mode_draw();

    if (lab_mode_used)
        lab_mode_draw();

    back_to_main.watch();
    back_to_main.draw_state();
}

void draw_left_menu()
{
    left_menu_background.draw_state();
    for (int i=0;i<7;i++)
    {
        left_menu_horizontal[i].draw_state();
        left_menu_vertical[i].draw_state();
    }


    if (!point_mode_used && !line_mode_used && !move_mode_used && !delete_mode_used && !U_ask_mode_used && !potential_mode_used)
    {
        point_mode.watch();
        line_mode.watch();
        move_mode.watch();
        delete_mode.watch();
        undo_button.watch();
        redo_button.watch();
        U_ask_mode.watch();
        potential_mode.watch();
        save.watch();
    }


    point_mode.draw_state();
    line_mode.draw_state();
    move_mode.draw_state();
    delete_mode.draw_state();
    undo_button.draw_state();
    redo_button.draw_state();
    U_ask_mode.draw_state();
    potential_mode.draw_state();
    save.draw_state();
}
