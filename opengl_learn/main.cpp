#include "includes.h"
#include "load_textures.h"
#include "basik_classes.h"
#include "feel_draw.h"
#include "feel_reaction.h"
#include "undo_redo.h"
#include "object_menu_draw.h"
#include "object_menu_reaction.h"
#include "delete_mode_reaction.h"
#include "input_info.h"
#include "read_write.h"
#include "U_ask_mode.h"
#include "window_message.h"
#include "potential_mode.h"
#include "main_menu.h"
#include "input_text.h"
#include "lab_mode.h"
#include "scan.h"

void Draw()
{

    glClear(GL_COLOR_BUFFER_BIT);
    if (in_feel)
    {
        draw_feel();
        draw_left_menu();
        if (object_menu_used)
            object_menu_draw();
        if (input_info_mode)
            input_info_draw();
        if (window_message)
            window_message_draw();
    } else
    if (in_main_menu)
    {
        main_menu_draw();
    }

    glutSwapBuffers();
}


void keyboard(unsigned char c, int x, int y)
{
    if (input_text_mode)
    {
        input_text_keyboard(c);
        return;
    }
    if (object_menu_used)
    {
        object_menu_keyboard(c,x,y);
    }
    if (c=='q') exit(0);
    if (input_info_mode)
    {
        input_keyboard(c);
    }


    if (object_menu_used) return;
    switch (c)
    {
        case 'r':

            undo();
            break;
        case 't':
            redo();
            break;
        case 'q':
            exit(0);
            break;
        case '+':
            if ((-startx)*min(double(2.0),scrol*speed_scrol)>left_menu_size)
            {
                startx=-left_menu_size/min(double(2.0),scrol*speed_scrol);
                startx=min(startx,feel_seg_size*feel_size-WinWid/scrol);
            }
            if ((-startx)*scrol<left_menu_size)
            {
                scrol*=speed_scrol;
                scrol=min(scrol,double(2.0));
            }
            break;
        case '-':
            if ((feel_size*feel_seg_size-startx)*scrol/speed_scrol>WinWid && (feel_size*feel_seg_size-starty)*scrol/speed_scrol>WinHei)
            {
                scrol/=speed_scrol;
            } else
            {
                if ((feel_size*feel_seg_size-startx)*scrol/speed_scrol<=WinWid)
                {
                    startx=feel_size*feel_seg_size-(WinWid/(scrol/speed_scrol))-0.0001;
                    startx=max(double(-left_menu_size)/scrol,startx);
                }

                if ((feel_size*feel_seg_size-starty)*scrol/speed_scrol<=WinHei)
                {
                    starty=feel_size*feel_seg_size-(WinHei/(scrol/speed_scrol))-0.0001;
                    starty=max(double(0.0),starty);
                }

                if ((feel_size*feel_seg_size-startx)*scrol/speed_scrol>=WinWid && (feel_size*feel_seg_size-starty)*scrol/speed_scrol>=WinHei)
                {
                    scrol/=speed_scrol;
                }
            }
            break;
        default:
            break;
    }
}

void skeyboard(int c, int x, int y)
{
    if (input_text_mode)
    {
        input_text_skeyboard(c);
        return;
    }
    if (input_info_mode)
    {
        input_skeyboard(c);
    }
    if (input_info_mode) return;
    if (object_menu_used) return;
    switch (c)
    {
        case GLUT_KEY_RIGHT:
            startx+=speed_move;
            startx=min(startx,feel_seg_size*feel_size-WinWid/scrol);
            break;

        case GLUT_KEY_LEFT:
            startx-=speed_move;
            startx=max(double(-left_menu_size)/scrol,startx);
            break;
        case GLUT_KEY_DOWN:
            starty+=speed_move;
            starty=min(starty,feel_seg_size*feel_size-WinHei/scrol);
            break;
        case GLUT_KEY_UP:
            starty-=speed_move;
            starty=max(double(0.0),starty);
            break;
        default:
            break;
    }

}

void main_menu_create()
{
    main_menu_background=Figure(0,WinWid,0,WinHei,menu_background,1.0);
    ld midle=WinWid/2.0;

    new_file=Button_do(Figure(midle-200,midle,350,550,new_file_tex,1.0),&create_new_file,window_light,shade_menu);
    old_file=Button_do(Figure(midle,midle+200,350,550,old_file_tex,1.0),&load_old_file,window_light,shade_menu);
    lab=Button_do(Figure(midle-200,midle,550,750,lab_tex,1.0),&choose_lab_select,window_light,shade_menu);
    photo=Button_do(Figure(midle,midle+200,550,750,photo_tex,1.0),&create_new_file,window_light,shade_menu);
    exit_b=Button_do(Figure(midle-200,midle+200,750,950,exit_tex,1.0),&exit_,light_exit,shade_exit);

}



