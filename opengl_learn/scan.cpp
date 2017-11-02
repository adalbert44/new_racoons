#include "scan.h"
#include "digits.h"


struct pt {
	double x, y;
	pt(int x_, int y_)
	{
        x=x_;
        y=y_;
	}

	pt()
	{

	}
};

struct line {
	double a, b, c;

    line(int x1, int y1, int x2, int y2)
    {
        a=y1-y2;
        b=-(x1-x2);
        c=-a*x1-b*y1;
    }

    line(pt p1, pt p2)
    {
        a=p1.y-p2.y;
        b=-(p1.x-p2.x);
        c=-a*p1.x-b*p1.y;
    }
};

const double EPS = 1e-9;

double det (double a, double b, double c, double d) {
	return a * d - b * c;
}

bool intersect (line m, line n, pt & res) {
	double zn = det (m.a, m.b, n.a, n.b);
	if (abs (zn) < EPS)
		return false;
	res.x = - det (m.c, m.b, n.c, n.b) / zn;
	res.y = - det (m.a, m.c, n.a, n.c) / zn;
	return true;
}

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
        res[j].pb(0);
            else
        res[j].pb(1);
        }
    }

    delete[] integral_image;
    reverse(res.begin(),res.end());
    return(res);
}

vector<vector<int> > colour;
vector<vector<bool> > vec,use_p,need_use;
vector<pair<int,int> > visited_points;

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
        visited_points.pb(now);
        colour[i][j]=c;

        if (i-1>=0)
            if (vec[i-1][j] && !colour[i-1][j])
                q.push({i-1,j});

        if (i+1<vec.size())
            if (vec[i+1][j] && !colour[i+1][j])
                q.push({i+1,j});

        if (j-1>=0)
            if (vec[i][j-1]  && !colour[i][j-1])
                q.push({i,j-1});

        if (j+1<vec[i].size() )
            if (vec[i][j+1]  && !colour[i][j+1])
                q.push({i,j+1});

    }

}

double area(pt p1, pt p2, pt p3)
{
    return abs((p2.x - p1.x) * (p3.y - p1.y) - (p2.y - p1.y) * (p3.x - p1.x))/2.0;
}

double dist_pt(pt p1, pt p2)
{
    return(sqrt(sqr(p1.x-p2.x)+sqr(p1.y-p2.y)));
}

ld angle(pt p1, pt p2, pt p3)
{
    ld b=dist_pt(p1,p2);
    ld c=dist_pt(p1,p3);
    ld a=dist_pt(p2,p3);

    return(acos((c*c+b*b-a*a)/(2.0*b*c)));
}

ld dist_to_line(pt i, line j)
{
    return(abs(j.a*i.x+j.b*i.y+j.c)/sqrt(sqr(j.a)+sqr(j.b)));
}

bool endd(pair<int,int> i)
{
    if (i.fir==0 || i.fir==vec.size()-1)
        return(1);
    if (i.sec==0 || i.sec==vec[0].size()-1)
        return(1);

    if (colour[i.fir][i.sec]!=colour[i.fir-1][i.sec]) return(1);
    if (colour[i.fir][i.sec]!=colour[i.fir][i.sec-1]) return(1);
    if (colour[i.fir][i.sec]!=colour[i.fir+1][i.sec]) return(1);
    if (colour[i.fir][i.sec]!=colour[i.fir][i.sec+1]) return(1);

    return(0);
}

void bfs2(pair<int,int> u)
{
    queue<pair<int,int> > q;
    q.push(u);
    while (!q.empty())
    {
        pair<int,int> now=q.front();
        q.pop();

        int i=now.fir;
        int j=now.sec;
        if (use_p[i][j])
            continue;
        use_p[i][j]=1;

        if (i-1>=0)
            if (need_use[i-1][j] && !use_p[i-1][j])
                q.push({i-1,j});

        if (i+1<vec.size())
            if (need_use[i+1][j] && !use_p[i+1][j])
                q.push({i+1,j});

        if (j-1>=0)
            if (need_use[i][j-1] && !use_p[i][j-1])
                q.push({i,j-1});

        if (j+1<vec[i].size())
            if (need_use[i][j+1] && !use_p[i][j+1])
                q.push({i,j+1});
    }
}

