/*
ID: wjl1241
PROG: starry
LANG: C++
*/

#include<cstdio>
#include<utility>
#include<vector>
#include<set>
#include<algorithm>
using namespace std;

int width, height;
int skymap[102][102];
int idx;

class cluster{
    int left, top, right, bottom;  // [left, right] [top, bottom]

    int cwidth, cheight;
    vector< set<int> > points;
public:
    int idx;
    vector< pair<int, int> > stars;
    cluster():left(102), top(102), right(0), bottom(0){}
    void addstar(int x, int y){
        if(x<top)top=x;
        if(x>bottom)bottom=x;
        if(y<left)left=y;
        if(y>right)right=y;
        stars.push_back(make_pair(x, y));
    }
    void makepoints(int index){
        idx = index;
        cwidth = right - left + 1;
        cheight = bottom - top + 1;
        if(cwidth > cheight){
            swap(cwidth, cheight);
            points.resize(cheight);
            for(vector<pair<int,int> >::iterator i=stars.begin();
                i != stars.end(); ++i){
                    points[i->second - left].insert(i->first - top);
            }
        } else {
            points.resize(cheight);
            for(vector<pair<int,int> >::iterator i=stars.begin();
                i!= stars.end(); ++i){
                    points[i->first - top].insert(i->second - left);
            }
        }
    }
    bool similar(const cluster &r) const {
        if(stars.size() != r.stars.size() || cwidth != r.cwidth || cheight != r.cheight)
            return false;
        if(points == r.points)return true;
        if(equal(points.begin(), points.end(), r.points.rbegin()))return true;
        bool flag = true;
        for(int i=0; flag && i<(int)points.size(); ++i)
            for(set<int>::iterator it=points[i].begin(); flag && it!=points[i].end(); ++it)
                if(r.points[i].find(cwidth-*it-1)==r.points[i].end())flag=false;
        if(flag)return true;
        flag = true;
        for(int i=0; flag && i<(int)points.size(); ++i)
            for(set<int>::iterator it=points[i].begin(); flag && it!=points[i].end(); ++it)
                if(r.points[cheight-i-1].find(cwidth-*it-1)==r.points[cheight-i-1].end())flag=false;
        if(flag)return true;
        if(cwidth == cheight){
            flag = true;
            for(int i=0; flag && i<(int)points.size(); ++i)
                for(set<int>::iterator it=points[i].begin(); flag && it!=points[i].end(); ++it)
                    if(r.points[*it].find(i)==r.points[*it].end())flag=false;
            if(flag)return true;
            flag = true;
            for(int i=0; flag && i<(int)points.size(); ++i)
                for(set<int>::iterator it=points[i].begin(); flag && it!=points[i].end(); ++it)
                    if(r.points[*it].find(cwidth-i-1)==r.points[*it].end())flag=false;
            if(flag)return true;
            flag = true;
            for(int i=0; flag && i<(int)points.size(); ++i)
                for(set<int>::iterator it=points[i].begin(); flag && it!=points[i].end(); ++it)
                    if(r.points[cheight-*it-1].find(i)==r.points[cheight-*it-1].end())flag=false;
            if(flag)return true;
            flag = true;
            for(int i=0; flag && i<(int)points.size(); ++i)
                for(set<int>::iterator it=points[i].begin(); flag && it!=points[i].end(); ++it)
                    if(r.points[cheight-*it-1].find(cwidth-i-1)==r.points[cheight-*it-1].end())flag=false;
            if(flag)return true;
        }
        return false;
    }
};

vector<cluster> vclusters;

void floodfill(int x, int y){
    skymap[x][y] = idx;
    vclusters.back().addstar(x, y);
    if(skymap[x+1][y] == 1)floodfill(x+1, y);
    if(skymap[x][y+1] == 1)floodfill(x, y+1);
    if(skymap[x-1][y] == 1)floodfill(x-1, y);
    if(skymap[x][y-1] == 1)floodfill(x, y-1);
    if(skymap[x+1][y+1] == 1)floodfill(x+1, y+1);
    if(skymap[x+1][y-1] == 1)floodfill(x+1, y-1);
    if(skymap[x-1][y+1] == 1)floodfill(x-1, y+1);
    if(skymap[x-1][y-1] == 1)floodfill(x-1, y-1);
}

int main(){
    FILE *fp = fopen("starry.in", "r");
    fscanf(fp, "%d%d", &width, &height);
    fgetc(fp);
    for(int j=0; j<102; ++j){
        skymap[0][j] = -1;
        skymap[height+1][j] = -1;
    }
    for(int i=1; i<=height; ++i){
        skymap[i][0] = -1;
        for(int j=1; j<=width; ++j)
            skymap[i][j] = fgetc(fp) - '0';
        skymap[i][width+1] = -1;
        fgetc(fp);
    }
    fclose(fp);

    vclusters.reserve(500);
    idx = 1;
    for(int i=1; i<=height; ++i)
        for(int j=1; j<=width; ++j)
            if(skymap[i][j] == 1){
                ++idx;
                vclusters.resize(vclusters.size() + 1);
                floodfill(i, j);
            }

    for(int i=0; i<(int)vclusters.size(); ++i)
        vclusters[i].makepoints(i);

    idx = -1;
    for(int i=0; i<(int)vclusters.size(); ++i){
        if(i > vclusters[i].idx)continue;
        vclusters[i].idx = ++idx;
        for(int j=i+1; j<(int)vclusters.size(); ++j)
            if(vclusters[i].idx < vclusters[j].idx && vclusters[i].similar(vclusters[j]))
                vclusters[j].idx = vclusters[i].idx;
    }
    for(vector<cluster>::iterator i=vclusters.begin(); i!=vclusters.end(); ++i)
        for(vector<pair<int,int> >::iterator it = i->stars.begin();
            it != i->stars.end(); ++it)
            skymap[it->first][it->second] = i->idx + 'a';

    fp = fopen("starry.out", "w");
    for(int i=1; i<=height; ++i){
        for(int j=1; j<=width; ++j)
            fputc(skymap[i][j]?skymap[i][j]:'0', fp);
        fputc('\n', fp);
    }
    fclose(fp);
}

