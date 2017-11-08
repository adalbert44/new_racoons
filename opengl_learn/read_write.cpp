#include "read_write.h"
#include <fstream>

int save_do()
{
    write(now_file_name);
}

bool in_all_files(string st)
{
    ifstream in("all_files.txt");
    bool ch=0;
    while (in)
    {
        string s;
        in>>s;
        if (s==st) ch=1;
    }
    in.close();
    return(ch);
}

void add_all_files(string st)
{
    ifstream in("all_files.txt");
    bool ch=0;
    vector<string> vec;
    while (in)
    {
        string s;
        in>>s;
        vec.pb(s);
    }
    in.close();
    vec.pb(st);


    ofstream out("all_files.txt");
    for (int i=0;i<vec.size();i++)
        out<<vec[i]<<'\n';
    out.close();
}

void read(string way)
{
    way+=".ec";
    ifstream in(way);
    int reb_size, first_i2, second_i2;
    for(int i = 1; i <= 30; i++)
        for(int j = 1; j <= 30; j++)
        {
            in >> object[i][j].f.alpha >> object[i][j].f.tex >> object[i][j].f.x1 >> object[i][j].f.x2 >> object[i][j].f.y1 >> object[i][j].f.y2;
            in >> object[i][j].R >> object[i][j].shade >> object[i][j].U;
            in >> reb_size;
            object[i][j].reb.resize(reb_size);
            for(int i2 = 0; i2 < reb_size; i2++)
            {
                in >> first_i2 >> second_i2;
                object[i][j].reb[i2].first = first_i2;
                object[i][j].reb[i2].second = second_i2;
            }
        }
    in.close();

}

void write(string way)
{
    write_info(way);
    way+=".ec";
    ofstream out(way);
    for(int i = 1; i <= 30; i++)
        for(int j = 1; j <= 30; j++)
        {
            out << object[i][j].f.alpha << ' ' << object[i][j].f.tex << ' '<< object[i][j].f.x1 << ' ' << object[i][j].f.x2 << ' ' << object[i][j].f.y1 << ' ' << object[i][j].f.y2 << endl;
            out << object[i][j].R << ' ' << object[i][j].shade << ' ' << object[i][j].U << endl;
            out << object[i][j].reb.size() << endl;
            int reb_size = object[i][j].reb.size();
            for(int i2 = 0; i2 < reb_size; i2++)
                out << object[i][j].reb[i2].first << ' ' << object[i][j].reb[i2].second << ' ';
            out << endl;
        }
    out.close();
}



vector<vector<Color> > readBMP(string file)
{
    char *filename = new char[file.length() + 1];
    strcpy(filename, file.c_str());

    int i;
    FILE* f = fopen(filename, "rb");

    if(f == NULL)
        throw "Argument Exception";

    unsigned char info[54];
    fread(info, sizeof(unsigned char), 54, f); // read the 54-byte header

    // extract image height and width from header
    int width = *(int*)&info[18];
    int height = *(int*)&info[22];

    int row_padded = (width*3 + 3) & (~3);

    unsigned char* data = new unsigned char[row_padded];

    unsigned char tmp;
    vector<vector<Color> > res(height);

    for(int i = 0; i < height; i++)
    {
        fread(data, sizeof(unsigned char), row_padded, f);
        for(int j = 0; j < width*3; j += 3)
        {
            // Convert (B, G, R) to (R, G, B)
            tmp = data[j];
            data[j] = data[j+2];
            data[j+2] = tmp;

            res[i].pb(Color((int)data[j],(int)data[j+1],(int)data[j+2]));
        }
    }

    fclose(f);

    return(res);
}


int number(int x,int y)
{
    if((object[x][y].f.tex == left_menu_horizontal[5].tex) || (object[x][y].f.tex == left_menu_horizontal[6].tex) || (object[x][y].f.tex == left_menu_vertical[5].tex) || (object[x][y].f.tex == left_menu_vertical[6].tex))
        return(1);
    if((object[x][y].f.tex == left_menu_horizontal[3].tex) || (object[x][y].f.tex == left_menu_vertical[3].tex))
        return(2);
    if((object[x][y].f.tex == left_menu_horizontal[0].tex) || (object[x][y].f.tex == left_menu_vertical[0].tex))
        return(3);
    if((object[x][y].f.tex == left_menu_horizontal[1].tex) || (object[x][y].f.tex == left_menu_vertical[1].tex))
        return(4);
    if((object[x][y].f.tex == left_menu_horizontal[2].tex) || (object[x][y].f.tex == left_menu_vertical[2].tex))
        return(5);
    if((object[x][y].f.tex == left_menu_horizontal[4].tex) || (object[x][y].f.tex == left_menu_vertical[4].tex))
        return(6);
    if(object[x][y].f.tex == connection_point)
        return(0);
    return(99);
}

