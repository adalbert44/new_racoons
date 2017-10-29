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

    cout << endl;
    cout << "  Name: " << filename << endl;
    cout << " Width: " << width << endl;
    cout << "Height: " << height << endl;

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
