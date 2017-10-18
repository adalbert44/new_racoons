#include "get_power.h"

vector<pair<int,int> > visited;

bool used[30][30],use[30][30],good[30][30];
pair<int,int> pred_[30][30];

int nomb[30][30][30][30];

bool to_start[30][30];

pair<int,int> pred[30][30];

bool bad_R(long double u)
{
    return(u>1e8);
}

int gauss (vector < vector<ld> > a, vector<ld> & ans) {
	int n = (int) a.size();
	int m = (int) a[0].size() - 1;

	vector<int> where (m, -1);
	for (int col=0, row=0; col<m && row<n; ++col) {
		int sel = row;
		for (int i=row; i<n; ++i)
			if (abs (a[i][col]) > abs (a[sel][col]))
				sel = i;
		if (abs (a[sel][col]) < 1e-15)
			continue;
		for (int i=col; i<=m; ++i)
			swap (a[sel][i], a[row][i]);
		where[col] = row;

		for (int i=0; i<n; ++i)
			if (i != row) {
				double c = a[i][col] / a[row][col];
				for (int j=col; j<=m; ++j)
					a[i][j] -= a[row][j] * c;
			}
		++row;
	}

	ans.assign (m, 0);
	for (int i=0; i<m; ++i)
		if (where[i] != -1)
			ans[i] = a[where[i]][m] / a[where[i]][i];
	for (int i=0; i<n; ++i) {
		double sum = 0;
		for (int j=0; j<m; ++j)
			sum += ans[j] * a[i][j];
		if (abs (sum - a[i][m]) > 1e-15)
			return 0;
	}

	for (int i=0; i<m; ++i)
		if (where[i] == -1)
			return int(inf);
	return 1;
}

ld get_U(pair<int,int> u, pair<int,int> v)
{
    if (object[u.fir][u.sec].f.tex==left_menu_horizontal[5].tex
        && u.fir<v.fir) return(object[u.fir][u.sec].R); else
    if (object[u.fir][u.sec].f.tex==left_menu_horizontal[5].tex
        && u.fir>v.fir) return(-object[u.fir][u.sec].R); else
    if (object[u.fir][u.sec].f.tex==left_menu_horizontal[6].tex
        && u.fir<v.fir) return(-object[u.fir][u.sec].R); else
    if (object[u.fir][u.sec].f.tex==left_menu_horizontal[6].tex
        && u.fir>v.fir) return(object[u.fir][u.sec].R); else

    if (object[u.fir][u.sec].f.tex==left_menu_vertical[5].tex
        && u.sec<v.sec) return(object[u.fir][u.sec].R); else
    if (object[u.fir][u.sec].f.tex==left_menu_vertical[5].tex
        && u.sec>v.sec) return(-object[u.fir][u.sec].R); else
    if (object[u.fir][u.sec].f.tex==left_menu_vertical[6].tex
        && u.sec<v.sec) return(-object[u.fir][u.sec].R); else
    if (object[u.fir][u.sec].f.tex==left_menu_vertical[6].tex
        && u.sec>v.sec) return(object[u.fir][u.sec].R); else

    return(0.0);
}

bool check(GLuint u)
{
    if (u==left_menu_horizontal[5].tex) return(1);
    if (u==left_menu_horizontal[6].tex) return(1);
    if (u==left_menu_vertical[5].tex) return(1);
    if (u==left_menu_vertical[6].tex) return(1);
    return(0);
}

vector<ld> get(pair<int,int> left, pair<int,int> right, int cnt)
{
    vector<ld> vec;
    while (vec.size()<=cnt) vec.pb(0);

    vector<pair<int,int> > gl;

    while (left!=mp(0,0))
    {
        gl.pb(left);
        left=pred[left.fir][left.sec];
    }

    vector<pair<int,int> > gr;
    while (right!=mp(0,0))
    {
        gr.pb(right);
        right=pred[right.fir][right.sec];
    }

    gr.pop_back();
    reverse(gr.begin(),gr.end());

    vector<pair<int,int> > vert;

    for (auto i:gl)
        vert.pb(i);
    for (auto i:gr)
        vert.pb(i);

    for (int i=0;i<vert.size();i++)
    {
        pair<int,int> fir=vert[i];
        pair<int,int> sec=vert[(i+1)%vert.size()];

        if (!check(object[fir.fir][fir.sec].f.tex) && !check(object[sec.fir][sec.sec].f.tex))
        vec[nomb[fir.fir][fir.sec][sec.fir][sec.sec]]+=(object[fir.fir][fir.sec].R+object[sec.fir][sec.sec].R)/2.0;
        vec[vec.size()-1]+=get_U(fir,sec);
    }

    return(vec);
}
/*
void get_inf(int i, int j, int pi, int pj)
{
    pred_[i][j]={pi,pj};


    use[i][j]=1;

    if (pi!=0)
        good[i][j]=1;
    for (auto to:object[i][j].reb)
    if (!(!check(object[to.fir][to.sec].f.tex) && object[to.fir][to.sec].R>1e-7))
    {
        if (use[to.fir][to.sec] && (!good[to.fir][to.sec]) && !(to.fir==pi && to.sec==pj))
        {
            to_start[i][j]=1;
            to_start[to.fir][to.sec]=1;
            power[i][j][to.fir][to.sec]=inf;
            power[to.fir][to.sec][i][j]=inf;
        }

        if (!use[to.fir][to.sec])
            get_inf(to.fir,to.sec,i,j);
    }

    good[i][j]=0;

}
*/