void creat_feel()
{
    //cout<<WinWid<<'!'<<' '<<WinHei<<'\n';
    for (int i=0;i<feel_size;i++)
        for (int j=0;j<feel_size;j++)
        if (rand()%3)
        feel_background.push_back(Figure(feel_seg_size*i, feel_seg_size*(i+1), feel_seg_size*j, feel_seg_size*(j+1), feel_background_texture[0],1)); else
        feel_background.push_back(Figure(feel_seg_size*i, feel_seg_size*(i+1), feel_seg_size*j, feel_seg_size*(j+1), feel_background_texture[1],1));

    for (int i=1;i<feel_size;i++)
        for (int j=1;j<feel_size;j++)
            object[i][j]=Circle_element(i*feel_seg_size,j*feel_seg_size);

    left_menu_background=Figure(0,left_menu_size+20,0,WinHei,left_menu_background_tex,1.0);

    for (int i=0;i<7;i++)
        left_menu_vertical[i]=Figure(0,left_menu_size/2.0,100+i*(WinHei-100)/7.0,100+(i+1)*(WinHei-100)/7.0,left_menu_vertical[i].tex,1.0);

    for (int i=0;i<7;i++)
        left_menu_horizontal[i]=Figure(left_menu_size/2.0,left_menu_size+20,100+i*(WinHei-100)/7.0,100+(i+1)*(WinHei-100)/7.0,left_menu_horizontal[i].tex,1.0);

    ld www=WinWid/4.0;
    ld hhh=WinHei/4.0;
    for (int i=0;i<16;i++)
    {
        int x=i%4;
        int y=i/4;
        choose_lab[i]=Button_do(Figure(x*www,(x+1)*www,y*hhh,(y+1)*hhh,choose_lab_tex[i],1.0),&create_lab,light_lab,shade_lab);
    }

    line_mode=Button(Figure(100,left_menu_size+20,50,100,line_mode_tex,1.0),{&line_mode_used});
    save=Button_do(Figure(0,50,0,50,save_tex,1.0),&save_do,window_light,window_shade.tex);
    point_mode=Button(Figure(0,50,50,100,point_mode_tex,1.0),{&point_mode_used});
    move_mode=Button(Figure(150,200,0,50,move_tex,1.0),{&move_mode_used});
    delete_mode=Button(Figure(50,100,50,100,delete_mode_tex,1.0),{&delete_mode_used});
    U_ask_mode=Button(Figure(200,250,0,50,u_mode,1.0),{&U_ask_mode_used});
    potential_mode=Button(Figure(250,300,0,50,p_mode,1.0),{&potential_mode_used});

    undo_button=Button_do(Figure(50,100,0,50,undo_tex,1.0),&undo,window_light,window_shade.tex);
    redo_button=Button_do(Figure(100,150,0,50,redo_tex,1.0),&redo,window_light,window_shade.tex);

    shade_button1.tex=shade_button_tex1;
    shade_button2.tex=shade_button_tex2;

    double w1=WinWid/2.3;
    double h1=WinHei/2.3;
    double w2=WinWid/2.5+100;
    double h2=WinHei/2.5+100;
    double l=(WinWid-w1*2)/2.0;

    lab_background0 = Figure(0,WinWid,0,WinHei,lab_background,1.0);

    input_info_background=Figure(w1/1.15,WinWid-w1/1.15,40,WinHei-h1*1.62+10,info_background,1.0);
    input_feel=Figure(w2-60,WinWid-w2+60,160,200,text_line,1.0);
    input_ok=Button_do(Figure(w1,w1+l,WinHei-h1,WinHei-h1+100,ok_tex,1.0),&input_ok_do,light_ok,shade_circle);
    input_R_ok=Button_do(Figure(w1,w1+l,WinHei-h1,WinHei-h1+100,ok_tex,1.0),&change_R,light_ok,shade_circle);
    input_bad=Button_do(Figure(w1+l,w1+2*l,WinHei-h1,WinHei-h1+100,bad_tex,1.0),&input_bad_do,light_ok,shade_circle);

    back_to_main=Button_do(Figure(WinWid-100,WinWid,WinHei-100,WinHei,back_button_tex,1.0),&back_to_main_do,light_down,shade_down);

    statement_show=Button_do(Figure(WinWid-100,WinWid-50,50,100,show_statements_tex,1.0),&show_statement,light_ok,shade_circle);
    answer_lab=Button_do(Figure(WinWid-100,WinWid-50,150,200,ok_lab_tex,1.0),&read_anses,light_ok,shade_circle);

    window_shade=Figure(0,WinWid,0,WinHei,window_shade.tex,0.0);

    ld mx_power=0.001;
    main_menu_create();

    lab_ans[0]={2,1,1,1};
    lab_ask[0]={"R","I1","I2","I3"};
    lab_ans[1]={1,1,1,3};
    lab_ask[1]={"U1","U2","U3","R"};
    lab_ans[2]={1,0};
    lab_ask[2]={"R","I1"};
    lab_ans[3]={1};
    lab_ask[3]={"I1"};
    lab_ans[4]={1};
    lab_ask[4]={"R"};
    lab_ans[5]={1};
    lab_ask[5]={"R"};
    lab_ans[6]={5};
    lab_ask[6]={"R"};
    lab_ans[7]={5,8};
    lab_ask[7]={"R1","R2"};
    lab_ans[8]={3,12};
    lab_ask[8]={"R1","R2"};
    lab_ans[9]={44/15,3};
    lab_ask[9]={"R1","R2"};
    for (int i=10;i<16;i++)
    {
        lab_ans[i].pb(0);
        lab_ask[i].pb("");
    }

}



