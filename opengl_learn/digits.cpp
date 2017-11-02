#include "digits.h"

int get_dif(vector<vector<bool> > vec, string way)
{
    ifstream in(way);

    int res=1e9;
    while (in)
    {
        string s="";
        int cnt=0;
        for (int i=0;i<vec.size();i++)
        {
            in>>s;
            for (int j=0;j<vec[i].size();j++)
                if (vec[i][j]!=s[j]-'0')
                cnt++;
        }
        res=min(res,cnt);
    }

    in.close();
    return(res);
}

int get_nomber(vector<vector<bool> > vec, int cnt)
{
    vector<pair<int,int> > v;

    if (cnt==1)
    {
        v.pb({get_dif(vec,"digit1.txt"),1});
        v.pb({get_dif(vec,"digit2.txt"),2});
        v.pb({get_dif(vec,"digit3.txt"),3});
        v.pb({get_dif(vec,"digit5.txt"),5});
        v.pb({get_dif(vec,"digit7.txt"),7});
        v.pb({get_dif(vec,"digit4.txt"),4});
    }

    if (cnt==2)
    {
        v.pb({get_dif(vec,"digit4.txt"),4});
        v.pb({get_dif(vec,"digit0.txt"),0});
        v.pb({get_dif(vec,"digit6.txt"),6});
        v.pb({get_dif(vec,"digit9.txt"),9});
    }

    if (cnt==3)
    {
        v.pb({get_dif(vec,"digit8.txt"),8});
    }

    sort(v.begin(),v.end());
    if (v[0].fir<150)
    return(v[0].sec); else
    return(-1);
}