void solve_pot(pair<int,int> u, double p)
{

}

void solve(vector<pair<int,int> > vec)
{
    if (vec.size()<=1) return;

    int cnt=0;
    vector<vector<ld> > all;
    for (auto u:vec)
    {
        if (bad_R(object[u.fir][u.sec].R)) continue;
        potential[u.fir][u.sec]=0.0;
        for (auto v:object[u.fir][u.sec].reb)
        {
            if (bad_R(object[v.fir][v.sec].R)) continue;
            nomb[u.fir][u.sec][v.fir][v.sec]=cnt;

            cnt++;
        }
    }

    vector<ld> emp;
    while (emp.size()<=cnt) emp.pb(0);


    for (auto u:vec)
    {

        if (bad_R(object[u.fir][u.sec].R)) continue;
        vector<ld> now=emp;
        for (auto v:object[u.fir][u.sec].reb)
        {

            if (bad_R(object[v.fir][v.sec].R)) continue;
            now[nomb[u.fir][u.sec][v.fir][v.sec]]=1.0;
        }
        all.pb(now);
    }



    all.pop_back();

    for (auto u:vec)
    {

        if (bad_R(object[u.fir][u.sec].R)) continue;
        for (auto v:object[u.fir][u.sec].reb)
            if (u<v)
            {

                if (bad_R(object[v.fir][v.sec].R)) continue;
                vector<ld> now=emp;
                now[nomb[u.fir][u.sec][v.fir][v.sec]]=1.0;
                now[nomb[v.fir][v.sec][u.fir][u.sec]]=1.0;
                all.pb(now);
            }
    }

    for (auto u:vec)
    {

        if (bad_R(object[u.fir][u.sec].R)) continue;
        for (auto v:object[u.fir][u.sec].reb)
            if (u<v)
            {

                if (bad_R(object[v.fir][v.sec].R)) continue;
                if (pred[u.fir][u.sec]!=v && pred[v.fir][v.sec]!=u)
                {
                    vector<ld> toadd=get(u,v,cnt);
                    all.pb(toadd);
                }

            }
    }



    vector<ld> res;
    int r=gauss(all,res);

    if (r==0)
    {
        for (auto i:vec)
            {
                potential[i.fir][i.sec]=inf;
                for (auto j:vec)
                {
                    power[i.fir][i.sec][j.fir][j.sec]=inf;
                }
            }
    } else
    {
        for (auto u:vec)
            {
                if (bad_R(object[u.fir][u.sec].R)) continue;
                for (auto v:object[u.fir][u.sec].reb)
                {

                    if (bad_R(object[v.fir][v.sec].R)) continue;

                    power[u.fir][u.sec][v.fir][v.sec]=res[nomb[u.fir][u.sec][v.fir][v.sec]];
                    if (check(object[u.fir][u.sec].f.tex) || check(object[v.fir][v.sec].f.tex))
                    {
                        ld pl=(object[u.fir][u.sec].R+object[v.fir][v.sec].R)/2.0;
                        if (object[u.fir][u.sec].f.tex)
                        {
                            if (get_U(u,v)>0.0)
                                pl=-pl;
                        }

                        if (object[v.fir][v.sec].f.tex)
                        {
                            if (get_U(v,u)<0.0)
                                pl=-pl;
                        }

                        potential[v.fir][v.sec]=potential[u.fir][u.sec]+pl;
                    } else
                    potential[v.fir][v.sec]=potential[u.fir][u.sec]+power[u.fir][u.sec][v.fir][v.sec]*(object[u.fir][u.sec].R+object[v.fir][v.sec].R)/2.0;
                }
            }

    }

}

void dfs(int i, int j)
{
    if (bad_R(object[i][j].R)) return;
    used[i][j]=1;
    visited.pb({i,j});

    for (auto to:object[i][j].reb)
    if (!used[to.fir][to.sec])
    {
        dfs(to.fir,to.sec);
        pred[to.fir][to.sec]={i,j};
    }
}

void solve()
{
    for (int i=1;i<feel_size;i++)
        for (int j=1;j<feel_size;j++)
        {
            used[i][j]=0;
        }

    for (int i=1;i<feel_size;i++)
        for (int j=1;j<feel_size;j++)
            for (int i1=1;i1<feel_size;i1++)
                for (int j1=1;j1<feel_size;j1++)
                    power[i][j][i1][j1]=0;

    for (int i=1;i<feel_size;i++)
        for (int j=1;j<feel_size;j++)
            if (!used[i][j])
            {
                pred[i][j]={0,0};
                dfs(i,j);
                solve(visited);
                visited.clear();
            }
}
