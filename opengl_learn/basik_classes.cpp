#include "basik_classes.h"
#include "object_menu_reaction.h"


double WinWid=0.0;
double WinHei=0.0;
void *currentfont;

double speed_scrol=1.05;
double speed_move=20.0;
double taken_R;

double ky;
double kx;

long double mx_U=1000000;
long double mx_R=1000000;
long double mx_I=700;

bool read_U=0;
bool read_R=0;
//GLuint key_close_horizontal=Load("textures/key_hor.png");
//GLuint key_close_vertical=Load("textures/key_ver.png");

string input_info_ask;
string input_text_ask;
vector<ld> lab_ans[16];
vector<string> lab_ask[16];
GLuint rotate_tex;
GLuint ok_tex;
GLuint bad_tex;
bool window_message;
bool in_main_menu=1;
bool window_picture_used;
bool choose_lab_mode;
int choosen_lab;
int last_ans;
vector<Figure> window_picture;
string window_message_write;
Figure main_menu_background;
Button_do lab;
Button_do exit_h;
Button_do photo;
Button_do new_file;
Button_do old_file;
Button_do save;
Button_do back_to_main;
Button_do answer_lab;

GLuint menu_background;
GLuint back_button_tex;
GLuint change_tex;
GLuint u_mode;
GLuint show_statements_tex;
GLuint save_tex;
GLuint ok_lab_tex;
GLuint lab_background;
GLuint info_khm;
GLuint p_mode;

GLuint lab_tex;
GLuint exit_tex;
GLuint photo_tex;
GLuint new_file_tex;
GLuint old_file_tex;
GLuint choose_lab_tex[16];
GLuint choose_labs_tex[16];


ld start[30][30][30][30];
ld len[30][30][30][30];

GLuint info_background;
int info_i,info_j;
GLuint undo_tex;
GLuint text_line;
GLuint close_hor;
GLuint close_ver;
GLuint redo_tex;
GLuint window_light;
Figure window_shade;
Figure object_info;
Figure input_info_background;
Figure input_feel;
Button_do exit_b;
Button_do object_delete;
Button_do object_rotate;
Button_do input_ok;
Button_do input_R_ok;
Button_do input_bad;
Button_do choose_lab[16];
Button U_ask_mode;
bool U_ask_mode_used;
bool input_R_used;

pair<int,int> pred_pos={-1,-1};
vector<Reb> to_del_reb;
vector<pair<int,int> > to_del_point;
string info_zn="0";
string info_name="";
string now_file_name="";
ld power[30][30][30][30];
ld potential[30][30];
GLuint move_tex;
GLuint delete_mode_tex;
Figure shade_button1,shade_button2;
Figure text_back_ground;
GLuint shade_button_tex1,shade_button_tex2;
double feel_seg_size=100;
int feel_size=30;
double real_WinWid,real_WinHei;
double scrol=1.0;
double mousex=0.0, mousey=0.0;
bool in_feel=0;
bool something_taken=0;
bool direction=0;
GLuint taken;
GLuint put;
double left_menu_size=350;
double startx=-left_menu_size,starty=0;
GLuint feel_background_texture[2];
GLuint empty_;
GLuint connection_point;
vector<Figure> feel_background;
Figure left_menu_background;
Circle_element object[30][30];
GLuint left_menu_background_tex;
GLuint line_mode_tex;
GLuint point_mode_tex;
Button_do *pressed_do=NULL;
bool taken_point=0;
vector<pair<int,int> > taken_reb;
bool choosen_reb[31][31][31][31];

Figure left_menu_vertical[9];
Figure left_menu_horizontal[9];

vector<pair<int,int> > choosen_point;
GLuint choosen_point_tex;
vector<vector<Event> > events;
int last_event=-1;

Button line_mode;
Button delete_mode;
Button move_mode;
Button point_mode;
Button potential_mode;
bool potential_mode_used=0;
bool line_mode_used=0;
bool point_mode_used=0;
bool move_mode_used=0;
bool delete_mode_used=0;
bool input_info_mode=0;
bool input_text_mode=0;
bool lab_mode_used=0;
Button_do undo_button;
Button_do redo_button;
Button* pressed=NULL;
pair<int,int> choosen_object={-1,-1};
bool object_menu_used=0;
Button_do object_change_state;
Button_do object_change_R;
Button_do statement_show;
string parse_to_string(double u)
{

    u=abs(u);
    if (u>=1e9)
        return("inf");
    u+=0.0001;
    string res="";
    int uu=int(u);
    while (uu!=0)
    {
        res+=uu%10+'0';
        uu/=10;
    }
    u-=int(u);
    if (res.empty()) res+='0';
    reverse(res.begin(),res.end());
    res+='.';
    for (int i=1;i<=3;i++)
    {
        u*=10;
        res+=int(u)+'0';
        u-=int(u);
    }
    if (res.back()=='.') res.pop_back();
    return(res);
}

