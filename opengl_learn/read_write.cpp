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

#include <fstream>
#include <iostream>
#include <string>
#include <array>
#include <vector>
#include <iterator>

vector<vector<Color> > readBMP(string file)
{
    static constexpr size_t HEADER_SIZE = 54;

    std::ifstream bmp(file, std::ios::binary);

    std::array<char, HEADER_SIZE> header;
    bmp.read(header.data(), header.size());

    auto fileSize = *reinterpret_cast<uint32_t *>(&header[2]);
    auto dataOffset = *reinterpret_cast<uint32_t *>(&header[10]);
    auto width = *reinterpret_cast<uint32_t *>(&header[18]);
    auto height = *reinterpret_cast<uint32_t *>(&header[22]);
    auto depth = *reinterpret_cast<uint16_t *>(&header[28]);

    std::cout << "fileSize: " << fileSize << std::endl;
    std::cout << "dataOffset: " << dataOffset << std::endl;
    std::cout << "width: " << width << std::endl;
    std::cout << "height: " << height << std::endl;
    std::cout << "depth: " << depth << "-bit" << std::endl;

    std::vector<char> img(dataOffset - HEADER_SIZE);
    bmp.read(img.data(), img.size());

    auto dataSize = ((width * 3 + 3) & (~3)) * height;
    img.resize(dataSize);
    bmp.read(img.data(), img.size());

    char temp = 0;

    for (auto i = dataSize - 4; i >= 5; i -= 3)
    {
        temp = img[i];
        img[i] = img[i+2];
        img[i+2] = temp;

        //std::cout << "R: " << int(img[i] & 0xff) << " G: " << int(img[i+1] & 0xff) << " B: " << int(img[i+2] & 0xff) << std::endl;
    }

    vector<vector<Color> > res;

    for (int i=0;i<height;i++)
    {
        vector<Color> now;
        for (int j=0;j<width;j++)
            now.pb(Color(img[i*width+j],img[i*width+j+1],img[i*width+j+2]));
        res.pb(now);
    }

    return(res);
}