void try_add(pt p1_, pt p2_, pt p3_, pt p4_, vector<pair<int,int> > &vec)
{
    if (abs(angle(p1_,p2_,p4_)-acos(-1)/2.0)>acos(-1)/12.0)
        return;
    if (abs(angle(p4_,p1_,p3_)-acos(-1)/2.0)>acos(-1)/12.0)
        return;
    if (abs(angle(p2_,p3_,p1_)-acos(-1)/2.0)>acos(-1)/12.0)
        return;
    if (abs(angle(p3_,p2_,p4_)-acos(-1)/2.0)>acos(-1)/12.0)
        return;


    for (auto i:vec)
        if (min({dist_to_line(pt(i.fir,i.sec),line(p1_,p2_)),
                 dist_to_line(pt(i.fir,i.sec),line(p2_,p3_)),
                 dist_to_line(pt(i.fir,i.sec),line(p3_,p4_)),
                 dist_to_line(pt(i.fir,i.sec),line(p1_,p4_)),})<=40.0)
        {
            need_use[i.fir][i.sec]=1;
        }

    for (auto i:vec)
        if (need_use[i.fir][i.sec])
        {
            bfs2(i);
            break;
        }

    bool ch=1;

    for (auto i:vec)
        if (need_use[i.fir][i.sec] && !use_p[i.fir][i.sec])
            ch=0;

    for (auto i:vec)
    {
        need_use[i.fir][i.sec]=0;
        use_p[i.fir][i.sec]=0;
    }

    if (ch)
        cout<<"sq"<<colour[vec[0].fir][vec[0].sec]<<'\n';
}


void check_square(vector<pair<int,int> > vec)
{
    if (vec.size()<50)
        return;
    pt mnx,mny,mxx,mxy;
    mnx.x=1e9;
    mxx.x=-1e9;
    mny.y=1e9;
    mxy.y=-1e9;


    for (auto i:vec)
    {
        if (i.fir>mxx.x)
            mxx=pt(i.fir,i.sec);
        if (i.fir<mnx.x)
            mnx=pt(i.fir,i.sec);
        if (i.sec>mxy.y)
            mxy=pt(i.fir,i.sec);
        if (i.sec<mny.y)
            mny=pt(i.fir,i.sec);
    }

    try_add(mnx,mny,mxx,mxy,vec);

    pt a,b,c,d;
    a.x=mnx.x;
    a.y=mny.y;
    b.x=mxx.x;
    b.y=mny.y;
    c.x=mxx.x;
    c.y=mxy.y;
    d.x=mnx.x;
    d.y=mxy.y;
    try_add(a,b,c,d,vec);

}

bool check_circle(vector<pair<int,int> > vec)
{
    if (vec.size()<50)
        return(0);
    pt mnx,mny,mxx,mxy;
    mnx.x=1e9;
    mxx.x=-1e9;
    mny.y=1e9;
    mxy.y=-1e9;

    for (auto i:vec)
    {
        if (i.fir>mxx.x)
            mxx=pt(i.fir,i.sec);
        if (i.fir<mnx.x)
            mnx=pt(i.fir,i.sec);
        if (i.sec>mxy.y)
            mxy=pt(i.fir,i.sec);
        if (i.sec<mny.y)
            mny=pt(i.fir,i.sec);
    }

    pt O=pt((mxx.x+mnx.x)/2.0,(mny.y+mxy.y)/2.0);
    ld r=0;

    for (auto i:vec)
    {
        r=max(r,ld(dist_pt(O,pt(i.fir,i.sec))));
    }



    for (auto i:vec)
        if (dist_pt(O,pt(i.fir,i.sec))>=r/sqrt(2)+1)
        {
            need_use[i.fir][i.sec]=1;
        }
    for (auto i:vec)
        if (need_use[i.fir][i.sec])
        {
            bfs2(i);
            break;
        }

    bool ch=1;

    for (auto i:vec)
        if (need_use[i.fir][i.sec] && !use_p[i.fir][i.sec])
            ch=0;

    for (auto i:vec)
    {
        need_use[i.fir][i.sec]=0;
        use_p[i.fir][i.sec]=0;
    }

    return(ch);
}

