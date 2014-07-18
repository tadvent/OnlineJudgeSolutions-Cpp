#include<iostream>
#include<vector>
#include<map>
#include<queue>
using namespace std;

const int MaxVer = 1002;

class graph{
    static const int infinity = 2100000000;
    map<int, int> G[MaxVer];  // 0: start, 1001: end
public:
    void clear(){
        for(int i=0; i<MaxVer; ++i)
            G[i].clear();
    }
    void add(int from, int to, int time){
        map<int, int>::iterator it = G[from].find(to);
        if(it != G[from].end()){  // already have this arc
            if(it->second <= time)return;
            it->second = time;
            it = G[to].find(from);
            it->second = time;
        } else {  // insert new arc
            G[from].insert(make_pair(to, time));
            G[to].insert(make_pair(from, time));
        }
    }
    int min_dist(int from, int to){
        bool finalSet[MaxVer];
        int d[MaxVer];
        fill(d, d+MaxVer, infinity);
        memset(finalSet, 0, sizeof(finalSet));
        priority_queue<pair<int, int>, vector<pair<int, int> >,
            greater<pair<int, int> > > pq;

        pq.push(make_pair(0, from));
        d[from] = 0;

        while(!pq.empty()){
            pair<int, int> top = pq.top();
            pq.pop();
            if(finalSet[top.second])continue;
            if(top.second == to)return top.first;
            finalSet[top.second] = true;

            for(map<int,int>::const_iterator it = G[top.second].begin();
                it != G[top.second].end(); ++it){
                    if(finalSet[it->first])continue;
                    int t;
                    if((t = top.first + G[top.second][it->first]) < d[it->first]){
                        d[it->first] = t;
                        pq.push(make_pair(t, it->first));
                    }
            }
        }
        return d[to];
    }
};
const int graph::infinity;

int main(){
#ifndef ONLINE_JUDGE
    freopen("i.txt", "r", stdin);
    freopen("o.txt", "w", stdout);
#endif
    int T, S, D;
    graph g;
    while(cin>>T>>S>>D){
        g.clear();
        while(T--){
            int from, to, time;
            cin>>from>>to>>time;
            g.add(from, to, time);
        }
        while(S--){
            int src;
            cin>>src;
            g.add(0, src, 0);
        }
        while(D--){
            int des;
            cin>>des;
            g.add(des, 1001, 0);
        }
        cout<<g.min_dist(0, 1001)<<'\n';
    }
}
