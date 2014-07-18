#include<cstdio>
#include<vector>
#include<algorithm>

using namespace std;

int divx, divy, scStan, scOllie;

typedef vector< pair<int,int> > PointArray;
PointArray points;

class isOnline{
    int x, y;
public:
    isOnline(int X, int Y): x(X), y(Y){}
    bool operator()(const pair<int,int> &p) const {
        return p.first == x || p.second == y;
    }
};

class isXLessThan{
    int x;
public:
    isXLessThan(int X): x(X){}
    bool operator()(const pair<int,int> &p) const {
        return p.first < x;
    }
};

class isYLessThan{
    int y;
public:
    isYLessThan(int Y): y(Y){}
    bool operator()(const pair<int,int> &p) const {
        return p.second < y;
    }
};

void remove_online_points(){
    points.erase(
        remove_if(points.begin(), points.end(), isOnline(divx, divy)),
        points.end()
    );
}

void count_scores(){
    PointArray::iterator it1, it2, it3;
    it2 = partition(points.begin(), points.end(), isXLessThan(divx));
    it1 = partition(points.begin(), it2, isYLessThan(divy));
    it3 = partition(it2, points.end(), isYLessThan(divy));
    scOllie = it3 - it1;
    scStan = points.size() - scOllie;
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("i.txt", "r", stdin);
    freopen("o.txt", "w", stdout);
#endif
    int n;
    while(scanf("%d", &n) != EOF && n > 0){
        points.clear();
        points.reserve(n);
        while(n--){
            int x, y;
            scanf("%d%d", &x, &y);
            points.push_back(make_pair(x, y));
        }
        divx = points[points.size()/2].first;
        divy = points[points.size()/2].second;

        remove_online_points();
        count_scores();

        printf("%d %d\n", scStan, scOllie);
    }
}
