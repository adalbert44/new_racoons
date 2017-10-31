#include "scan.h"

vector<vector<int> > black_white(vector<vector<Color> > vec)
{
    vector<vector<int> > res;
    for (int i=0;i<vec.size();i++)
    {
        res.pb({});
        for (int j=0;j<vec[i].size();j++)
            res[i].pb(0.2125*vec[i][j].R + 0.7154*vec[i][j].G + 0.0721*vec[i][j].B);
    }
    return(res);
}

vector<vector<bool> > read_pic(string file)
{
    vector<vector<Color> > vec=readBMP(file);
    vector<vector<int> > vec1=black_white(vec);

    int width=vec[0].size();
    int height=vec.size();

    const int S = width/8;
    int s2 = S/2;
    const float t = 0.15;
    unsigned long* integral_image = 0;
    long sum=0;
    int count=0;
    int index;
    int x1, y1, x2, y2;
    cout<<"do";

  //рассчитываем интегральное изображение
    integral_image = new unsigned long [width*height*sizeof(unsigned long*)];

    for (int i = 0; i < width; i++) {
        sum = 0;
        for (int j = 0; j < height; j++) {
            index = j * width + i;
            sum += vec1[j][i];

            if (i==0)
            {
                integral_image[index] = sum;
            }
            else
            {
                integral_image[index] = integral_image[index-1] + sum;
            }

        }
    }
    cout<<"do";
    vector<vector<bool> > res(vec1.size());


//находим границы для локальные областей
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
        index = j * width + i;

        x1=i-s2;
        x2=i+s2;
        y1=j-s2;
        y2=j+s2;

        if (x1 < 0)
        x1 = 0;
        if (x2 >= width)
        x2 = width-1;
        if (y1 < 0)
        y1 = 0;
        if (y2 >= height)
        y2 = height-1;

        count = (x2-x1)*(y2-y1);

        sum = integral_image[y2*width+x2] - integral_image[y1*width+x2] -
				  integral_image[y2*width+x1] + integral_image[y1*width+x1];
        if ((long)(vec1[j][i]*count) < (long)(sum*(1.0-t)))
        res[j].pb(1);
            else
        res[j].pb(0);
        }
    }

    delete[] integral_image;

    return(res);
}

vector<vector<int> > colour;
vector<vector<bool> > vec;
void bfs(int i, int j, int c)
{
    queue<pair<int,int> > q;
    q.push({i,j});
    while (!q.empty())
    {
        pair<int,int> now=q.front();
        q.pop();
        int i=now.fir;
        int j=now.sec;
        if (colour[i][j])
            continue;
        colour[i][j]=c;

        if (i-1>=0)
            if (vec[i-1][j])
                q.push({i-1,j});

        if (i+1<vec.size())
            if (vec[i+1][j])
                q.push({i+1,j});

        if (j-1>=0)
            if (vec[i][j-1])
                q.push({i,j-1});

        if (j+1<vec[i].size())
            if (vec[i][j+1])
                q.push({i,j+1});

    }

}

vector<vector<int> > comp_pic(string file)
{

    vec=read_pic(file);
    cout<<'!';
    for (int i=0;i<vec.size();i++)
    {
        colour.pb({});
        for (int j=0;j<vec[i].size();j++)
            colour[i].pb(0);
    }

    for (int i=0;i<colour.size();i++)
        for (int j=0;j<colour[i].size();j++)
            colour[i][j]=0;

    int cnt=0;
    for (int i=0;i<colour.size();i++)
        for (int j=0;j<colour[i].size();j++)
            if (!colour[i][j] && vec[i][j])
            {
                bfs(i,j,++cnt);
            }

    freopen("koko","w",stdout);

    for (auto i:vec)
    {
        for (auto j:i)
            cout<<j;
        cout<<'\n';
    }

    return(colour);
}

void scan(string file)
{
    comp_pic(file);
}
