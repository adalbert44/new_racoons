#include "object_menu_draw.h"

bool use__[30][30];

bool badR__(long double u)
{
    return(u>1e8);
}

void dfs__(int a, int b)
{
    if (use__[a][b]) return;
    use__[a][b]=1;
    if (object[a][b].R>1e7) return;
    for (auto i:object[a][b].reb)
        if (!(badR__(power[a][b][i.fir][i.sec])) && !(object[i.fir][i.sec].R>1e7))
            dfs__(i.fir,i.sec);
}


void object_menu_draw()
{
    int i=choosen_object.fir;
    int j=choosen_object.sec;
    window_shade.alpha=0.1;
    window_shade.draw_state();

    object_info.draw_state();

    //cout<<object_info.tex<<'@'<<'\n';


    if (!(object[i][j].f.tex==choosen_point_tex || object[i][j].f.tex==connection_point && !can_delete(i,j)))
        object_delete.draw_state();

    if (object[i][j].f.tex!=choosen_point_tex && object[i][j].f.tex!=connection_point)
        object_rotate.draw_state();

    if (reostat(object[i][j].f.tex))
    {
        string to_draw="R=";
        to_draw+=parse_to_string(object[i][j].R);
        drawstring(object_info.x1+20,(object_info.y2+object_info.y1)/2.0+10,1.0,to_draw);
        object_change_R.draw_state();
    }

    if (key(object[i][j].f.tex))
    {
        string to_draw="state: ";
        if (open_key(object[i][j].f.tex))
            to_draw+="unconnected"; else
            to_draw+="connected";
        drawstring(object_info.x1+15,(object_info.y2+object_info.y1)/2.0+10,1.0,to_draw);
        object_change_state.draw_state();
    }

    if (rezistor(object[i][j].f.tex))
    {
        string to_draw="R=";
        to_draw+=parse_to_string(object[i][j].R);
        drawstring(object_info.x1+20,(object_info.y2+object_info.y1)/2.0+10,1.0,to_draw);
    }

    if (ampermetr(object[i][j].f.tex) || con_point(object[i][j].f.tex))
    {
        ld I=0;
        for (auto to: object[i][j].reb)
        {
            I+=max(power[i][j][to.fir][to.sec],ld(0));
            I=min(I,ld(inf));
        }


        string to_draw="I=";

        if (I<inf)
            to_draw+=parse_to_string(I); else
            to_draw+="inf";
        drawstring(object_info.x1+20,(object_info.y2+object_info.y1)/2.0+10,1.0,to_draw);
    }

    if (voltmetr(object[i][j].f.tex))
    {
        ld U=0;
        pair<int,int> to=object[i][j].reb[0];
        U+=potential[to.fir][to.sec];

        for (int i=1;i<feel_size;i++)
            for (int j=1;j<feel_size;j++)
            use__[i][j]=0;
        dfs__(to.fir,to.sec);

        to=object[i][j].reb[1];
        U-=potential[to.fir][to.sec];
        string to_draw="U=";


        if (potential[to.fir][to.sec]!=inf && use__[to.fir][to.sec])
            to_draw+=parse_to_string(U); else
            to_draw+="inf";
        drawstring(object_info.x1+20,(object_info.y2+object_info.y1)/2.0+10,1.0,to_draw);
    }

    if (energy(object[i][j].f.tex))
    {
        string to_draw="U=";
        to_draw+=parse_to_string(object[i][j].R);
        drawstring(object_info.x1+20,(object_info.y2+object_info.y1)/2.0+10,1.0,to_draw);
    }

    if(input_R_used)
        input_info_R_draw();
}


