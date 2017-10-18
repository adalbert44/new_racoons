#include "undo_redo.h"

void change_back(Event u)
{

    if (u.type==2)
    {
        vector<pair<int,int> > reb=object[u.p1.fir][u.p1.sec].reb;
        object[u.p1.fir][u.p1.sec]=u.was;



        object[u.p1.fir][u.p1.sec].reb=reb;
    } else
    if (u.type==1)
    {
        vector<pair<int,int> > new_;
        for (auto i: object[u.p1.fir][u.p1.sec].reb)
            if (i!=u.p2) new_.pb(i);
        object[u.p1.fir][u.p1.sec].reb=new_;

        new_.clear();

        for (auto i: object[u.p2.fir][u.p2.sec].reb)
            if (i!=u.p1) new_.pb(i);
        object[u.p2.fir][u.p2.sec].reb=new_;

        new_.clear();
    } else
    if (u.type==3)
    {
        object[u.p1.fir][u.p1.sec].reb.pb({u.p2});
        object[u.p2.fir][u.p2.sec].reb.pb({u.p1});
    }
}

void del_changes(Event u)
{
    if (u.type==2)
    {
        vector<pair<int,int> > reb=object[u.p1.fir][u.p1.sec].reb;
        object[u.p1.fir][u.p1.sec]=u.become;
        object[u.p1.fir][u.p1.sec].reb=reb;
    } else
    if (u.type==1)
    {
        object[u.p1.fir][u.p1.sec].reb.pb(u.p2);
        object[u.p2.fir][u.p2.sec].reb.pb(u.p1);
    } else
    if (u.type==3)
    {
        vector<pair<int,int> > new_;
        for (auto i: object[u.p1.fir][u.p1.sec].reb)
            if (i!=u.p2) new_.pb(i);
        object[u.p1.fir][u.p1.sec].reb=new_;

        new_.clear();

        for (auto i: object[u.p2.fir][u.p2.sec].reb)
            if (i!=u.p1) new_.pb(i);
        object[u.p2.fir][u.p2.sec].reb=new_;
    }
}

int undo()
{
    if (last_event!=-1)
    {
        for (int i=0;i<events[last_event].size();i++)
            change_back(events[last_event][i]);
        last_event--;
    }
    solve();
}
int redo()
{
    if (last_event+1<events.size())
    {
        last_event++;
        for (int i=0;i<events[last_event].size();i++)
            del_changes(events[last_event][i]);
    }
    solve();
}
