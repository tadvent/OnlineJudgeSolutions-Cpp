/*
ID: wjl1241
LANG: C++
TASK: telecow
*/

#include<cstdio>
#include<cstdlib>
#include<vector>
#include<list>
#include<algorithm>
using namespace std;

const int infinity = 100000000; // 10^8

class CMaxFlow {
public:
    CMaxFlow():nextId(0){}
    void clear(){
        nextId = 0;
    }
    void setVerNum(int n){ // 1, 2, 3, ..., n
        graph.resize(n+1);
    }
    bool addArc(int from, int to, int cap, int Idx = -1){
        graph[from].push_back(SArc(to, cap, Idx<0? ++nextId: Idx));
        return true;
    }
    bool setPoints(int Src, int Snk){
        src = Src;
        snk = Snk;
        return true;
    }
    int calc(){
        int total = 0, u;
        calcInit();
        vector<list<SRNArc>::iterator> cur(rsn.size());
        vector<int> pre(rsn.size());
        vector<int> h(rsn.size(), 0);
        vector<int> h_cnt(rsn.size()+1, 0);
        h_cnt[0] = rsn.size() - 1;  // all vertices' h are 0, so h_cnt[0] = n (rsn.size() == n+1)

        for(int i=1; i<(int)rsn.size(); ++i)
            cur[i] = rsn[i].begin();

        u = src;
        while(h[src] < rsn.size() -1){
            if(u == snk){
                int augflow = infinity;
                for(int i = src; i != snk; i = cur[i]->to)
                    if(cur[i]->cap < augflow) augflow = cur[i]->cap;
                for(int i = src; i != snk; i = cur[i]->to){
                    cur[i]->cap -= augflow;
                    cur[i]->rap->cap += augflow;
                    cur[i]->flow += augflow;
                    cur[i]->rap->flow -= augflow;
                }
                total += augflow;
                u = src;
            }
            list<SRNArc>::iterator ai;
            for(ai = cur[u]; ai != rsn[u].end(); ++ai){
                if(h[u] == h[ai->to] + 1 && ai->cap > 0)break;
            }
            if(ai != rsn[u].end()){ // advance
                cur[u] = ai;
                pre[ai->to] = u;
                u = ai->to;
            } else {    // relabel and backtrack
                if(--h_cnt[h[u]] == 0)break;
                cur[u] = rsn[u].begin();
                int label = rsn.size()-1;
                for(list<SRNArc>::iterator ti = rsn[u].begin(); ti != rsn[u].end(); ++ti)
                    if(ti->cap > 0 && label > h[ti->to])label = h[ti->to];
                ++h_cnt[h[u] = label+1];
                if(u != src) u = pre[u];
            }
        }
        return total;
    }
    const vector<int> & getMinCut(){ // return the min-cut arcs' idxs (index each arc from 1 to m according to the input order)
        color.assign(rsn.size(), 0);
        dfsColor(src);
        minCut.clear();
        visited.assign(graph.size(), 0);
        dfsCut(src);
        sort(minCut.begin(), minCut.end());
        return minCut;
    }

private:
    struct SArc{        // Graph Arc
        int to, cap;    // from, to, capacity
        int idx;
        SArc(){}
        SArc(int To, int Cap, int Idx): to(To), cap(Cap), idx(Idx){}
    };
    struct SRNArc{          // Residual Network Arc
        int fr, to, cap, flow, idx;
        SRNArc *rap;       // reverse arc pointer
        SRNArc(){}
        SRNArc(int From, int To, int Cap, int Idx, SRNArc *RevArc = NULL)
            :fr(From), to(To), cap(Cap), idx(Idx), flow(0), rap(RevArc){}
    };

    vector< list<SArc> > graph;
    vector< list<SRNArc> > rsn;
    vector<int> minCut;
    int src, snk, nextId;

