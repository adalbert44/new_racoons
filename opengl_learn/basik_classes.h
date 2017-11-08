#ifndef BASIK_CLASSES_H_INCLUDED
#define BASIK_CLASSES_H_INCLUDED


    #include "includes.h"

    using namespace std;

    void setFont(void* font);
    string parse_to_string(double u);
    void drawstring(double x, double y, double z, string s);
    double dist_(double x1, double y1, double x2, double y2);
    double dist_(pair<double,double> p1,pair<double,double> p2);
    double sqr(double a);

    struct Figure
    {
    public:
        double x1,x2,y1,y2,alpha;
        GLuint tex;

        Figure();
        Figure(double x1_, double x2_, double y1_, double y2_, GLuint tex_, double alpha);
        Figure(double x1_, double x2_, double y1_, double y2_, double alpha);
        double dist();
        double centre_dist();
        bool in();
        bool in_circle();
        bool in_dinamic();

        void draw();
        void draw_state();
        void resize_(double siz);
    };

    struct Reb
    {
    public:
        int x1,y1,x2,y2;
        Reb(int x1_, int y1_, int x2_, int y2_);
    };



    struct Point
    {
    public:
        double x,y;
        Point()
        {
        }
        Point (double x_, double y_)
        {
            x=x_;
            y=y_;
        }
    };

    struct Circle_element
    {
    public:
        Figure f;
        vector<pair<int,int> > reb;
        double shade;
        long double R;
        long double U;
        Circle_element();
        Circle_element(double x, double y);
        Circle_element(Figure f_, long double R_, long double U_);
        void draw();
    };

    class Button
    {
    public:
        Figure f;
        vector<bool*> change;
        double shade=0;
        double light=0;
        bool used=0;
        Button();
        Button(Figure f_, vector<bool*> change);
        void draw_state();
        void press_down();
        void press_up();
        void watch();
    };


    class Button_do
    {
    public:
        Figure f;
        int (*to_do)();
        double shade=0;
        double light=0;

        Button_do();
        Button_do(Figure f_, int (*to_do_)());
        void draw_state();
        void press_down();
        void press_up();
        void watch();
    };

    class Color
    {
    public:
        int R,G,B;
        Color();
        Color(int r, int g, int b);
    };

struct pt {
	double x, y;
	pt(int x_, int y_);

	pt();
};

struct Element
{
    vector<pt> p;
    long double rad;
    long double R;
    pt minuss;
    pt pluss;
    string name="";

    Element();
};

struct prov
{
    int c1,c2;
    pt p1,p2;

    prov();
    prov(int c1_,int c2_, pt p1_, pt p2_);
};



    class Event
    {
    public:
        int type;
        pair<int,int> p1;
        pair<int,int> p2;
        Circle_element was;
        Circle_element become;
        Event();
        Event(pair<int,int> p1_, pair<int,int> p2_);
        Event(pair<int,int> p1_, pair<int,int> p2_, int type_);
        Event(Circle_element was_, Circle_element become_, pair<int,int> p1);
    };

    extern Circle_element object[30][30];
    extern std::vector<Figure> feel_background;
    extern Figure left_menu_background;
    extern Figure left_menu_vertical[9];
    extern Figure left_menu_horizontal[9];
    extern GLuint taken;
    extern Button line_mode;
    extern bool line_mode_used;
    extern Button point_mode;
    extern bool point_mode_used;
    extern Button move_mode;
    extern bool move_mode_used;
    extern Button* pressed;
    extern Button_do undo_button;
    extern Button_do redo_button;
    extern Button_do *pressed_do;
    extern Figure object_info;
    extern Button_do object_delete;
    extern Button_do object_rotate;
    extern Figure window_shade;
    extern bool taken_point;
    extern vector<pair<int,int> > taken_reb;
    extern Figure shade_button1,shade_button2;
    extern GLuint move_tex;
    extern Button delete_mode;
    extern bool delete_mode_used;
    extern vector<Reb> to_del_reb;
    extern vector<pair<int,int> > to_del_point;
    extern Figure input_info_background;
    extern Figure input_feel;
    extern Button_do input_ok;
    extern Button_do input_bad;
    extern double taken_R;
    extern vector<vector<Event> > events;
    extern long double power[30][30][30][30];
    extern Figure text_back_ground;
    extern bool choose_lab_mode;
    extern bool window_picture_used;
    extern vector<Figure> window_picture;
    extern GLuint choose_lab_mode_tex[16];
    extern GLuint window_light;

    extern long double start[30][30][30][30];
    extern long double len[30][30][30][30];


    extern GLuint key_close_horizontal;
    extern GLuint key_close_vertical;
    extern GLuint info_background;
    extern GLuint text_line;
    extern GLuint close_hor;
    extern GLuint close_ver;
    extern double real_WinWid,real_WinHei;
    extern long double potential[30][30];
    extern Button_do object_change_state;
    extern Button_do object_change_R;
    extern Button_do input_R_ok;

    extern Button potential_mode;
    extern bool potential_mode_used;

    extern Button U_ask_mode;
    extern bool U_ask_mode_used;
    extern GLuint choose_lab_tex[16];
    extern GLuint choose_labs_tex[16];
    extern Button_do choose_lab[16];
    extern vector<long double> lab_ans[16];
    extern bool input_R_used;

    extern bool in_main_menu;

    extern Figure main_menu_background;
    extern Button_do lab;
    extern Button_do exit_b;
    extern Button_do photo;
    extern Button_do new_file;
    extern Button_do old_file;
    extern Button_do statement_show;
    extern bool lab_mode_used;
    extern int choosen_lab;
    extern Button_do back_to_main;
    extern GLuint lab_tex;
    extern GLuint menu_background;
    extern GLuint exit_tex;
    extern GLuint photo_tex;
    extern GLuint new_file_tex;
    extern GLuint old_file_tex;
    extern string info_name;
    extern string now_file_name;
    extern Button_do answer_lab;
    extern int last_ans;
    extern vector<string> lab_ask[16];

    extern bool input_text_mode;
    extern Button_do save;
    extern string input_info_ask;
    extern string input_text_ask;

    extern long double mx_U;
    extern long double mx_R;
    extern long double mx_I;

    extern bool read_U;
    extern bool read_R;

#endif // BASIK_CLASSES_H_INCLUDED
