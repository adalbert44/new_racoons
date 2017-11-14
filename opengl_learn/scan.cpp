#include "scan.h"

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

vector<digit> digits;

vector<pair<int,int> > pluss,minuss;
vector<pair<int,int> > dot;

vector<vector<int> > colour;
vector<vector<bool> > vec,use_p,need_use;
vector<pair<int,int> > visited_points;
vector<Element> elements;

vector<pair<int,int> > points[2000];

vector<prov> rebers;

bool all_very_bad;

void clear_all()
{
    digits.clear();
    pluss.clear();
    minuss.clear();
    dot.clear();
    colour.clear();
    vec.clear();
    use_p.clear();
    need_use.clear();
    visited_points.clear();
    elements.clear();

    for (int i=0;i<2000;i++)
        points[i].clear();
    rebers.clear();
    all_very_bad=0;
}

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
    for (int i=0;i<(int)vec.size();i++)
    {
        res.pb({});
        for (int j=0;j<(int)vec[i].size();j++)
            res[i].pb(0.2125*vec[i][j].R + 0.7154*vec[i][j].G + 0.0721*vec[i][j].B);
    }
    return(res);
}

vector<vector<bool> > read_pic(string file)
{
    vector<vector<Color> > vec=readBMP(file,all_very_bad);
    vector<vector<bool> > a;
    if (all_very_bad) return(a);

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

        if (i+1<(int)vec.size())
            if (vec[i+1][j] && !colour[i+1][j])
                q.push({i+1,j});

        if (j-1>=0)
            if (vec[i][j-1]  && !colour[i][j-1])
                q.push({i,j-1});

        if (j+1<(int)vec[i].size() )
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
    if (i.fir==0 || i.fir==(int)vec.size()-1)
        return(1);
    if (i.sec==0 || i.sec==(int)vec[0].size()-1)
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

bool check_midle(pt p1_, pt p2_, pt p3_, pt p4_)
{
    int mnx=min({p1_.x,p2_.x,p3_.x,p4_.x});
    int mxx=max({p1_.x,p2_.x,p3_.x,p4_.x});
    int mny=min({p1_.y,p2_.y,p3_.y,p4_.y});
    int mxy=max({p1_.y,p2_.y,p3_.y,p4_.y});


    pt pp=pt((p1_.x+p3_.x)/2.0,(p1_.y+p3_.y)/2.0);

    ld len=dist_pt(p1_,pp);
    ld len_=len/2.0;

    p1_=pt(pp.x+(p1_.x-pp.x)*0.3 , pp.y+(p1_.y-pp.y)*0.3);

    len=dist_pt(p3_,pp);
    len_=len/2.0;

    p3_=pt(pp.x+(p3_.x-pp.x)*0.3 , pp.y+(p3_.y-pp.y)*0.3);

    pp=pt((p2_.x+p4_.x)/2.0,(p2_.y+p4_.y)/2.0);

    len=dist_pt(p2_,pp);
    len_=len/2.0;

    p2_=pt(pp.x+(p2_.x-pp.x)*0.3 , pp.y+(p2_.y-pp.y)*0.3);

    len=dist_pt(p4_,pp);
    len_=len/2.0;

    p4_=pt(pp.x+(p4_.x-pp.x)*0.3 , pp.y+(p4_.y-pp.y)*0.3);

     mnx=min({p1_.x,p2_.x,p3_.x,p4_.x});
     mxx=max({p1_.x,p2_.x,p3_.x,p4_.x});
     mny=min({p1_.y,p2_.y,p3_.y,p4_.y});
     mxy=max({p1_.y,p2_.y,p3_.y,p4_.y});


    for (int i=mnx;i<=mxx;i++)
        for (int j=mny;j<=mxy;j++)
        {
            if (abs(area(p1_,p2_,pt(i,j))+area(p3_,p2_,pt(i,j))+area(p3_,p4_,pt(i,j))+area(p1_,p4_,pt(i,j))
                -area(p1_,p2_,p3_)-area(p1_,p3_,p4_))<EPS)
                {
                    if (i>=0 && i<vec.size())
                        if (j>=0 && j<vec[0].size())
                        if (vec[i][j]==0)
                        {
                            return(1);
                        }

                }
        }
    return(0);
}

vector<pt> intersect_black(pt p1, pt p2)
{
    int mnx=min(p1.x,p2.x);
    int mxx=max(p1.x,p2.x);
    int mny=min(p1.y,p2.y);
    int mxy=max(p1.y,p2.y);



    p1.x+=0.5;
    p1.y+=0.5;
    p2.x+=0.5;
    p2.y+=0.5;

    vector<pt> res;

    for (int i=mnx;i<=mxx;i++)
        for (int j=mny;j<=mxy;j++)
        {
            if (i<0)
                continue;
            if (j<0)
                continue;
            if (i>=vec.size())
                continue;
            if (j>=vec[0].size())
                continue;

            pt o;
            bool ch=0;
            if (intersect(line(p1,p2),line(pt(i,j),pt(i+1,j)),o))
                ch=1;
            if (intersect(line(p1,p2),line(pt(i+1,j),pt(i+1,j+1)),o))
                ch=1;
            if (intersect(line(p1,p2),line(pt(i+1,j+1),pt(i,j+1)),o))
                ch=1;
            if (intersect(line(p1,p2),line(pt(i,j),pt(i,j+1)),o))
                ch=1;

            if (ch && vec[i][j]==0)
                res.pb(pt(i,j));
        }

    return (res);
}

bool check_res(pt p1_, pt p2_, pt p3_, pt p4_)
{
    vector<pt> g12=intersect_black(p1_,p2_);
    vector<pt> g23=intersect_black(p2_,p3_);
    vector<pt> g34=intersect_black(p3_,p4_);
    vector<pt> g41=intersect_black(p1_,p4_);

    if (!g12.empty() && !g34.empty())
        return 1;

    if (!g23.empty() && !g41.empty())
        return 1;

    return 0;
}

int count_seg(pt p1_, pt p2_, pt p3_, pt p4_)
{
    vector<pt> g12=intersect_black(p1_,p2_);
    vector<pt> g23=intersect_black(p2_,p3_);
    vector<pt> g34=intersect_black(p3_,p4_);
    vector<pt> g41=intersect_black(p1_,p4_);

    return ((g12.size()!=0) + (g23.size()!=0) + (g34.size()!=0) + (g41.size()!=0));
}

void add(pt p1_, pt p2_, pt p3_, pt p4_)
{

    pt pp=pt((p1_.x+p3_.x)/2.0,(p1_.y+p3_.y)/2.0);

    ld len=dist_pt(p1_,pp);
    ld len_=len+40;


    p1_=pt(pp.x+(p1_.x-pp.x)*1.1 , pp.y+(p1_.y-pp.y)*1.1);


    len=dist_pt(p3_,pp);
    len_=len+40;

    p3_=pt(pp.x+(p3_.x-pp.x)*1.1 , pp.y+(p3_.y-pp.y)*1.1);

    pp=pt((p2_.x+p4_.x)/2.0,(p2_.y+p4_.y)/2.0);

    len=dist_pt(p2_,pp);
    len_=len+40;

    p2_=pt(pp.x+(p2_.x-pp.x)*1.1 , pp.y+(p2_.y-pp.y)*1.1);

    len=dist_pt(p4_,pp);
    len_=len+40;

    p4_=pt(pp.x+(p4_.x-pp.x)*1.1 , pp.y+(p4_.y-pp.y)*1.1);


    while (count_seg(p1_,p2_,p3_,p4_)>2)
    {
        pt pp=pt((p1_.x+p3_.x)/2.0,(p1_.y+p3_.y)/2.0);

        ld len=dist_pt(p1_,pp);
        ld len_=len+40;


        p1_=pt(pp.x+(p1_.x-pp.x)*1.1 , pp.y+(p1_.y-pp.y)*1.1);


        len=dist_pt(p3_,pp);
        len_=len+40;

        p3_=pt(pp.x+(p3_.x-pp.x)*1.1 , pp.y+(p3_.y-pp.y)*1.1);

        pp=pt((p2_.x+p4_.x)/2.0,(p2_.y+p4_.y)/2.0);

        len=dist_pt(p2_,pp);
        len_=len+40;

        p2_=pt(pp.x+(p2_.x-pp.x)*1.1 , pp.y+(p2_.y-pp.y)*1.1);

        len=dist_pt(p4_,pp);
        len_=len+40;

        p4_=pt(pp.x+(p4_.x-pp.x)*1.1 , pp.y+(p4_.y-pp.y)*1.1);

    }


    if (count_seg(p1_,p2_,p3_,p4_)!=2)
        return;

    elements.pb(Element());
    elements.back().p={p1_,p2_,p3_,p4_};

    vector<pair<int,int> > inform;
    for (auto i:digits)
    {
       if (abs(area(p1_,p2_,pt(i.x,i.y))+area(p3_,p2_,pt(i.x,i.y))+area(p3_,p4_,pt(i.x,i.y))+area(p1_,p4_,pt(i.x,i.y))
                -area(p1_,p2_,p3_)-area(p1_,p3_,p4_))<EPS)
            inform.pb({i.y,i.zn});
    }

    sort(inform.begin(),inform.end());

    ld R=0;

    for (auto i:inform)
    {
        R*=10;
        R+=i.sec;
    }


    int last=inform.size()-1;

    for (auto i:dot)
    {
        if (abs(area(p1_,p2_,pt(i.fir,i.sec))+area(p3_,p2_,pt(i.fir,i.sec))+area(p3_,p4_,pt(i.fir,i.sec))+area(p1_,p4_,pt(i.fir,i.sec))
                -area(p1_,p2_,p3_)-area(p1_,p3_,p4_))<EPS)
                {
                    if (last>=0)
                    while (i.sec<inform[last].fir)
                    {
                        R/=10.0;
                        last--;
                        if (last<0)
                            break;
                    }
                }
    }

    elements.back().R=R;
    bool ch=0;

    for (auto i:minuss)
        if (abs(area(p1_,p2_,pt(i.fir,i.sec))+area(p3_,p2_,pt(i.fir,i.sec))+area(p3_,p4_,pt(i.fir,i.sec))+area(p1_,p4_,pt(i.fir,i.sec))
                -area(p1_,p2_,p3_)-area(p1_,p3_,p4_))<EPS)
        {
            ch=1;
            elements.back().minuss=pt(i.fir,i.sec);
        }


    for (auto i:pluss)
        if (abs(area(p1_,p2_,pt(i.fir,i.sec))+area(p3_,p2_,pt(i.fir,i.sec))+area(p3_,p4_,pt(i.fir,i.sec))+area(p1_,p4_,pt(i.fir,i.sec))
                -area(p1_,p2_,p3_)-area(p1_,p3_,p4_))<EPS)
        {
            ch=1;
            elements.back().pluss=pt(i.fir,i.sec);
        }

    if (ch)
    {
        elements.back().name="energy";
        return;
    }

    if (check_midle(p1_,p2_,p3_,p4_))
    {
        elements.back().name="key";
        return;
    }

    if (check_res(p1_,p2_,p3_,p4_))
    {
        elements.back().name="rezistor";
        return;
    }

    elements.back().name="reostat";
    return;

}

void add_volt(pt p, ld r)
{
    r+=40;
    elements.pb(Element());
    elements.back().p={p};
    elements.back().rad=r;
    elements.back().name="voltmetr";
}

void add_amp(pt p, ld r)
{
    r+=40;
    elements.pb(Element());
    elements.back().p={p};
    elements.back().rad=r;
    elements.back().name="ampermetr";
}

bool try_add(pt p1_, pt p2_, pt p3_, pt p4_, vector<pair<int,int> > &vec)
{
    if (abs(angle(p1_,p2_,p4_)-acos(-1)/2.0)>acos(-1)/9.0)
        return(0);
    if (abs(angle(p4_,p1_,p3_)-acos(-1)/2.0)>acos(-1)/9.0)
        return(0);
    if (abs(angle(p2_,p3_,p1_)-acos(-1)/2.0)>acos(-1)/9.0)
        return(0);
    if (abs(angle(p3_,p2_,p4_)-acos(-1)/2.0)>acos(-1)/9.0)
        return(0);


    if (abs(area(p1_,p2_,p3_))+abs(area(p1_,p4_,p3_))<1.5*ld(vec.size()))
    {
        add(p1_,p2_,p3_,p4_);
        return(1);
    } else
    return(0);
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

    if (try_add(mnx,mny,mxx,mxy,vec))
        return;

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

    if (ch)
        add_amp(O,r);

    return(ch);
}


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


    if (ch)
        add_volt(O,r);
    return(ch);
}

