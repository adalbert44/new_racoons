#ifndef READ_WRITE_H_INCLUDED
#define READ_WRITE_H_INCLUDED

    #include "includes.h"

    void read(string way);
    void write(string way);
    bool in_all_files(string st);
    void add_all_files(string st);
    int save_do();
    vector<vector<Color>  > readBMP(string file);
    vector<vector<bool>  > read_pic(string file);

#endif // READ_WRITE_H_INCLUDED

