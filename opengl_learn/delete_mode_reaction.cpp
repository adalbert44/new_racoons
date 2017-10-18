#include "delete_mode_reaction.h"



void delete_mode_mouse_pressed(int button, int state)
{
        if (button==GLUT_LEFT_BUTTON && state==GLUT_DOWN)
    {
        if (delete_mode.f.in())
        {

            delete_mode.press_down();
            pressed=&delete_mode;
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

    if (button==GLUT_LEFT_BUTTON && state==GLUT_UP)
    {
        vector<Event> vec;
        to_del_reb.clear();

        for (int i1=1;i1<feel_size;i1++)
            for (int j1=1;j1<feel_size;j1++)
                for (int i2=1;i2<feel_size;i2++)
                    for (int j2=1;j2<feel_size;j2++)
                        if (choosen_reb[i1][j1][i2][j2])
                        {
                            choosen_reb[i1][j1][i2][j2]=0;
                            choosen_reb[i2][j2][i1][j1]=0;
                            del_reb({i1,j1},{i2,j2});
                            vec.pb(Event({i1,j1},{i2,j2},3));
                        }


        for (auto l:to_del_point)
        {
            int i=l.fir;
            int j=l.sec;


            object[i][j].f.tex=connection_point;
            Circle_element fir=object[i][j];
            object[i][j].f.tex=empty_;
            object[i][j].f.resize_(40);
            object[i][j].R=0.0;

            vector<pair<int,int> > r=object[i][j].reb;

            for(auto l:r)
            {
                del_reb(l,{i,j});
                vec.pb(Event(l,{i,j},3));
            }

            Circle_element sec=object[i][j];

            vec.pb(Event(fir,sec,{i,j}));


        }

        if (!vec.empty())
        {
            del_events();
            events.pb(vec);
            last_event++;
        }

        to_del_point.clear();
    }
}

bool intersect(int l1, int r1, int l2, int r2)
{
    if (l1>r1)
        swap(l1,r1);
    if (l2>r2)
        swap(l2,r2);
    return(max(l1,l2)<=min(r1,r2));
}

int area(pair<int,int> p1, pair<int,int> p2, pair<int,int> p3)
{
    return((p2.fir-p1.fir)*(p3.sec-p1.sec)-(p3.fir-p1.fir)*(p2.sec-p1.sec));
}


bool intersect(pair<int,int> p1, pair<int,int> p2, pair<int,int> p3, pair<int,int> p4)
{
    if (!intersect(p1.fir,p2.fir,p3.fir,p4.fir)) return(0);
    if (!intersect(p1.sec,p2.sec,p3.sec,p4.sec)) return(0);
    if (area(p1,p3,p4)==0) return(1);
    if (area(p2,p3,p4)==0) return(1);
    if (area(p1,p3,p2)==0) return(1);
    if (area(p1,p4,p2)==0) return(1);
    if ((area(p1,p3,p4)>0)==(area(p2,p3,p4)>0)) return(0);
    if ((area(p3,p1,p2)>0)==(area(p4,p1,p2)>0)) return(0);
    return(1);
}

bool can_delete(int i, int j)
{
    if (object[i][j].f.tex!=connection_point) return(0);
    for (auto l:object[i][j].reb)
    {
        if (object[l.fir][l.sec].f.tex!=connection_point && object[l.fir][l.sec].f.tex!=choosen_point_tex) return(0);
    }
    return(1);
}

void delete_mode_mouse_pressed_motion(double x1, double y1, double x2, double y2)
{
    for (int i=1;i<feel_size;i++)
        for (int j=1;j<feel_size;j++)
            if (can_delete(i,j) && object[i][j].f.in_circle())
            {
                object[i][j].f.tex=choosen_point_tex;
                to_del_point.pb({i,j});
            }

    if (x1==x2 && y1==y2) return;

    for (int i=1;i<feel_size;i++)
        for (int j=1;j<feel_size;j++)
            for (auto l:object[i][j].reb)
            {
                double xx1=((object[i][j].f.x1-startx)*scrol+(object[i][j].f.x2-startx)*scrol)/2.0;
                double yy1=((object[i][j].f.y1-starty)*scrol+(object[i][j].f.y2-starty)*scrol)/2.0;
                double xx2=((object[l.fir][l.sec].f.x1-startx)*scrol+(object[l.fir][l.sec].f.x2-startx)*scrol)/2.0;
                double yy2=((object[l.fir][l.sec].f.y1-starty)*scrol+(object[l.fir][l.sec].f.y2-starty)*scrol)/2.0;
                if (intersect({xx1,yy1},{xx2,yy2},{x1,y1},{x2,y2}) &&
                    (object[i][j].f.tex==connection_point || object[i][j].f.tex==choosen_point_tex) &&
                    (object[l.fir][l.sec].f.tex==connection_point || object[l.fir][l.sec].f.tex==choosen_point_tex))
                    {
                        choosen_reb[i][j][l.fir][l.sec]=1;
                        choosen_reb[l.fir][l.sec][i][j]=1;
                    }
            }
}
