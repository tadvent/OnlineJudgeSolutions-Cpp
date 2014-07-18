#include<vector>
#include<iostream>
using namespace std;

struct edge{
    int to;
    bool visited;
    edge *next;
    edge *rev;
};

vector<edge*> graph;
vector<int> edgecnt;
int totaledge, currentedge;

void addedge(int from, int to){
    edge *p = new edge;
    edge *q = new edge;
    p->next = graph[from];
    p->rev = q;
    p->to = to;
    p->visited = false;
    q->next = graph[to];
    q->rev = p;
    q->to = from;
    q->visited = false;
    graph[from] = p;
    graph[to] = q;

    ++edgecnt[from];
    ++edgecnt[to];
    ++totaledge;
}

void cleargraph(){
    edge *p, *q;
    for(int i=0; i<(int)graph.size(); ++i){
        p = graph[i];
        while(p){
            q = p;
            p = p->next;
            delete q;
        }
    }
    graph.clear();
    edgecnt.clear();
    totaledge = 0;
    currentedge = 0;
}

bool dfs(int vex, int end){
    if(totaledge == currentedge && vex == end)return true;
    for(edge *e = graph[vex]; e; e=e->next){
        if(e->visited)continue;
        e->visited = true;
        e->rev->visited = true;
        ++currentedge;
        if(dfs(e->to, end))return true;
        --currentedge;
        e->rev->visited = false;
        e->visited = false;
    }
    return false;
}

bool isEuler(){
    for(int i=0; i<(int)edgecnt.size(); ++i){
        if(edgecnt[i] % 2)return false;
    }
    return dfs(0, 0);
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("i.txt", "r", stdin);
    freopen("o.txt", "w", stdout);
#endif
    int nnode, nedge;
    totaledge = 0;
    currentedge = 0;
    while(cin>>nnode && nnode){
        cin>>nedge;
        graph.assign(nnode, (edge*)NULL);
        edgecnt.assign(nnode, 0);
        int v1, v2;
        while(nedge--){
            cin>>v1>>v2;
            addedge(v1-1, v2-1);
        }
        if(isEuler())cout << "1\n";
        else cout << "0\n";
        cleargraph();
    }
}
