#include "scan.h"

vector<vector<char> > white_black(vector<vector<Color> > vec)
{
    vector<vector<char> > res;
    for (auto i:vec)
    {
        res.pb({});
        for (auto j:i)
            res.back().pb(0.2125*ld(j.R) + 0.7154*ld(j.G) + 0.0721*ld(j.B));
    }
    return(res);
}

vector<vector<bool> > Bradley_threshold(vector<vector<char> > vec)
{
    const int S = width/8;
    int s2 = S/2;
  const float t = 0.15;
  unsigned long* integral_image = 0;
  long sum=0;
  int count=0;
  int index;
  int x1, y1, x2, y2;

  //рассчитываем интегральное изображение
  integral_image = new unsigned long [width*height*sizeof(unsigned long*)];

  for (int i = 0; i < width; i++) {
    sum = 0;
    for (int j = 0; j < height; j++) {
      index = j * width + i;
      sum += src[index];
      if (i==0)
	integral_image[index] = sum;
      else
	integral_image[index] = integral_image[index-1] + sum;
    }
  }

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
      if ((long)(src[index]*count) < (long)(sum*(1.0-t)))
	res[index] = 0;
      else
	res[index] = 255;
    }
  }
}

vector<vector<bool> > read_pic(string file)
{
    vector<vector<Color> > vec=readBMP(file);
    vector<vector<char> > vec1=white_black(vec);
    vector<vector<bool> > vec2=Bradley_threshold(vec2);
    return(vec2);
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
    /*cout<<'!';
    for (int i=0;i<vec.size();i++)
    {
        colour.pb({});
        for (int j=0;j<vec[i].size();j++)
            colour[i].pb(0);
    }

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

    for (int i = 0; i < width; i++)
    {
        sum = 0;
        for (int j = 0; j < height; j++)
        {
            index = j * width + i;
            sum += src[j][i];
            if (i==0)
            integral_image[index] = sum;
            else
            integral_image[index] = integral_image[index-1] + sum;
        }
    }

/*находим границы для локальные областей
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
      if ((long)(src[index]*count) < (long)(sum*(1.0-t)))
	res[index] = 0;
      else
	res[index] = 255;
    }
  }

  delete[] integral_image;

    /*int cnt=0;
    for (int i=0;i<colour.size();i++)
        for (int j=0;j<colour[i].size();j++)
            if (!colour[i][j] && vec[i][j])
            {
                bfs(i,j,++cnt);
            }
    */
    /*freopen("koko","w",stdout);

    for (auto i:vec)
    {
        for (auto j:i)
            cout<<j;
        cout<<'\n';
    }*/

    return(colour);
}