vector<pair<int,int> > bfs3(pair<int,int> u, vector<vector< bool> > &use_p, vector<vector< bool > > & vec)
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

vector<pair<int,int> > bfs4(pair<int,int> u, vector<vector< bool> > &use_p, vector<vector< int > > & vec)
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




pair<int,int> midle(vector<pair<int,int> > visited)
{
    int mnx=1e9;
    int mny=1e9;
    int mxx=-1e9;
    int mxy=-1e9;
    for (auto i:visited)
    {
        mnx=min(mnx, i.fir);
        mxx=max(mxx,  i.fir);
        mny=min(mny,  i.sec);
        mxy=max(mxy,  i.sec);
    }

    return(make_pair((mnx+mxx)/2,(mny+mxy)/2));
}

bool check_pluss(vector<pair<int,int> > visited)
{
    int mnx=1e9;
    int mny=1e9;
    int mxx=-1e9;
    int mxy=-1e9;
    for (auto i:visited)
    {
        mnx=min(mnx, i.fir);
        mxx=max(mxx,  i.fir);
        mny=min(mny,  i.sec);
        mxy=max(mxy,  i.sec);
    }

    if ((ld)abs(mnx-mxx)/(ld)abs(mny-mxy)>1.5 || (ld)abs(mnx-mxx)/(ld)abs(mny-mxy)<0.7)
        return(0);
    int lx=abs(mnx-mxx)/4;
    int ly=abs(mny-mxy)/4;

    for (auto i:visited)
    {
        if (i.fir<mnx+lx && i.sec<mny+ly)
            return(0);
        if (i.fir<mnx+lx && i.sec>mxy-ly)
            return(0);
        if (i.fir>mxx-lx && i.sec<mny+ly)
            return(0);
        if (i.fir>mxx-lx && i.sec>mxy-ly)
            return(0);
    }

    return(1);
}

