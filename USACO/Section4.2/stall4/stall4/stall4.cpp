/*
ID: wjl1241
PROG: stall4
LANG: C++
*/

#include<fstream>
#include<vector>
using namespace std;

struct edge{
    int vert;
    bool link;
    edge *next;
    edge *rev;
    edge(){}
    edge(int V, bool L, edge *N):vert(V), link(L), next(N), rev(NULL){}
};

vector<edge*> Net;
int src, des;

int maxmatch(){
    int match = 0, node;
    vector<unsigned> dist(Net.size(), 0);
    vector<edge*> current(Net);
    vector<edge*> prev(Net.size());
    vector<int> numbs(Net.size()+2, 0);
    numbs[0] = Net.size();
    node = src;
    while(dist[src] < Net.size()){
        if(node == des){
            for(int i=src; i!=des; i=current[i]->vert){
                current[i]->link = false;
                current[i]->rev->link = true;
            }
            ++match;
            node = src;
        }
        edge *e;
        for(e = current[node]; e; e = e->next)
            if(e->link && dist[node] == dist[e->vert] + 1)break;
        if(e){
            current[node] = e;
            prev[e->vert] = e->rev;
            node = e->vert;
        } else {
            if(0 == (--numbs[dist[node]]))break;
            current[node] = Net[node];
            unsigned mind = Net.size();
            for(edge *ce=Net[node]; ce; ce=ce->next)
                if(ce->link)mind = min(mind, dist[ce->vert]);
            dist[node] = mind + 1;
            ++numbs[dist[node]];
            if(node != src)
                node = prev[node]->vert;
        }
    }
    return match;
}

int main(){
    ifstream fin("stall4.in");
    ofstream fout("stall4.out");
    int N, M;
    fin>>N>>M;
    Net.resize(N+M+2, (edge*)NULL);
    for(int i=1; i<=N; ++i){
        int ns, j;
        fin>>ns;
        while(ns--){
            fin>>j;
            Net[i] = new edge(N+j,true,Net[i]);
            Net[N+j] = new edge(i,false,Net[N+j]);
            Net[i]->rev = Net[N+j];
            Net[N+j]->rev = Net[i];
        }
        Net[0] = new edge(i, true, Net[0]);
        Net[i] = new edge(0, false, Net[i]);
        Net[0]->rev = Net[i];
        Net[i]->rev = Net[0];
    }
    for(int i=N+1; i<=N+M; ++i){
        Net[i] = new edge(N+M+1,true,Net[i]);
        Net[N+M+1] = new edge(i,false,Net[N+M+1]);
        Net[i]->rev = Net[N+M+1];
        Net[N+M+1]->rev = Net[i];
    }
    src = 0; des = N+M+1;
    fout<<maxmatch()<<endl;
    fin.close();fout.close();
    return 0;
}