double sqr(double a)
{
    return(a*a);
}


double dist_(double x1, double y1, double x2, double y2)
{
    return(sqrt(sqr(x1-x2)+sqr(y1-y2)));
}

double dist_(pair<double,double> p1, pair<double,double> p2)
{
    return(sqrt(sqr(p1.fir-p2.fir)+sqr(p1.sec-p2.sec)));
}

void setFont(void *font)
{
    currentfont=font;                      // Set the currentfont to the font
}

void drawstring(double x,double y,double z,string s)
{


    setFont(GLUT_BITMAP_TIMES_ROMAN_24);
    glColor3f(1.0,1.0,1.0);

    char *c;
    glRasterPos3f(x,y,z);

    for (int i=0;i<s.size();i++)
    {
        glColor3f(0.0,0.0,0.0);
        glutBitmapCharacter(currentfont,s[i]);
    }
    glPopMatrix();
}

Figure :: Figure()
{

}

Figure :: Figure(double x1_, double x2_, double y1_, double y2_, GLuint tex_, double alpha_)
{
    x1=x1_;
    x2=x2_;
    y1=y1_;
    y2=y2_;
    tex=tex_;
    alpha=alpha_;
}

void Figure :: draw()
{

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, tex);
        glPushMatrix();

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glColor4f(1, 1, 1, alpha);

        glBegin(GL_QUADS);
            glTexCoord2f(0, 0); glVertex2f((x1-startx)*scrol, (y1-starty)*scrol);
            glTexCoord2f(1, 0); glVertex2f((x2-startx)*scrol, (y1-starty)*scrol);
            glTexCoord2f(1, 1); glVertex2f((x2-startx)*scrol, (y2-starty)*scrol);
            glTexCoord2f(0, 1); glVertex2f((x1-startx)*scrol, (y2-starty)*scrol);
        glEnd();

        glDisable(GL_BLEND);

        glPopMatrix();
    glDisable(GL_TEXTURE_2D);
}

void Figure :: draw_state()
{

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, tex);
        glPushMatrix();

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glColor4f(1, 1, 1, alpha);

        glBegin(GL_QUADS);
            glTexCoord2f(0, 0); glVertex2f(x1, y1);
            glTexCoord2f(1, 0); glVertex2f(x2, y1);
            glTexCoord2f(1, 1); glVertex2f(x2, y2);
            glTexCoord2f(0, 1); glVertex2f(x1, y2);
        glEnd();

        glDisable(GL_BLEND);

        glPopMatrix();
    glDisable(GL_TEXTURE_2D);
}

double Figure :: dist()
{
    double x1_=(x1-startx)*scrol;
    double x2_=(x2-startx)*scrol;
    double y1_=(y1-starty)*scrol;
    double y2_=(y2-starty)*scrol;

    double res=100000;

    res=min(res,dist_(x1_,y1_,mousex,mousey));
    res=min(res,dist_(x1_,y2_,mousex,mousey));
    res=min(res,dist_(x2_,y1_,mousex,mousey));
    res=min(res,dist_(x2_,y2_,mousex,mousey));
    return(res);
}

double Figure :: centre_dist()
{
    double x1_=(x1-startx)*scrol;
    double x2_=(x2-startx)*scrol;
    double y1_=(y1-starty)*scrol;
    double y2_=(y2-starty)*scrol;

    double x=(x1_+x2_)/2.0;
    double y=(y1_+y2_)/2.0;

    return(dist_(x,y,mousex,mousey));
}

bool Figure :: in()
{
    return(x1<=mousex && mousex<=x2 && y1<=mousey && mousey<=y2);
}

bool Figure :: in_dinamic()
{
    return((x1-startx)*scrol<=mousex && mousex<=(x2-startx)*scrol && (y1-starty)*scrol<=mousey && mousey<=(y2-starty)*scrol);

}



bool Figure :: in_circle()
{
    double x1_=(x1-startx)*scrol;
    double x2_=(x2-startx)*scrol;
    double y1_=(y1-starty)*scrol;
    double y2_=(y2-starty)*scrol;

    return(dist_((x2_+x1_)/double(2.0),(y2_+y1_)/double(2.0),double(mousex),double(mousey))<=(x2_-x1_)/2.0+10.0);
}

void Figure :: resize_(double len)
{
    double sx=(x1+x2)/2.0;
    double sy=(y1+y2)/2.0;

    x1=sx-len/2.0;
    x2=sx+len/2.0;
    y1=sy-len/2.0;
    y2=sy+len/2.0;
}

Circle_element :: Circle_element()
{
    shade=0.0;
    R=0;
    U=0;
}

Circle_element :: Circle_element(double x, double y)
{
    f=Figure(x-20.0,x+20.0,y-20.0, y+20.0, empty_, 0.3);
    R=0.0;
    U=0.0;
    shade=0.0;
}

