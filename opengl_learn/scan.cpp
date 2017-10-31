#include "scan.h"

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
        res[j].pb(0);
            else
        res[j].pb(1);
        }
    }

    delete[] integral_image;

    return(res);
}

vector<vector<int> > colour;
vector<vector<bool> > vec;
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

void try_add(pt p1_, pt p2_, pt p3_, pt p4_, vector<pair<int,int> > &vec)
{
    if (abs(angle(p1_,p2_,p4_)-acos(-1)/2.0)>acos(-1)/18.0)
        return;
    if (abs(angle(p4_,p1_,p3_)-acos(-1)/2.0)>acos(-1)/18.0)
        return;
    if (abs(angle(p2_,p3_,p1_)-acos(-1)/2.0)>acos(-1)/18.0)
        return;
    if (abs(angle(p3_,p2_,p4_)-acos(-1)/2.0)>acos(-1)/18.0)
        return;

    int cnt_good=0;

    for (auto i:vec)
    {
        pt now(i.fir,i.sec);
        if (abs(area(now,p1_,p2_)+area(now,p2_,p3_)+area(now,p3_,p4_)+area(now,p4_,p1_)-area(p1_,p2_,p3_)-area(p1_,p3_,p4_))<EPS)
            cnt_good++;
    }
    if (cnt_good*10>=vec.size()*9 && cnt_good*10>=8*int(area(p1_,p2_,p3_)+area(p1_,p3_,p4_)))
        cout<<'#'<<colour[vec[0].fir][vec[0].sec]<<'\n';
}


void check_square(vector<pair<int,int> > vec)
{
    int mnx=1e9,mny=1e9,mxx=-1e9,mxy=-1e9;

    for (int i=0;i<vec.size();i++)
    {
        mnx=min(mnx,vec[i].fir);
        mxx=max(mxx,vec[i].fir);
        mny=min(mny,vec[i].sec);
        mxy=max(mxy,vec[i].sec);
    }

    int upmnx=-1e9,upmny=-1e9,domxx=1e9,domxy=1e9;
    int upmxx=-1e9,upmxy=-1e9,domnx=1e9,domny=1e9;
    for (auto i:vec)
    {
        if (i.fir<=mnx+5)
        {
            upmnx=max(upmnx,i.sec);
            domnx=min(domnx,i.sec);
        }
        if (i.fir>=mxx-5)
        {
            upmxx=max(upmxx,i.sec);
            domxx=min(domxx,i.sec);
        }

        if (i.sec<=mny+5)
        {
            upmny=max(upmny,i.fir);
            domny=min(domny,i.fir);
        }
        if (i.sec>=mxy-5)
        {
            upmxy=max(upmxy,i.fir);
            domxy=min(domxy,i.fir);
        }
    }

    pair<int,int> upleft,upright,downleft,downright,leftup,leftdown,rightup,rightdown;

    upleft={mxx,domxx};
    upright={mxx,upmxx};
    downleft={mnx,domnx};
    downright={mnx,upmnx};

    leftup={upmny,mny};
    leftdown={domny,mny};
    rightup={upmxy,mxy};
    rightdown={domxy,mxy};

    pt p1_;
    intersect(line(leftdown.fir,leftdown.sec,leftup.fir,leftup.sec),line(downleft.fir,downleft.sec,downright.fir,downright.sec),p1_);
    pt p2_;
    intersect(line(rightdown.fir,rightdown.sec,rightup.fir,rightup.sec),line(downleft.fir,downleft.sec,downright.fir,downright.sec),p2_);
    pt p3_;
    intersect(line(rightdown.fir,rightdown.sec,rightup.fir,rightup.sec),line(upleft.fir,upleft.sec,upright.fir,upright.sec),p3_);
    pt p4_;
    intersect(line(leftdown.fir,leftdown.sec,leftup.fir,leftup.sec),line(upleft.fir,upleft.sec,upright.fir,upright.sec),p4_);

    try_add(p1_,p2_,p3_,p4_,vec);
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
                visited_points.clear();
                bfs(i,j,++cnt);
                check_square(visited_points);
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

void scan(string file)
{
    comp_pic(file);
}