bool check_minuss(vector<pair<int,int> > visited)
{


    int mnx=1e9;
    int mny=1e9;
    int mxx=-1e9;
    int mxy=-1e9;
    for (auto i:visited)
    {
        mnx=min(mnx, i.fir);
        mxx=max(mxx, i.fir);
        mny=min(mny, i.sec);
        mxy=max(mxy, i.sec);
    }



    return((ld)abs(mny-mxy)/(ld)abs(mnx-mxx)>3);
}

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


    while ((vec.size()-1)/nb>=n)
        nb++;
    while ((vec[0].size()-1)/mb>=m)
        mb++;


    for (int i=0;i<vec.size();i++)
        for (int j=0;j<vec[i].size();j++)
            if (vec[i][j])
                res[i/nb][j/mb]=1;


    return(res);
}

digit check_digit(vector<pair<int,int> > visited)
{
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

    vector<vector<bool> > parsed;
    for (int i=0;i<=(mxx-mnx);i++)
    {
        parsed.pb({});
        for (int i=0;i<=(mxy-mny);i++)
            parsed.back().pb(0);
    }

    for (auto i:visited)
        parsed[i.fir-mnx][i.sec-mny]=1;

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

    ld kx=20.0/(mxx-mnx+1);
    ld ky=20.0/(mxy-mny+1);



    parsed.clear();


    for (int i=1;i<=28;i++)
    {
        parsed.pb({});
        for (int j=1;j<=28;j++)
            parsed.back().pb(0);
    }

    for (auto i:visited)
    {
        i.fir-=mnx;
        i.sec-=mny;
        i.fir*=kx;
        i.sec*=ky;
        i.fir=min(i.fir,20);
        i.sec=min(i.sec,20);
        parsed[i.fir+4][i.sec+4]=1;
    }

    for (int i=1;i<parsed.size()-1;i++)
        for (int j=1;j<parsed[i].size()-1;j++)
    {
        if (parsed[i+1][j] && parsed[i-1][j])
            parsed[i][j]=1;
        if (parsed[i][j+1] && parsed[i][j-1])
            parsed[i][j]=1;
    }





    int x=(mnx+mxx)/2;
    int y=(mny+mxy)/2;


    return(digit(digit(x,y,get_nomber(parsed,cnt))));
}