int length_long_double(long long number)
{
    int cnt = 0;
    while(round(number) != 0)
    {
        cnt++;
        number /= 10;
    }
    return cnt;
}

void write_info(string way)
{
    struct MyType
    {
        int object, num;
    };
    setlocale(0,"UKR");
    way+=".txt";
    ofstream out(way);
    long double maxU, maxI, maxR;
    int length_maxURI, last[7];
    MyType numlist[31][31];
    string name_of_object[7], text[2];
    text[1] = "#                   #                   # ";
    text[2] = "# Назва:            # Сусідні обєкти:   # "; //1 + 15 + 2 + " I: "(4) + length_maxURI + 1 = 23 + length_maxURI
    name_of_object[0] = "Точка";
    name_of_object[1] = "Джерело струму";
    name_of_object[2] = "Амперметр";
    name_of_object[3] = "Резистор";
    name_of_object[4] = "Вольтметр";
    name_of_object[5] = "Ключ";
    name_of_object[6] = "Реостат";
    for(int i = 0; i < 31; i++)
        for(int j = 0; j < 31; j++)
        {
            numlist[i][j].num = 0;
            numlist[i][j].object = 0;
        }
    for(int i = 0; i < 7; i++)
        last[i] = 0;
    out << "/__~_!__\!!+__/!!~!_!!+!!\_!/!~_!____!_+_!\_!!!__!!!!=__/!_!!___" << endl;
    out << "_ `  ;  !  !  #@@@@#. ,  !  _  ` :` -  !  !  @@@@@;  !  !  ' `` " << endl;
    out << "_    ;: _  !  #@@@@#@ '  _  _  ` .` -  _  _@@@@@@@#  _  !  ~ `: " << endl;
    out << "_`:..,``!:.!`@_@@@@##@0:`_  _  #@#:., `_::0@@#@## #``!.:_`:,.:-:" << endl;
    out << "+_~,!!!,\,'+##0#######0##E##E#######0##E##0##0####~#,!!'/~,_,!!'" << endl;
    out << "!    ~. _  !@@#@@@@#@@#@@#@@@@@@@#@@#@@#@@#@@#@@@@;@ _  !  ' `` " << endl;
    out << ",    -  '  _@@'@@@@#@@#@@#@@#@@@@#@@#@@#@@#@@#@@@ ;@ ,  _  . :` " << endl;
    out << "!`..`,-`!`:!@@!@@@@##@#@@!`@0@@@@##@#:`|@@#@@#@##:,@`!:.!:`~`-~`" << endl;
    out << "_;;~'_,;_-;_;#_'-###,~!;;_~,0##@@@###;;!',_''###~-#;;_~,!~-''~~;" << endl;
    out << "!.   ;  ~  _  0  @ .` ,  !  #@@@@@@@#  !  _  :@::##  !  _` ; .` " << endl;
    out << "_    ~: !  !  #    :: '  !  #@@@@@@@;  !  _  - ::@#  _  !  , :` " << endl;
    out << "!:::`,..~``!``0#..:~``,`:_:`_@@#@##.'..'`:!:`;:-#@#:.!:._..':;-." << endl;
    out << "/!!'~__'/,~\##+~',_!!!+~~/!!+-####~!_'~\'!\!'!_!!'0#~+!_\!'___!_" << endl;
    out << "~    ;  _  F@@_    .. ~  !  !  @@@. ;  _  !  . `. ;@@!  _  - .` " << endl;
    out << "!    -. !:@#  !    .` ~  _  _  @@.. -  !  _  : :: - @#` !  ; :` " << endl;
    out << "!---;!~;_##|;;!;..-~-;_`;!;-_;:##~,;'--!;-_;.~.,~;,::0#;!;-~-~,;" << endl;
    out << "!-~~;_'~0#-!--_--;`~'-!;`/;,_--##~~;,-;_-;!-;'-,'-,;;_##1--';~,-" << endl;
    out << "_ .  -@@#  _  _    :.@#@@!@@_  @@@` '@ |@@#` ` :: -  _ @#@ , `. " << endl;
    out << "!    '@@0  !  !    #@@#  ! @# @@@# @#  _ @#@@. :. `  !  #@`; .. " << endl;
    out << "/,,,,0##0'~/'~\~,##@@@0-,\!,0@@@@@@@0,,\-#0@@@##__!~~\,#0##_~_!'" << endl;
    out << "_`;#@##@0-._``!;@@@@@@@@@0@@0@@@@@@@@@@0@@0@@@@#;:':`_;@0@##@-,." << endl;
    out << "!  @@#  !  !  _  @@@@@@@@#@@! @@@@  #@@#@@#@@@@`. ;  _  _ @#@@: " << endl;
    out << "! @@@#@@#  _  !   :#@@@@@#@@_.@@@#  '@@#@@#@@; `. ;  ! @#@@#@@  " << endl;
    out << "!;.#####!-`!-;_-.:;~-####0-;_;-#@@~:':#0##0..-;,,;'.-!-~I####,'-" << endl;
    out << "!:```~-:+##0@`_:.`.,-._``!`:_``#@@'`,::_..!..~:';.,@#0@#!`.,:;,`" << endl;
    out << "'    `  ~  E@@#@   :  ,  '  ,@@@@#@ `  _  '  : :@@#@@_  ,  - `. " << endl;
    out << "!    ;: _  _  #@@@@:. '  !  !@@@@@@ ,  _  _  @@@@@;  !  !  ~ :: " << endl;
    out << "!~~~~!''/~,!~~!~''####0,~!~'_######'_,'_!~0##0'!''!,'/'~\''!,!'!" << endl;
    out << "_...`'::!::_.:_:``:~. _@@0@@_: #@#.:,@@0@@,:.;:-;.':.!::_.`~.-;`" << endl;
    out << "!    -. !  !  _    `: ,  *@@#@@` :@@#@@_  _  ; .` ;  _  _  ; .: " << endl;
    out << "_    ;  '  !  !    `  ~  _  _@@@@#@ '  _  _  ` .. -  !  !  ; `` " << endl;
    out << "/~_~!_!_+,'\__\!~'!!!_+~_/_!/_',_!__!~'/,_/!'_,!!_!~!/_!\_'!,!_!" << endl;
    for(int i = 1; i <= 30; i++)
        for(int j = 1; j <= 30; j++)
        {
            if(object[i][j].U > maxU)
                maxU = object[i][j].U;
            if(object[i][j].R > maxR)
                maxR = object[i][j].R;
            if(object[i][j].U / object[i][j].R > maxI)
                maxI = object[i][j].U / object[i][j].R;
        }
    length_maxURI = length_long_double(maxU);
    if(length_long_double(maxR) > length_maxURI)
        length_maxURI = length_long_double(maxR);
    if(length_long_double(maxI) > length_maxURI)
        length_maxURI = length_long_double(maxI);
    length_maxURI = length_maxURI + 3;
    int table_size = length_maxURI + length_maxURI + text[1].length() + 6;


    for(int i2 = 0; i2 <= table_size; i2++)
        out << "#";
    out << endl;
    for(int i = 1; i <= 30; i++)
        for(int j = 1; j <= 30; j++)
            if(number(i, j) != 99)
            {
                //out.precision(11);
                out << "#                   #";
                for(int i2 = 0; i2 < 23 + length_maxURI; i2++)
                    out << " ";
                out << "# ";
                for(int i2 = 0; i2 <= length_maxURI; i2++)
                    out << " ";
                out << " #" << endl;
                out << "# Назва:            # Сусідні обєкти:";
                for(int i2 = 0; i2 < 7 + length_maxURI; i2++)
                    out << " ";
                out << "# ";
                if((number(i, j) != 1) && (number(i, j) != 5))
                {
                    string s = parse_to_string(object[i][j].R);
                    out << "R: " << s;
                    for(int i2 = 0; i2 <= length_maxURI - (s.length() + 3); i2++)
                        out << " ";
                    out << " #" << endl;
                    /*if(object[i][j].R == 0)
                    {
                        out << "R: 0";
                        for(int i2 = 0; i2 <= length_maxURI - 4; i2++)
                            out << " ";
                        out << " #" << endl;
                    }
                    else
                    {
                        out << "R: " << object[i][j].R;
                        for(int i2 = 0; i2 <= length_maxURI - (length_long_double(object[i][j].R) + 3); i2++)
                            out << " ";
                        out << " #" << endl;
                    }*/
                }
                else
                    if(number(i, j) != 5)
                    {
                        string s = parse_to_string(object[i][j].R);
                        out << "U: " << s;
                        for(int i2 = 0; i2 <= length_maxURI - (s.length() + 3); i2++)
                            out << " ";
                        out << " #" << endl;
                        /*if(object[i][j].U == 0)
                        {
                            out << "U: 0";
                            for(int i2 = 0; i2 <= length_maxURI - 4; i2++)
                                out << " ";
                            out << " #" <<endl;
                        }
                        else
                        {
                            out << "U: " << object[i][j].U;
                            for(int i2 = 0; i2 <= length_maxURI - (length_long_double(object[i][j].U) + 3); i2++)
                                out << " ";
                            out << " #" << endl;
                        }*/
                    }
                    else
                    {
                        for(int i2 = 0; i2 <= length_maxURI; i2++)
                            out << " ";
                        out << " #" << endl;
                    }
                if(numlist[i][j].num == 0)
                {
                    numlist[i][j].object = number(i, j);
                    numlist[i][j].num = last[number(i, j)] + 1;
                    last[number(i,j)] =+ 1;
                }
                if(numlist[i][j].num < 10)
                    out << "# " << name_of_object[number(i, j)] << "0" << numlist[i][j].num << " ";
                    else
                    out << "# " << name_of_object[number(i, j)] << numlist[i][j].num << " ";
                for(int i2 = 0; i2 < 15 - name_of_object[number(i, j)].length(); i2++)
                    out << " ";
                out << "# ";
                int reb_size = object[i][j].reb.size();
                if(reb_size > 0)
                {
                    if(numlist[object[i][j].reb[0].first][object[i][j].reb[0].second].num == 0)
                    {
                        numlist[object[i][j].reb[0].first][object[i][j].reb[0].second].object = number(object[i][j].reb[0].first, object[i][j].reb[0].second);
                        numlist[object[i][j].reb[0].first][object[i][j].reb[0].second].num = last[number(object[i][j].reb[0].first, object[i][j].reb[0].second)] + 1;
                        last[number(object[i][j].reb[0].first, object[i][j].reb[0].second)] =+ 1;
                    }
                    if(numlist[object[i][j].reb[0].first][object[i][j].reb[0].second].num < 10)
                        out << name_of_object[number(object[i][j].reb[0].first, object[i][j].reb[0].second)] << "0" << numlist[object[i][j].reb[0].first][object[i][j].reb[0].second].num << " I: ";
                        else
                        out << name_of_object[number(object[i][j].reb[0].first, object[i][j].reb[0].second)] << numlist[object[i][j].reb[0].first][object[i][j].reb[0].second].num << " I: ";
                    int z;
                    if(abs(power[i][j][object[i][j].reb[0].first][object[i][j].reb[0].second]) > 1e+007)
                    {
                        out << "inf";
                        z = 3;
                    }
                    else
                    {
                        string s = parse_to_string(abs(power[i][j][object[i][j].reb[0].first][object[i][j].reb[0].second]));
                        out << s;
                        z = s.length();
                    }
                    for(int i2 = 0; i2 < 15 + length_maxURI - (name_of_object[number(object[i][j].reb[0].first, object[i][j].reb[0].second)].length() + z); i2++)
                        out << " ";
                    out << " # ";
                }
                else
                {
                    for(int i2 = 0; i2 < 22 + length_maxURI; i2++)
                        out << " ";
                    out << "# ";
                }
                if((number(i, j) == 4) || (number(i, j) == 3))
                {
                    /*string s = parse_to_string(object[i][j].U / object[i][j].R);
                    out << "I: " << s;*/
                    for(int i2 = 0; i2 <= length_maxURI; i2++)
                        out << " ";
                    out << " #" << endl;
                    /*if(object[i][j].R == 0)
                    {
                        out << "I: 0";
                        for(int i2 = 0; i2 <= length_maxURI - 3; i2++)
                            out << " ";
                        out << " #" << endl;
                    }
                    else
                    {
                        out << "I: " << object[i][j].U / object[i][j].R;
                        for(int i2 = 0; i2 <= length_maxURI - (length_long_double(object[i][j].U / object[i][j].R) + 2); i2++)
                            out << " ";
                        out << " #" << endl;
                    }*/
                }
                else
                {
                    for(int i2 = 0; i2 <= length_maxURI; i2++)
                        out << " ";
                    out << " #" << endl;
                }
                out << "# X: " << i << "; Y: " << j << ";";
                int length_xy = 11 + length_long_double(i) + length_long_double(j);
                for(int i2 = 0; i2 <= 18 - length_xy; i2++)
                    out << " ";
                out << " # ";
                if(reb_size > 1)
                {
                    if(numlist[object[i][j].reb[1].first][object[i][j].reb[1].second].num == 0)
                    {
                        numlist[object[i][j].reb[1].first][object[i][j].reb[1].second].object = number(object[i][j].reb[1].first, object[i][j].reb[1].second);
                        numlist[object[i][j].reb[1].first][object[i][j].reb[1].second].num = last[number(object[i][j].reb[1].first, object[i][j].reb[1].second)] + 1;
                        last[number(object[i][j].reb[1].first, object[i][j].reb[1].second)] =+ 1;
                    }
                    if(numlist[object[i][j].reb[1].first][object[i][j].reb[1].second].num < 10)
                        out << name_of_object[number(object[i][j].reb[1].first, object[i][j].reb[1].second)] << "0" << numlist[object[i][j].reb[1].first][object[i][j].reb[1].second].num << " I: ";
                        else
                        out << name_of_object[number(object[i][j].reb[1].first, object[i][j].reb[1].second)] << numlist[object[i][j].reb[1].first][object[i][j].reb[1].second].num << " I: ";
                    int z;
                    if(abs(power[i][j][object[i][j].reb[1].first][object[i][j].reb[1].second]) >= 1e+007)
                    {
                        out << "inf";
                        z = 3;
                    }
                    else
                    {
                        string s = parse_to_string(abs(power[i][j][object[i][j].reb[1].first][object[i][j].reb[1].second]));
                        out << s;
                        z = s.length();
                    }
                    for(int i2 = 0; i2 < 15 + length_maxURI - (name_of_object[number(object[i][j].reb[1].first, object[i][j].reb[1].second)].length() + z); i2++)
                        out << " ";
                    out << " # ";
                }
                else
                {
                    for(int i2 = 0; i2 < 22 + length_maxURI; i2++)
                        out << " ";
                    out << "# ";
                }
                for(int i2 = 0; i2 <= length_maxURI; i2++)
                    out << " ";
                out << " #" << endl;
                reb_size = object[i][j].reb.size();
                if(reb_size > 2)
                {
                    for(int p = 0; p < reb_size - 2; p++)
                    {
                        out << "# ";
                        for(int i2 = 0; i2 < 17; i2++)
                            out << " ";
                        out << " # ";
                        if(numlist[object[i][j].reb[p + 2].first][object[i][j].reb[p + 2].second].num == 0)
                        {
                            numlist[object[i][j].reb[p + 2].first][object[i][j].reb[p + 2].second].object = number(object[i][j].reb[p + 2].first, object[i][j].reb[p + 2].second);
                            numlist[object[i][j].reb[p + 2].first][object[i][j].reb[p + 2].second].num = last[number(object[i][j].reb[p + 2].first, object[i][j].reb[p + 2].second)] + 1;
                            last[number(object[i][j].reb[p + 2].first, object[i][j].reb[p + 2].second)] =+ 1;
                        }
                        if(numlist[object[i][j].reb[p + 2].first][object[i][j].reb[p + 2].second].num < 10)
                            out << name_of_object[number(object[i][j].reb[p + 2].first, object[i][j].reb[p + 2].second)] << "0" << numlist[object[i][j].reb[p + 2].first][object[i][j].reb[p + 2].second].num << " I: ";
                            else
                            out << name_of_object[number(object[i][j].reb[p + 2].first, object[i][j].reb[p + 2].second)] << numlist[object[i][j].reb[p + 2].first][object[i][j].reb[p + 2].second].num << " I: ";
                        int z;
                        if(abs(power[i][j][object[i][j].reb[p + 2].first][object[i][j].reb[p + 2].second]) >= 1e+7)
                        {
                            out << "inf";
                            z = 3;
                        }
                        else
                        {
                            string s = parse_to_string(abs(power[i][j][object[i][j].reb[p + 2].first][object[i][j].reb[p + 2].second]));
                            out << s;
                            z = s.length();
                        }
                        for(int i2 = 0; i2 < 15 + length_maxURI - (name_of_object[number(object[i][j].reb[p + 2].first, object[i][j].reb[p + 2].second)].length() + z); i2++)
                            out << " ";
                        out << " # ";
                        for(int i2 = 0; i2 <= length_maxURI; i2++)
                            out << " ";
                        out << " #" << endl;
                    }
                }
                out << "#                   #";
                for(int i2 = 0; i2 < 23 + length_maxURI; i2++)
                    out << " ";
                out << "# ";
                for(int i2 = 0; i2 <= length_maxURI; i2++)
                    out << " ";
                out << " #" << endl;
                for(int i2 = 0; i2 <= table_size; i2++)
                    out << "#";
                out << endl;
            }
    out.close();
}

