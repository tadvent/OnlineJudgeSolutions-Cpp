// Kruskal algorithm : O(E * logE)
// 边不用 sort() 而使用小顶堆的话可能效率会提高。
// 用一个变量记录集合的个数，当最后合并为 1 个时即可停止，因此无需对所有边排序。
/*
#include<cstdio>
#include<algorithm>
using namespace std;

struct Edge{
    int u, v, c;
    bool operator<(const Edge &r) const {
        return c < r.c;
    }
};

Edge egs[10000];
int vexgrp[102], belong[102];
int egs_sz, vex_sz;

bool input(){
    if(scanf("%d %d", &egs_sz, &vex_sz) == EOF || egs_sz == 0)
        return false;
    for(int i=0; i<egs_sz; ++i){
        int u, v, c;
        scanf("%d %d %d", &u, &v, &c);
        egs[i].u = u - 1;
        egs[i].v = v - 1;
        egs[i].c = c;
    }
    return true;
}

int vex2grp(int vex){
    vex = vexgrp[vex];
    while(vex != belong[vex])
        vex = belong[vex];
    return vex;
}

int mincost(){
    int costsum = 0;
    for(int i = 0; i < vex_sz; ++i){
        vexgrp[i] = i;
        belong[i] = i;
    }

    sort(egs, egs+egs_sz);
    for(Edge *e = egs; e < egs+egs_sz; ++e){
        int idu = vex2grp(e->u);
        int idv = vex2grp(e->v);
        if(idu != idv){ // merge
            if(idu < idv){
                belong[idv] = idu;
            } else {
                belong[idu] = idv;
            }
            vexgrp[e->u] = belong[idu];
            vexgrp[e->v] = belong[idv];
            costsum += e->c;
        }
    }

    int id = vex2grp(0);
    for(int i = 1; i < vex_sz; ++i)
        if(vex2grp(i) != id)return -1;
    return costsum;
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("i.txt", "r", stdin);
    freopen("o.txt", "w", stdout);
#endif
    while(input()){
        int cost = mincost();
        if(cost < 0)
            printf("?\n");
        else printf("%d\n", cost);
    }
}
*/
/////////////////////////////////////////////////////////
// Prim algorithm : O(E * logV)
#include<cstdio>
#include<queue>
#include<limits>
using namespace std;

const int maxint = numeric_limits<int>::max();

struct edge{
    int to, cost;
    edge *next;
    edge(int Vex, int Cost, edge* Next): to(Vex), cost(Cost), next(Next){}
};

edge *graph[102];
int egs_sz, vex_sz;

bool input(){
    if(scanf("%d %d", &egs_sz, &vex_sz) == EOF || egs_sz == 0)
        return false;
    memset(graph, 0, sizeof(graph));
    for(int i=0; i<egs_sz; ++i){
        int u, v, c;
        scanf("%d %d %d", &u, &v, &c);
        graph[u-1] = new edge(v-1, c, graph[u-1]);
        graph[v-1] = new edge(u-1, c, graph[v-1]);
    }
    return true;
}

void clear_graph(){
    for(int i=0; i<vex_sz; ++i){
        edge *p = graph[i], *q;
        while(p){
            q = p; p = p->next;
            delete q;
        }
    }
}

int mincost(){
    int dist[102], inset[102], costsum = 0, set_sz = 0;;
    fill_n(dist, vex_sz, maxint);
    memset(inset, 0, sizeof(inset));

    priority_queue<pair<int, int>, vector<pair<int, int> >, greater<pair<int, int> > > pq;
    // pq -> first  = dist[vex]
    // pq -> second = vex

    dist[0] = 0;
    pq.push(make_pair(0, 0));
    while(!pq.empty()){
        pair<int, int> t = pq.top();
        pq.pop();
        if(inset[t.second])continue;

        inset[t.second] = 1;
        ++set_sz;
        costsum += t.first;
        for(edge *e = graph[t.second]; e; e = e->next){
            if(inset[e->to] == 0 && e->cost < dist[e->to]){
                dist[e->to] = e->cost;
                pq.push(make_pair(e->cost, e->to));
            }
        }
    }
    if(set_sz < vex_sz)return -1;
    else return costsum;
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("i.txt", "r", stdin);
    freopen("o.txt", "w", stdout);
#endif
    while(input()){
        int cost = mincost();
        if(cost < 0)printf("?\n");
        else printf("%d\n", cost);
        clear_graph();
    }
}
