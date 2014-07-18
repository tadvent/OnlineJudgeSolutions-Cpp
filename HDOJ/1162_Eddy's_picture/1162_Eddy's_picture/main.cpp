#include<utility>
#include<queue>
#include<vector>
#include<complex>
#include<cstdio>
using std::pair;
using std::make_pair;
using std::greater;
using std::complex;
using std::priority_queue;
using std::vector;

const int maxn = 102;
const double inf = 1e100;

complex<double> pts[maxn];
int pts_sz;

bool input(){
    if(scanf("%d", &pts_sz) == EOF)return false;
    for(int i=0; i<pts_sz; ++i){
        double x, y;
        scanf("%lf%lf", &x, &y);
        pts[i] = complex<double>(x, y);
    }
    return true;
}

double prim(){
    double dist[maxn], sum = 0.0;
    int inset[maxn] = {0}, set_sz = 0;
    for(int i=0; i<pts_sz; ++i)dist[i] = inf;
    priority_queue<pair<double, int>, vector<pair<double,int> >, greater<pair<double,int> > > pq;
    pq.push(make_pair(0.0, 0));

    while(set_sz < pts_sz && !pq.empty()){
        pair<double, int> top = pq.top();
        pq.pop();
        if(inset[top.second])continue;
        inset[top.second] = 1;
        ++set_sz;
        sum += top.first;

        for(int i=0; i<pts_sz; ++i){
            double len;
            if(!inset[i] && (len = abs(pts[top.second] - pts[i])) < dist[i] - 1e-8){
                dist[i] = len;
                pq.push(make_pair(len, i));
            }
        }
    }
    if(set_sz < pts_sz)return inf;
    else return sum;
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("i.txt", "r", stdin);
    freopen("o.txt", "w", stdout);
#endif
    while(input())
        printf("%.2f\n", prim());
}

