#include "put_on_feel.h"

bool checkx(pt i, pt j)
{
    return(i.x<j.x);
}

bool checky(pt i, pt j)
{
    return(i.y<j.y);
}

pt get_mid(Element u)
{
    if (u.p.size()==1)
        return(u.p[0]);

    pt mid;
    mid.x=(u.p[0].x+u.p[2].x)/2.0;
    mid.y=(u.p[0].y+u.p[2].y)/2.0;
    return(mid);
}

bool can_put(vector<Element> elements, int u)
{
    int cnt[20][20];
    for (int i=0;i<20;i++)
        for (int j=0;j<20;j++)
            cnt[i][j]=0;

    for (auto i:elements)
    {
        pt mid=get_mid(i);
        int x=mid.x/u;
        int y=mid.y/u;

        if (x>9 || y>9)
            return(0);
        if (cnt[x][y])
            return(0);
        cnt[x][y]=1;
    }
    return(1);
}

void pos_hor(int j, int i, Element u)
{


    object[i][j].f.resize_(100);
    object[i][j].f.alpha=1.0;
    object[i][j].reb.pb({i,j-1});
    object[i][j].reb.pb({i,j+1});
    object[i][j].R=u.R;
    if (u.name=="rezistor")
    {
        object[i][j].f.tex=left_menu_vertical[0].tex;
    } else
    if (u.name=="reostat")
    {
        object[i][j].f.tex=left_menu_vertical[4].tex;
    } else
    if (u.name=="energy")
    {
        if (u.pluss.x<u.minuss.x)
        object[i][j].f.tex=left_menu_vertical[6].tex; else
        object[i][j].f.tex=left_menu_vertical[5].tex;
    } else
    if (u.name=="key")
    {
        object[i][j].R=1e15;
        object[i][j].f.tex=left_menu_vertical[2].tex;
    } else
    if (u.name=="voltmetr")
    {
        object[i][j].R=1e15;
        object[i][j].f.tex=left_menu_vertical[1].tex;
    } else
    if (u.name=="ampermetr")
    {
        object[i][j].f.tex=left_menu_vertical[3].tex;
    }

    object[i][j+1].f.tex=connection_point;
    object[i][j+1].f.alpha=1.0;
    object[i][j+1].f.resize_(20);
    object[i][j+1].reb.pb({i,j});

    object[i][j-1].f.tex=connection_point;
    object[i][j-1].f.alpha=1.0;
    object[i][j-1].f.resize_(20);
    object[i][j-1].reb.pb({i,j});
}

void pos_ver(int j, int i, Element u)
{
    object[i][j].f.resize_(100);
    object[i][j].f.alpha=1.0;
    object[i][j].reb.pb({i-1,j});
    object[i][j].reb.pb({i+1,j});
    object[i][j].R=u.R;
    if (u.name=="rezistor")
    {
        object[i][j].f.tex=left_menu_horizontal[0].tex;
    } else
    if (u.name=="reostat")
    {
        object[i][j].f.tex=left_menu_horizontal[4].tex;
    } else
    if (u.name=="energy")
    {
        if (u.pluss.y<u.minuss.y)
        object[i][j].f.tex=left_menu_horizontal[6].tex; else
        object[i][j].f.tex=left_menu_horizontal[5].tex;
    } else
    if (u.name=="key")
    {
        object[i][j].R=1e15;
        object[i][j].f.tex=left_menu_horizontal[2].tex;
    } else
    if (u.name=="voltmetr")
    {
        object[i][j].R=1e15;
        object[i][j].f.tex=left_menu_horizontal[1].tex;
    } else
    if (u.name=="ampermetr")
    {
        object[i][j].f.tex=left_menu_horizontal[3].tex;
    }

    object[i+1][j].f.tex=connection_point;
    object[i+1][j].f.alpha=1.0;
    object[i+1][j].f.resize_(20);
    object[i+1][j].reb.pb({i,j});

    object[i-1][j].f.tex=connection_point;
    object[i-1][j].f.alpha=1.0;
    object[i-1][j].f.resize_(20);
    object[i-1][j].reb.pb({i,j});
}


