#include "input_info.h"

void input_info_draw()
{
    window_shade.alpha=0.1;
    window_shade.draw_state();
    input_info_background.draw_state();
    input_feel.draw_state();
    input_ok.draw_state();
    input_bad.draw_state();

    drawstring(input_feel.x1,input_feel.y2,1.0,info_zn);
}

void input_info_R_draw()
{
    window_shade.alpha=0.1;
    window_shade.draw_state();
    input_info_background.draw_state();
    input_feel.draw_state();
    input_R_ok.draw_state();
    input_bad.draw_state();

    drawstring(input_feel.x1,input_feel.y2,1.0,info_zn);
}

double parse_to_double(string st)
{
    double u=0;
    bool ch=0;
    double add=1;
    for (int i=0;i<st.size();i++)
        if (st[i]=='.') ch=1; else
        {
            if (!ch)
            {
                u*=10.0;
                u+=st[i]-'0';
            } else
            {
                add/=10.0;
                u+=add*(st[i]-'0');
            }
        }
    return(u);
}

int change_R()
{
    vector<Event> vec;
    Circle_element fir=object[info_i][info_j];

    object[info_i][info_j].R=parse_to_double(info_zn);
    info_zn="0";

    Circle_element sec=object[info_i][info_j];

    vec.pb(Event(fir,sec,mp(info_i,info_j)));
    del_events();
    events.pb(vec);
    last_event++;
    input_R_used=0;
}

int input_ok_do()
{
    taken_R=parse_to_double(info_zn);
    info_zn="0";
    put_element(info_i,info_j);
    input_info_mode=0;
}

int check_anses()
{
    ld now=parse_to_double(info_zn);
    if (abs(now-lab_ans[choosen_lab][last_ans])<1e-4)
    {
        last_ans++;
        last_ans%=lab_ans[choosen_lab].size();
        window_message_write="TRUE";
        window_message=1;
    } else
    {
        window_message_write="FALSE";
        window_message=1;
    }
    info_zn="0";
    input_info_mode=0;
}

int input_bad_do()
{
    input_info_mode=0;
    info_zn="0";
}

int get(string st)
{
    int cnt=0;
    for (int i=0;i<st.size();i++)
        if (st[i]!='.') cnt++;
    return(cnt);
}

void input_keyboard(unsigned char c)
{
    if (c>='0' && c<='9') info_zn+=c;

    if (c=='.')
    {
        bool ch=0;
        for (auto i:info_zn)
            if (i=='.') ch=1;
        if (info_zn.size()!=0 && !ch)
        {
            info_zn+='.';
        }
    }

    if (get(info_zn)>6)
        info_zn.pop_back();
    reverse(info_zn.begin(),info_zn.end());
    if (info_zn.size()>=2)
    {
        int l=info_zn.size();
        while (info_zn[l-1]=='0' && info_zn[l-2]=='0')
        {
            info_zn.pop_back();
            l=info_zn.size();
            if (info_zn.size()<2) break;
        }

        if (info_zn.size()>=2 && info_zn.back()=='0')
            if (info_zn[info_zn.size()-2]<='9' && info_zn[info_zn.size()-2]>='0')
            info_zn.pop_back();
    }
    reverse(info_zn.begin(),info_zn.end());

}

void input_skeyboard(unsigned char c)
{
    if (c==GLUT_KEY_LEFT)
        if (!info_zn.empty())
        info_zn.pop_back();
}

void input_info_mouse_pressed(int button, int state)
{
    if (button==GLUT_LEFT_BUTTON && state==GLUT_DOWN)
    {
        if (input_ok.f.in())
        {
            input_ok.press_down();
            pressed_do=&input_ok;
        }

        if (input_bad.f.in())
        {
            input_bad.press_down();
            pressed_do=&input_bad;
        }
    }

    if (button==GLUT_LEFT_BUTTON && state==GLUT_UP)
    {

        if (pressed_do!=NULL)
        {
            (*pressed_do).press_up();
            pressed_do=NULL;
        }
    }
}

void input_R_mouse_pressed(int button, int state)
{
    if (button==GLUT_LEFT_BUTTON && state==GLUT_DOWN)
    {
        if (input_R_ok.f.in())
        {
            input_R_ok.press_down();
            pressed_do=&input_R_ok;
        }

        if (input_bad.f.in())
        {
            input_bad.press_down();
            pressed_do=&input_bad;
        }
    }

    if (button==GLUT_LEFT_BUTTON && state==GLUT_UP)
    {

        if (pressed_do!=NULL)
        {
            (*pressed_do).press_up();
            pressed_do=NULL;
        }
    }
}