Circle_element :: Circle_element(Figure f_, long double R_, long double U_)
{
    f=f_;
    R=R_;
    U=U_;
    shade=0.0;
}

void Circle_element :: draw()
{
    glLineWidth(5);

    for (int i=0;i<reb.size();i++)
    {

        int pi=((f.x1+f.x2)/2.0)/feel_seg_size+0.00001;
        int pj=((f.y1+f.y2)/2.0)/feel_seg_size+0.00001;
        double green=0.0;
        if (choosen_reb[pi][pj][reb[i].first][reb[i].second] || choosen_reb[reb[i].first][reb[i].second][pi][pj])
            green=1.0;
        glColor4f(0, green, 0, 1);
        Figure now=object[reb[i].first][reb[i].second].f;
        double x=(now.x1+now.x2)/2.0;
        double y=(now.y1+now.y2)/2.0;
        glBegin(GL_LINES);
            glVertex2f(((f.x1-startx)*scrol+(f.x2-startx)*scrol)/2.0,((f.y2-starty)*scrol+(f.y1-starty)*scrol)/2.0);
            glVertex2f(((x-startx)*scrol+((f.x1-startx)*scrol+(f.x2-startx)*scrol)/2.0)/2.0,((y-starty)*scrol+((f.y2-starty)*scrol+(f.y1-starty)*scrol)/2.0)/2.0);

        glEnd();
    }
    f.draw();

    glPushMatrix();

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    if (get_dir(f.tex))
    {
        shade_button1.x1=f.x1;
        shade_button1.x2=f.x2;
        shade_button1.y1=f.y1;
        shade_button1.y2=f.y2;

        shade_button1.alpha=shade*2.0;

        shade_button1.draw();
    } else
    {
        shade_button2.x1=f.x1;
        shade_button2.x2=f.x2;
        shade_button2.y1=f.y1;
        shade_button2.y2=f.y2;

        shade_button2.alpha=shade*2.0;
        shade_button2.draw();
    }



}

Button :: Button()
{

}

Button :: Button(Figure f_, vector<bool*> change_)
{
    f=f_;
    change=change_;
}

void Button :: draw_state()
{
     f.draw_state();


    Figure fig=Figure(f.x1,f.x2,f.y1,f.y2,window_shade.tex,shade);
    fig.draw_state();

    fig.tex=window_light;
    fig.alpha=light;
    fig.draw_state();
}

void Button :: press_down()
{
    shade=0.3;
}

void Button :: press_up()
{

    if (used)
        shade=0.0; else
        shade=0.16;
    used=!used;
    for (int i=0;i<change.size();i++)
        (*change[i])=!(*change[i]);

}

void Button :: watch()
{
    if (pressed!=NULL || pressed_do!=NULL)
    {
        light=0.0;
        return;
    }

    if (f.in() && shade<0.0001)
        light=0.15; else
        light=0.0;
}

Button_do :: Button_do()
{
    light=0;
}

Button_do :: Button_do(Figure f_, int (*to_do_)())
{
    light=0;
    f=f_;
    to_do=to_do_;
}

void Button_do :: draw_state()
{
    f.draw_state();


    Figure fig=Figure(f.x1,f.x2,f.y1,f.y2,window_shade.tex,shade);
    fig.draw_state();

    fig.tex=window_light;
    fig.alpha=light;
    fig.draw_state();

}

void Button_do :: watch()
{

    if (pressed!=NULL || pressed_do!=NULL)
    {
        light=0.0;
        return;
    }

    if (f.in() && shade<0.0001)
        light=0.15; else
        light=0.0;
}

void Button_do :: press_down()
{
    shade=0.3;
}

void Button_do :: press_up()
{
    shade=0.0;
    if (f.in())
        (*to_do)();
}


Event :: Event()
{

}

Event :: Event(pair<int,int> p1_, pair<int,int> p2_)
{
    type=1;
    p1=p1_;
    p2=p2_;
}

Event :: Event(pair<int,int> p1_, pair<int,int> p2_, int type_)
{
    type=type_;
    p1=p1_;
    p2=p2_;
}

Event :: Event(Circle_element was_, Circle_element become_, pair<int,int> p_)
{
    type=2;
    was=was_;
    become=become_;
    p1=p_;
}

Reb :: Reb (int x1_, int y1_, int x2_, int y2_)
{
    x1=x1_;
    y1=y1_;
    x2=x2_;
    y2=y2_;
}

Color :: Color()
{

}

Color :: Color(int r, int g, int b)
{
    R=r;
    G=g;
    B=b;
}

prov :: prov(int c1_,int c2_, pt p1_, pt p2_)
{
    c1=c1_;
    c2=c2_;
    p1=p1_;
    p2=p2_;
}

prov :: prov()
{

}

Element :: Element()
{
    R=0;
}

pt :: pt(int x_, int y_)
{
    x=x_;
    y=y_;
}

pt :: pt()
{

}

