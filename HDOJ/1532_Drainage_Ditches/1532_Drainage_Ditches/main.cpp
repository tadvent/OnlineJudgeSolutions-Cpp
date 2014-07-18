// template of maxflow program
#include<climits>
#include<vector>

class MaxFlow{
    struct Edge{
        int to;
        int cap;
        int flow;
        int r_arc; // reverse arc idx
        int n_arc; // next arc idx
        Edge(int toVex, int Capacity, int revArc, int nextArc)
            :to(toVex), cap(Capacity), flow(0), r_arc(revArc), n_arc(nextArc){}
    };

    std::vector<Edge> edge;
    std::vector<int> net;

    void rev_bfs(int sink, std::vector<int> &d, std::vector<int> &numbs){
        int head = 0;
        std::vector<int> q;
        q.reserve(net.size());

        d.assign(net.size(), INT_MAX);
        numbs.assign(net.size()+1, 0);

        d[sink] = 0;
        ++numbs[0];
        q.push_back(sink);
        while(head != q.size()){
            int v = q[head++];
            for(int e=net[v]; e!=-1; e=edge[e].n_arc){
                int u = edge[e].to;
                if(d[u] == INT_MAX && edge[edge[e].r_arc].cap > 0){
                    d[u] = d[v] + 1;
                    ++numbs[d[u]];
                    q.push_back(u);
                }
            }
        }
    }
public:
    void init(int nVex, int nEdge = 0){ // vex: 0 ~ nVex-1
        if(!nEdge)nEdge = nVex*5;
        net.assign(nVex, -1);
        edge.reserve(2*nEdge);
    }
    void add(int from, int to, int cap = 1){
        edge.push_back(Edge(to, cap, edge.size()+1, net[from]));
        edge.push_back(Edge(from, 0, edge.size()-1, net[to]));
        net[from] = edge.size() - 2;
        net[to]   = edge.size() - 1;
    }
    int calc(int src, int sink){
        int flow = 0, u = src;
        std::vector<int> d, numbs;
        rev_bfs(sink, d, numbs);
        std::vector<int> cur_edge(net);
        std::vector<int> pre(net.size());

        while(d[src] < (int)net.size()){
            if(u == sink){
                int delta = INT_MAX;
                for(int i=src; i!=sink; i=edge[cur_edge[i]].to)
                    if(edge[cur_edge[i]].cap < delta)delta = edge[cur_edge[i]].cap;
                for(int i=src; i!=sink; i=edge[cur_edge[i]].to){
                    edge[cur_edge[i]].cap -= delta;
                    edge[cur_edge[i]].flow += delta;
                    edge[edge[cur_edge[i]].r_arc].cap += delta;
                    edge[edge[cur_edge[i]].r_arc].flow -= delta;
                }
                flow += delta;
                u = src;
            }

            int e;
            for(e=cur_edge[u]; e!=-1; e=edge[e].n_arc)
                if(edge[e].cap > 0 && d[u] == d[edge[e].to] + 1)break;
            if(e != -1){
                cur_edge[u] = e;
                pre[edge[e].to] = u;
                u = edge[e].to;
            } else {
                if(!(--numbs[d[u]]))break;  // GAP
                cur_edge[u] = net[u];
                int mind = INT_MAX;
                for(e=net[u]; e!=-1; e=edge[e].n_arc)
                    if(edge[e].cap > 0 && d[edge[e].to] < mind) mind = d[edge[e].to];
                d[u] = (mind<INT_MAX)? mind+1:net.size();
                ++numbs[d[u]];
                if(u != src)u = pre[u];
            }
        }
        return flow;
    }
};

#include<cstdio>
using namespace std;
int main(){
#ifndef ONLINE_JUDGE
    freopen("i.txt", "r", stdin);
    freopen("o.txt", "w", stdout);
#endif
    int e, n, x, y, c;
    MaxFlow mf;
    while(scanf("%d%d", &e, &n) != EOF){
        mf.init(n, e);
        while(e--){
            scanf("%d%d%d", &x, &y, &c);
            mf.add(x-1, y-1, c);
        }
        printf("%d\n", mf.calc(0, n-1));
    }
}