    bool calcInit(){
        rsn.assign(graph.size(), list<SRNArc>());
        for(int i=1; i<graph.size(); ++i){
            for(list<SArc>::const_iterator it=graph[i].begin(); it!=graph[i].end(); ++it){
                rsn[i].push_back(SRNArc(i, it->to, it->cap, it->idx));
                rsn[it->to].push_back(SRNArc(it->to, i, 0, -it->idx, &rsn[i].back()));
                rsn[i].back().rap = &rsn[it->to].back();
            }
        }
        return true;
    }

    vector<int> color, visited;
    void dfsColor(int u){
        color[u] = 1;
        for(list<SRNArc>::iterator i = rsn[u].begin(); i != rsn[u].end(); ++i)
            if(color[i->to] == 0 && i->cap > 0)dfsColor(i->to);
    }
    void dfsCut(int u){
        visited[u] = 1;
        for(list<SArc>::iterator i = graph[u].begin(); i != graph[u].end(); ++i){
            if(color[i->to] == 0){
                if(i->cap > 0)
                    minCut.push_back(i->idx);
            }
            else if(!visited[i->to])
                dfsCut(i->to);
        }
    }
};

int main(){
    FILE *fin, *fout;
    int N, M, c1, c2, i;
    CMaxFlow mxf;

    fin = fopen("telecow.in", "r");
    fscanf(fin, "%d%d%d%d ", &N, &M, &c1, &c2);
    mxf.setVerNum(2*N);
    for(i=1; i<=N; ++i) mxf.addArc(2*i-1, 2*i, 10000+i);
    for(i=1; i<=M; ++i){
        int v1, v2;
        fscanf(fin, "%d%d ", &v1, &v2);
        mxf.addArc(2*v1, 2*v2-1, infinity);
        mxf.addArc(2*v2, 2*v1-1, infinity);
    }
    fclose(fin);

    fout = fopen("telecow.out", "w");
    mxf.setPoints(2*c1, 2*c2-1);
    mxf.calc();
    const std::vector<int> &downIdxs = mxf.getMinCut();

    fprintf(fout, "%d\n", downIdxs.size());
    if(downIdxs.size() > 0){
        fprintf(fout, "%d", downIdxs.front());
        for(i = 1; i < (int)downIdxs.size(); ++i)
            fprintf(fout, " %d", downIdxs[i]);
    }
    fputc('\n', fout);
    fclose(fout);

    return EXIT_SUCCESS;
}

/*
int main(){
    FILE *fin, *fout;
    int N, M, c1, c2, i;
    fin = fopen("telecow.in", "r");
    if(!fin || fscanf(fin, "%d%d%d%d ", &N, &M, &c1, &c2) == EOF){
        fprintf(stderr, "Data read error...\n");
        getchar();
        exit(1);
    }

    CMaxFlow mxf;
    mxf.setVerNum(2*N);
    for(i=1; i<=N; ++i){
        mxf.addArc(2*i-1, 2*i, 10000+i);
    }
    for(i=1; i<=M; ++i){
        int v1, v2;
        if(fscanf(fin, "%d%d ", &v1, &v2) == EOF)
            break;
        mxf.addArc(2*v1, 2*v2-1, infinity);
        mxf.addArc(2*v2, 2*v1-1, infinity);
    }
    if(i<=M){
        fclose(fin);
        fprintf(stderr, "Lines data read error...\n");
        getchar();
        exit(1);
    }
    fclose(fin);

    fout = fopen("telecow.out", "w");
    if(!fout){
        fprintf(stderr, "Can't open out file...\n");
        getchar();
        exit(2);
    }

    mxf.setPoints(2*c1, 2*c2-1);
    mxf.calc();
    //fprintf(fout, "%d\n", mxf.calc());

    const std::vector<int> &downIdxs = mxf.getMinCut();

    fprintf(fout, "%d\n", downIdxs.size());
    if(downIdxs.size() > 0){
        fprintf(fout, "%d", downIdxs.front());
        for(i = 1; i < (int)downIdxs.size(); ++i){
            fprintf(fout, " %d", downIdxs[i]);
        }
    }
    fputc('\n', fout);
    fclose(fout);

    return EXIT_SUCCESS;
}
*/
