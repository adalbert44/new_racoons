#ifndef MAIN_MENU_H_INCLUDED
#define MAIN_MENU_H_INCLUDED

    #include "includes.h"
    #include "input_text.h"
    #include "read_write.h"
    #include "get_power.h"
    #include "scan.h"

    void main_menu_draw();
    void main_menu_reaction(int button, int state);
    void clear_feel();
    int create_new_file();
    int load_old_file();
    int exit_();
    int create_lab();
    int choose_lab_select();
    int back_to_main_do();
    int open_info();
    int open_info();
    int make_scan_do();



#endif // MAIN_MENU_H_INCLUDED