bool ampermetr(vector<pair<int,int> > vec)
{
    if (vec.size()<50)
        return(0);
    pt mnx,mny,mxx,mxy;
    mnx.x=1e9;
    mxx.x=-1e9;
    mny.y=1e9;
    mxy.y=-1e9;

    for (auto i:vec)
    {
        if (i.fir>mxx.x)
            mxx=pt(i.fir,i.sec);
        if (i.fir<mnx.x)
            mnx=pt(i.fir,i.sec);
        if (i.sec>mxy.y)
            mxy=pt(i.fir,i.sec);
        if (i.sec<mny.y)
            mny=pt(i.fir,i.sec);
    }

    pt O=pt((mxx.x+mnx.x)/2.0,(mny.y+mxy.y)/2.0);
    ld r=0;

    for (auto i:vec)
    {
        r=max(r,ld(dist_pt(O,pt(i.fir,i.sec))));
    }



    for (auto i:vec)
        if (dist_pt(O,pt(i.fir,i.sec))>=r/sqrt(2)+1)
        {
            need_use[i.fir][i.sec]=1;
        }
    for (auto i:vec)
        if (need_use[i.fir][i.sec])
        {
            bfs2(i);
            break;
        }

    bool ch=1;

    for (auto i:vec)
        if (need_use[i.fir][i.sec] && !use_p[i.fir][i.sec])
            ch=0;

    for (auto i:vec)
    {
        need_use[i.fir][i.sec]=0;
        use_p[i.fir][i.sec]=0;
    }

    if (!ch)
        return(0);

    ch=0;

     for (int i=int(O.x-r);i<=int(O.x+r+1);i++)
        for (int j=int(O.y-r);j<=int(O.y+r+1);j++)
            if (dist_pt(pt(i,j),O)<=r/2.0)
            {
                if (colour[i][j]!=colour[vec[0].fir][vec[0].sec] && colour[i][j]!=0)
                {
                    ch=1;
                }

            }

    return(ch);
}

vector<pair<int,int> > points[2000];

bool voltmetr(vector<pair<int,int> > vec)
{
    if (vec.size()<50)
        return(0);
    pt mnx,mny,mxx,mxy;
    mnx.x=1e9;
    mxx.x=-1e9;
    mny.y=1e9;
    mxy.y=-1e9;

    for (auto i:vec)
    {
        if (i.fir>mxx.x)
            mxx=pt(i.fir,i.sec);
        if (i.fir<mnx.x)
            mnx=pt(i.fir,i.sec);
        if (i.sec>mxy.y)
            mxy=pt(i.fir,i.sec);
        if (i.sec<mny.y)
            mny=pt(i.fir,i.sec);
    }

    pt O=pt((mxx.x+mnx.x)/2.0,(mny.y+mxy.y)/2.0);
    ld r=0;

    for (auto i:vec)
    {
        r=max(r,ld(dist_pt(O,pt(i.fir,i.sec))));
    }



    for (auto i:vec)
        if (dist_pt(O,pt(i.fir,i.sec))>=r/sqrt(2)+1)
        {
            need_use[i.fir][i.sec]=1;
        }
    for (auto i:vec)
        if (need_use[i.fir][i.sec])
        {
            bfs2(i);
            break;
        }

    bool ch=1;

    for (auto i:vec)
        if (need_use[i.fir][i.sec] && !use_p[i.fir][i.sec])
            ch=0;

    for (auto i:vec)
    {
        need_use[i.fir][i.sec]=0;
        use_p[i.fir][i.sec]=0;
    }

    if (!ch)
        return(0);

    ch=1;

     for (int i=int(O.x-r);i<=int(O.x+r+1);i++)
        for (int j=int(O.y-r);j<=int(O.y+r+1);j++)
            if (dist_pt(pt(i,j),O)<=r/2.0)
                if (colour[i][j]!=colour[vec[0].fir][vec[0].sec] && colour[i][j]!=0)
                ch=0;
    return(ch);
}

vector<pair<int,int> > bfs3(pair<int,int> u, vector<vector< bool> > &use_p, vector<vector< bool> > & vec)
{
    vector<pair<int,int> > visited;
    queue<pair<int,int> > q;
    q.push(u);
    while (!q.empty())
    {

        pair<int,int> now=q.front();
        q.pop();

        int i=now.fir;
        int j=now.sec;
        if (use_p[i][j])
            continue;
        visited.pb({i,j});
        use_p[i][j]=1;

        if (i-1>=0)
            if (vec[i-1][j]==vec[i][j] && !use_p[i-1][j])
                q.push({i-1,j});

        if (i+1<vec.size())
            if (vec[i+1][j]==vec[i][j] && !use_p[i+1][j])
                q.push({i+1,j});

        if (j-1>=0)
            if (vec[i][j-1]==vec[i][j]  && !use_p[i][j-1])
                q.push({i,j-1});

        if (j+1<vec[i].size())
            if (vec[i][j+1]==vec[i][j]  && !use_p[i][j+1])
                q.push({i,j+1});
    }

    return(visited);
}

struct digit
{
    int x,y,zn;

    digit()
    {

    }

    digit(int x_, int y_, int zn_)
    {
        x=x_;
        y=y_;
        zn=zn_;
    }
};

vector<digit> digits;

