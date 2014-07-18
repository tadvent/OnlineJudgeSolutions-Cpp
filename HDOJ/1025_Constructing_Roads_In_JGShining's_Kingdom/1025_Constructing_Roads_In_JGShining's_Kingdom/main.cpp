#include<cstdio>
#include<utility>
#include<map>
#include<algorithm>
using namespace std;
const int maxn = 500002;

pair<int, int> roads[maxn];
int N;

bool input(){
    if(scanf("%d", &N) == EOF)return false;
    for(int i=0; i<N; ++i){
        scanf("%d%d", &roads[i].first, &roads[i].second);
    }
    return true;
}

int max_road(){
    map<int, int> max_roads_till_r;
    max_roads_till_r.insert(make_pair(0, 0));
    int maxrd = 0;

    sort(roads, roads+N);
    for(int p = 0; p < N; ++p){
        int &r = roads[p].second;
        map<int,int>::iterator it = max_roads_till_r.lower_bound(r), prev;
        prev = it; --prev;
        int newroads = prev->second + 1;
        maxrd = max(maxrd, newroads);
        it = max_roads_till_r.insert(it, make_pair(r, newroads));
        ++it;
        while(it != max_roads_till_r.end() && newroads >= it->second){
            max_roads_till_r.erase(it++);
        }
    }
    return maxrd;
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("i.txt", "r", stdin);
    freopen("o.txt", "w", stdout);
#endif
    int iTest = 1, ans;
    while(input()){
        ans = max_road();
        printf("Case %d:\nMy king, at most %d ", iTest++, ans);
        printf((ans>1)?"roads":"road");
        printf(" can be built.\n\n");
    }
}
