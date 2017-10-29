#include "scan.h"

vector<vector<bool> > read_pic(string file)
{
    vector<vector<Color> > vec=readBMP(file);
    int mn=1e9;
    Color rmn;
    int mx=-1;
    Color rmx;

    for (auto i:vec)
        for (auto j:i)
        {
            if (sqr(j.R)+sqr(j.G)+sqr(j.B)<mn)
            {

                mn=sqr(j.R)+sqr(j.G)+sqr(j.B);
                rmn=j;
            }
        }


    for (auto i:vec)
        for (auto j:i)
            if (sqr(j.R)+sqr(j.G)+sqr(j.B)>mx)
            {
                mx=sqr(j.R)+sqr(j.G)+sqr(j.B);
                rmx=j;
            }

    vector<vector<bool> > res;

    cout<<rmn.B<<' '<<rmn.G<<' '<<rmn.R<<'\n';
    cout<<rmx.B<<' '<<rmx.G<<' '<<rmx.R<<'\n';

    for (auto i:vec)
    {
        res.pb({});
        for (auto j:i)
        {
            if ((sqr(rmn.R - j.R) + sqr(rmn.G - j.G) + sqr(rmn.B - j.B)) <
                3*(sqr(rmx.R - j.R) + sqr(rmx.G - j.G) + sqr(rmx.B - j.B)))
                res.back().pb(0); else
                res.back().pb(1);
        }
    }

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

    for (auto i:colour)
    {
        for (auto j:i)
            cout<<j;
        cout<<'\n';
    }

    return(colour);
}