void put_on_feel(vector<Element> elements, vector<prov> rebers)
{
    /*for (auto i:elements)
        for (auto j:i.p)
        swap(j.x,j.y);

    for (auto i:rebers)
    {
        swap(i.p1.x,i.p1.y);
        swap(i.p2.x,i.p2.y);
    }*/

    vector<vector<pt> > points;
    for (auto i:elements)
        points.pb({});

    for (auto i:rebers)
    {
        points[i.c1-1].pb(i.p1);
        points[i.c2-1].pb(i.p2);
    }

    map<pair<int,int>,pair<int,int> > way;

    int start=-1;
    for (int i=1;i<=5000;i++)
        if (can_put(elements,i))
        start=i;

    if (start==-1)
        return;

    clear_feel();
    int now=0;
    for (auto u:elements)
    {
        pt mid=get_mid(u);
        int x=mid.x/start;
        int y=mid.y/start;

        x=x*3+2;
        y=y*3+2;

        if (u.p.size()==4)
        {
            int mnx=min({u.p[0].x,u.p[1].x,u.p[2].x,u.p[3].x});
            int mxx=max({u.p[0].x,u.p[1].x,u.p[2].x,u.p[3].x});
            int mny=min({u.p[0].y,u.p[1].y,u.p[2].y,u.p[3].y});
            int mxy=max({u.p[0].y,u.p[1].y,u.p[2].y,u.p[3].y});

            if (mxx-mnx>mxy-mny)
            {

                int x1=x-1;
                int y1=y;
                int x2=x+1;
                int y2=y;

                sort(points[now].begin(),points[now].end(),checkx);

                ld mx=-1;
                int last=0;

                for (int i=0;i<(int)points[now].size()-1;i++)
                if (points[now][i+1].x-points[now][i].x>mx)
                {
                    mx=max(mx,ld(points[now][i+1].x-points[now][i].x));
                    int last=i;
                }

                for (int i=0;i<(int)points[now].size();i++)
                    if (i<=last)
                    {
                        way[{points[now][i].x,points[now][i].y}]={x1,y1};
                    } else
                    {
                        way[{points[now][i].x,points[now][i].y}]={x2,y2};
                    }


                pos_hor(x,y,u);

            } else
            {
                int x1=x;
                int y1=y-1;
                int x2=x;
                int y2=y+1;

                sort(points[now].begin(),points[now].end(),checky);

                ld mx=-1;
                int last=0;

                for (int i=0;i<(int)points[now].size()-1;i++)
                if (points[now][i+1].y-points[now][i].y>mx)
                {
                    mx=max(mx,ld(points[now][i+1].y-points[now][i].y));
                    int last=i;
                }

                for (int i=0;i<(int)points[now].size();i++)
                    if (i<=last)
                    {
                        way[{points[now][i].x,points[now][i].y}]={x1,y1};
                    } else
                    {
                        way[{points[now][i].x,points[now][i].y}]={x2,y2};
                    }
                pos_ver(x,y,u);
            }

        } else
        {
            bool xy=0;
            ld mxx=-1;
            ld mxy=-1;

            for (int i=0;i<(int)points[now].size();i++)
                for (int j=0;j<(int)points[now].size();j++)
                {
                    mxx=max(mxx,(ld)abs(points[now][i].x-points[now][j].x));
                    mxy=max(mxy,(ld)abs(points[now][i].y-points[now][j].y));
                }

            if (mxx>mxy)
            {
                int x1=x-1;
                int y1=y;
                int x2=x+1;
                int y2=y;

                sort(points[now].begin(),points[now].end(),checkx);

                ld mx=-1;
                int last=0;

                for (int i=0;i<(int)points[now].size()-1;i++)
                if (points[now][i+1].x-points[now][i].x>mx)
                {
                    mx=max(mx,(ld)points[now][i+1].x-points[now][i].x);
                    int last=i;
                }

                for (int i=0;i<(int)points[now].size();i++)
                    if (i<=last)
                    {
                        way[{points[now][i].x,points[now][i].y}]={x1,y1};
                    } else
                    {
                        way[{points[now][i].x,points[now][i].y}]={x2,y2};
                    }


                pos_hor(x,y,u);
            } else
            {
                int x1=x;
                int y1=y-1;
                int x2=x;
                int y2=y+1;

                sort(points[now].begin(),points[now].end(),checky);

                ld mx=-1;
                int last=0;

                for (int i=0;i<(int)points[now].size()-1;i++)
                if (points[now][i+1].y-points[now][i].y>mx)
                {
                    mx=max(mx,(ld)points[now][i+1].y-points[now][i].y);
                    int last=i;
                }

                for (int i=0;i<(int)points[now].size();i++)
                    if (i<=last)
                    {
                        way[{(int)points[now][i].x,(int)points[now][i].y}]={x1,y1};
                    } else
                    {
                        way[{(int)points[now][i].x,(int)points[now][i].y}]={x2,y2};
                    }
                pos_ver
                (x,y,u);
            }
        }
        now++;
    }


    for (auto i:rebers)
    {
        int x1=way[{(int)i.p1.x,(int)i.p1.y}].fir;
        int y1=way[{(int)i.p1.x,(int)i.p1.y}].sec;
        int x2=way[{(int)i.p2.x,(int)i.p2.y}].fir;
        int y2=way[{(int)i.p2.x,(int)i.p2.y}].sec;


        object[y1][x1].reb.pb({y2,x2});
        object[y2][x2].reb.pb({y1,x1});
    }

    solve();
}