void clear_vec(vector<pair<int,int> > visited)
{
    for (auto i:visited)
        vec[i.fir][i.sec]=1;
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


            if (visited.size()<1000 && visited.size()>60)
            {
                if (check_pluss(visited))
                {
                    pluss.pb(midle(visited));
                    clear_vec(visited);
                } else
                if (check_minuss(visited))
                {
                    minuss.pb(midle(visited));
                    clear_vec(visited);

                }
                else
                {

                    digit u=check_digit(visited);
                    if (u.zn!=-1)
                    {
                        digits.pb(u);
                        clear_vec(visited);
                    }


                }
            } else
            if (visited.size()<=60)
            {
                dot.pb(midle(visited));
                clear_vec(visited);
            }
        }




}


vector<vector<int> > comp_pic(string file)
{

    vec=read_pic(file);
    vector<vector<int> > a;
    if (all_very_bad) return(a);
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
            ; else
        if (voltmetr(points[i]))
            ; else
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

void clear_(Element u, int now)
{
    if (u.p.size()==1)
    {
        int mnx=u.p[0].x-u.rad;
        int mxx=u.p[0].x+u.rad;
        int mny=u.p[0].y-u.rad;
        int mxy=u.p[0].y+u.rad;


        for (int i=mnx;i<=mxx;i++)
            for (int j=mny;j<=mxy;j++)
                if (dist_pt(u.p[0],pt(i,j))<=u.rad)
                    if (i>=0 && j>=0 && i<vec.size() && j<vec[0].size())
                    colour[i][j]=now;
    } else
    {
        int mnx=1e9;
        int mny=1e9;
        int mxx=-1e9;
        int mxy=-1e9;

        for (auto i:u.p)
        {
            mnx=min(mnx,(int)i.x);
            mny=min(mny,(int)i.y);
            mxx=max(mnx,(int)i.x);
            mxy=max(mny,(int)i.y);

            for (int i=mnx;i<=mxx;i++)
                for (int j=mny;j<=mxy;j++)
                    if (abs(area(u.p[0],u.p[1],pt(i,j))+area(u.p[1],u.p[2],pt(i,j))+area(u.p[2],u.p[3],pt(i,j))+area(u.p[0],u.p[3],pt(i,j))
                        -area(u.p[0],u.p[1],u.p[2])-area(u.p[0],u.p[2],u.p[3]))<EPS)
                    if (i>=0 && j>=0 && i<vec.size() && j<vec[0].size())
                    colour[i][j]=now;
        }
    }
}

ld area(Element u)
{
    if (u.p.size()==1)
        return(acos(-1)*u.rad*u.rad); else
        return(area(u.p[0],u.p[1],u.p[2])+area(u.p[0],u.p[2],u.p[3]));
}

bool in(pt u, Element e)
{
    ld a=area(e);

    return(abs((area(u,e.p[0],e.p[1])+area(u,e.p[1],e.p[2])+area(u,e.p[3],e.p[2])+area(u,e.p[0],e.p[3])-a)<EPS));
}

bool intersect(Element i, Element j)
{
    if (i.p.size()==1 && j.p.size()==1)
    {
        return(dist_pt(i.p[0],j.p[0])<i.rad+j.rad);
    }

    if (i.p.size()==4 && j.p.size()==4)
    {

        for (auto l:i.p)
            if (in(l,j))
                return(1);
        for (auto l:j.p)
            if (in(l,i))
                return(1);
        return(0);
    }

    if (i.p.size()==4)
        swap(i,j);

    for (auto l:j.p)
        if (dist_pt(i.p[0],l)<i.rad)
        return(1);
    return(0);
}

bool scan(string file)
{

    clear_all();

    comp_pic(file);

    if (all_very_bad)
        return(0);



    vector<Element> new_elements;

    for (int i=0;i<elements.size();i++)
    {
        bool ch=1;

        for (int j=0;j<elements.size();j++)
            if (j!=i)
            {
                if (area(elements[i])>=area(elements[j]))
                    if (intersect(elements[i],elements[j]))
                    ch=0;
            }


        if (ch)
            new_elements.pb(elements[i]);
    }

    elements=new_elements;


    for (int i=0;i<colour.size();i++)
        for (int j=0;j<colour[i].size();j++)
        if (colour[i][j]==0)
        colour[i][j]=0; else
        colour[i][j]=elements.size()+1;

    int cnt=0;

    for (auto i:elements)
        clear_(i,++cnt);

    for (auto i:elements)
    {
        if (i.p.size()==4)
        {
            vector<pt> g12=intersect_black(i.p[0],i.p[1]);
            vector<pt> g23=intersect_black(i.p[1],i.p[2]);
            vector<pt> g34=intersect_black(i.p[2],i.p[3]);
            vector<pt> g41=intersect_black(i.p[0],i.p[3]);
        }
    }



    vector<vector<bool> > used;

    for (auto i:colour)
    {
        used.pb({});
        for (auto j:i)
            used.back().pb(0);
    }

    for (int i=0;i<colour.size();i++)
        for (int j=0;j<colour[0].size();j++)
    {
        if (!used[i][j] && colour[i][j]==0)
        {

            vector<pair<int,int> > vis=bfs4({i,j},used,colour);

            vector<pair<pt,int> > v;

            map<int,bool> mp;
            mp[0]=1;
            mp[elements.size()+1]=1;

            for (auto i:vis)
            {
                if (i.fir+1<vec.size())
                    if (!mp[colour[i.fir+1][i.sec]])
                    {
                        v.pb({pt(i.fir,i.sec),colour[i.fir+1][i.sec]});
                        mp[colour[i.fir+1][i.sec]]=1;
                    }
                if (i.fir-1>=0)
                    if (!mp[colour[i.fir-1][i.sec]])
                    {
                        v.pb({pt(i.fir,i.sec),colour[i.fir-1][i.sec]});
                        mp[colour[i.fir-1][i.sec]]=1;
                    }

                if (i.sec+1<vec[0].size())
                    if (!mp[colour[i.fir][i.sec+1]])
                    {
                        v.pb({pt(i.fir,i.sec),colour[i.fir][i.sec+1]});
                        mp[colour[i.fir][i.sec+1]]=1;
                    }

                if (i.sec-1>=0)
                    if (!mp[colour[i.fir][i.sec-1]])
                    {
                        v.pb({pt(i.fir,i.sec),colour[i.fir][i.sec-1]});
                        mp[colour[i.fir][i.sec-1]]=1;
                    }
            }

            for (int i=0;i<(int)v.size();i++)
                for (int j=i+1;j<(int)v.size();j++)
                    rebers.pb(prov(v[i].sec,v[j].sec,v[i].fir,v[j].fir));
        }
    }

    return(put_on_feel(elements,rebers));
}