vector<vector<bool> > squeeze(vector<vector<bool> > vec, int n, int m)
{
    vector<vector<bool> > res;

    for (int i=1;i<=n;i++)
    {
        res.pb({});
        for (int j=1;j<=m;j++)
            res.back().pb(0);
    }

    int nb=1;
    int mb=1;

    cout<<vec.size()-1<<' '<<n<<"@@@@@@@"<<'\n';

    while ((vec.size()-1)/nb>=n)
        nb++;
    while ((vec[0].size()-1)/mb>=m)
        mb++;


    for (int i=0;i<vec.size();i++)
        for (int j=0;j<vec[i].size();j++)
            if (vec[i][j])
                res[i/nb][j/mb]=1;

    cout<<(vec[0].size()-1)/mb<<'\n';
    return(res);
}

digit check_digit(vector<pair<int,int> > visited)
{

    //cout<<'!';
    ld mnx=1e9;
    ld mny=1e9;
    ld mxx=-1e9;
    ld mxy=-1e9;
    for (auto i:visited)
    {
        mnx=min(mnx,(ld) i.fir);
        mxx=max(mxx,(ld)  i.fir);
        mny=min(mny,(ld)  i.sec);
        mxy=max(mxy,(ld)  i.sec);
    }
    mnx--;
    mny--;
    mxx++;
    mxy++;

    ld kx=30.0/(mxx-mnx+1);
    ld ky=20.0/(mxy-mny+1);

    vector<vector<bool> > parsed;

    for (int i=1;i<=30;i++)
    {
        parsed.pb({});
        for (int j=1;j<=20;j++)
            parsed.back().pb(0);
    }

    for (auto i:visited)
    {
        i.fir-=mnx;
        i.sec-=mny;
        i.fir*=kx;
        i.sec*=ky;
        i.fir=min(i.fir,29);
        i.sec=min(i.sec,19);
        parsed[i.fir][i.sec]=1;
    }

    for (int i=1;i<parsed.size()-1;i++)
        for (int j=1;j<parsed[i].size()-1;j++)
    {
        if (parsed[i+1][j] && parsed[i-1][j])
            parsed[i][j]=1;
        if (parsed[i][j+1] && parsed[i][j-1])
            parsed[i][j]=1;
    }





    //parsed=squeeze(parsed,30,20);

    vector<vector<bool> > use_p;
    for (auto i:parsed)
    {
        use_p.pb({});
        for (auto j:parsed)
            use_p.back().pb(0);
    }


    int cnt=0;
    for (int i=0;i<parsed.size();i++)
        for (int j=0;j<parsed[0].size();j++)
        if (parsed[i][j]==0  && !use_p[i][j])
        {
            bfs3({i,j},use_p,parsed);
            cnt++;
        }

    int x=(mnx+mxx)/2;
    int y=(mny+mxy)/2;



    return(digit(x,y,get_nomber(parsed,cnt)));
}


void get_digits()
{

    vector<vector<bool> > use_p;
    for (auto i:vec)
    {
        use_p.pb({});
        for (auto j:vec)
            use_p.back().pb(0);
    }

    for (int i=0;i<vec.size();i++)
        for (int j=0;j<vec[0].size();j++)
        if (vec[i][j]==0 && !use_p[i][j])
        {
            vector<pair<int,int> > visited=bfs3({i,j},use_p,vec);
            if (visited.size()<1000 && visited.size()>10)
            {
                digit u=check_digit(visited);
                    digits.pb(u);
            }
        }

    for (auto i:digits)
    {
        cout<<i.x<<' '<<i.y<<' '<<i.zn<<'\n';
    }
}


vector<vector<int> > comp_pic(string file)
{

    vec=read_pic(file);
    get_digits();

    for (int i=0;i<vec.size();i++)
    {
        colour.pb({});
        use_p.pb({});
        need_use.pb({});
        for (int j=0;j<vec[i].size();j++)
        {
            colour[i].pb(0);
            use_p[i].pb(0);
            need_use[i].pb(0);
        }

    }

    for (int i=0;i<colour.size();i++)
        for (int j=0;j<colour[i].size();j++)
            colour[i][j]=0;

    int cnt=0;
    for (int i=0;i<colour.size();i++)
        for (int j=0;j<colour[i].size();j++)
            if (!colour[i][j] && vec[i][j])
            {
                visited_points.clear();
                bfs(i,j,++cnt);
                points[cnt]=visited_points;
            }

    for (int i=1;i<=cnt;i++)
    {
        if (ampermetr(points[i]))
            cout<<"amp"<<i<<'\n'; else
        if (voltmetr(points[i]))
            cout<<"volt"<<i<<'\n'; else
            check_square(points[i]);
    }

    /*ofstream out("koko");
    for (auto i:colour)
    {
        for (auto j:i)
            out<<j;
        out<<'\n';
    }

    out.close();*/
    return(colour);
}

void scan(string file)
{
    comp_pic(file);
}
