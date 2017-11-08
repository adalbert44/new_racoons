#include "digits.h"

int dist(vector<int> vec1, vector<int> vec2)
{
    int res=0;
    for (int i=0;i<vec1.size();i++)
    {
        res+=min(abs(vec1[i]-vec2[max(0,i-1)]), min(abs(vec1[i]-vec2[i]), abs(vec1[i]-vec2[min(i+1,(int)vec2.size()-1)])));
    }
    return(res);
}



int dist_dig[10];

void get_dist(vector<vector<bool> > vec)
{
    for (int i=0;i<10;i++)
        dist_dig[i]=1e9;

    ifstream in("pictures");
    int p=0;
    while(p<10000)
    {

        p++;
        int now;
        in>>now;

        string s[vec.size()];
        int cnt=0;
        for (int i=0;i<vec.size();i++)
        {
            in>>s[i];
            for (int j=0;j<vec[0].size();j++)
                cnt+=(vec[i][j]+'0'!=s[i][j]);
        }


        dist_dig[now]=min(dist_dig[now],cnt);
    }
}

int get_nomber(vector<vector<bool> > vec, int cnt)
{

    if (cnt<1 || cnt>3)
        return(-1);
    vector<pair<int,int> > v;

    get_dist(vec);

    if (cnt==1)
    {
        v.pb({dist_dig[1],1});
        v.pb({dist_dig[2],2});
        v.pb({dist_dig[3],3});
        v.pb({dist_dig[5],5});
        v.pb({dist_dig[7],7});
        v.pb({dist_dig[4],4});
    }

    if (cnt==2)
    {
        v.pb({dist_dig[4],4});
        v.pb({dist_dig[0],0});
        v.pb({dist_dig[6],6});
        v.pb({dist_dig[9],9});
    }

    if (cnt==3)
    {
        v.pb({dist_dig[8],8});
    }

    sort(v.begin(),v.end());


    if (v[0].fir<150)
    return(v[0].sec); else
    return(-1);
}