void Initialize(int w, int h)
{
    //cout<<w<<' '<<h<<'\n';
    glViewport(0,0,w,h);
    real_WinWid=w;
    real_WinHei=h;
    WinWid=1920;
    WinHei=1080;
    kx=real_WinWid/WinWid;
    ky=real_WinHei/WinHei;
    //cout<<WinWid<<' '<<WinHei<<' '<<real_WinWid<<' '<<real_WinHei<<'\n';
    left_menu_size=(WinHei-100)/7.0*2.0;
    startx=-left_menu_size;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0, WinWid, WinHei, 0.0, 0.f, -1.f);

	glMatrixMode(GL_MODELVIEW);

	creat_feel();

}



void mouse_pressed(int button, int state, int x, int y)
{
    x/=kx;
    y/=ky;

    if (in_main_menu)
    {
        main_menu_reaction(button,state);
    }

    if (in_feel && U_ask_mode_used)
    {
        U_ask_mouse_pressed_motion(mousex,mousey,x,y);
    }

    if (in_feel && delete_mode_used)
    {
        delete_mode_mouse_pressed_motion(mousex,mousey,x,y);
    }




    mousex=x;
    mousey=y;
    if (in_feel)
    {
        if (window_message)
        {
            window_message_reaction(button,state);
            return;
        }

        if (potential_mode_used)
        {
            potential_mode_reaction(button,state);
            return;
        }

        if (input_info_mode)
        {
            input_info_mouse_pressed(button,state);
            return;
        }

        if (object_menu_used)
        {
            object_menu_mouse_pressed(button,state);
            return;
        }

        if (delete_mode_used)
        {
            delete_mode_mouse_pressed(button,state);
            return;
        }

        if (U_ask_mode_used)
        {
            U_ask_mouse_pressed(button,state);
            return;
        }

        if (line_mode_used && mousex>left_menu_size)
            add_point_to_choosen();

        if (mousex<=left_menu_size)
            left_menu_mouse_pressed(button,state); else
            feel_mouse_pressed(button,state);
    }
}

void mouse_pressed_motion(int x, int y)
{

    x/=kx;
    y/=ky;
    if (in_feel && U_ask_mode_used)
    {
        U_ask_mouse_pressed_motion(mousex,mousey,x,y);
        return;
    }
    if (in_feel && delete_mode_used)
    {
        delete_mode_mouse_pressed_motion(mousex,mousey,x,y);
        return;
    }

    mousex=x;
    mousey=y;
    if (in_feel)
    {
        if (line_mode_used && mousex>left_menu_size)
            add_point_to_choosen();
    }

}

void mouse_motion(int x, int y)
{

    x/=kx;
    y/=ky;
    mousex=x;
    mousey=y;
}




void redraw(int)
{
    glutPostRedisplay();
    glutTimerFunc(30,redraw,0);
}


int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);

	ilInit();
    iluInit();
    ilutInit();
    ilutRenderer(ILUT_OPENGL);
    ilSetInteger(IL_KEEP_DXTC_DATA, IL_TRUE);
    ilutEnable(ILUT_GL_AUTODETECT_TEXTURE_TARGET);
    ilutEnable(ILUT_OPENGL_CONV);
    ilutEnable(ILUT_GL_USE_S3TC);


    glutCreateWindow("q");

    load_all();

    glutReshapeFunc(Initialize);
    glutDisplayFunc(Draw);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(skeyboard);
    glutTimerFunc(30, redraw, 0);
    glutMouseFunc(mouse_pressed);
    glutMotionFunc(mouse_pressed_motion);
    glutPassiveMotionFunc(mouse_motion);
    glutFullScreen();

    scan("textures/scheme.bmp");

    glutMainLoop();

	return 0;
}
