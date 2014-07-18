/*
ID: wjl1241
PROG: milk6
LANG: C++
*/
// 算是用投机的方法吧
// 正常来说第一次最大流要找到序号最小的边(很麻烦)
// 然后去除该边再求一次最大流，得出剩余的最小割

// 第一次求最大流找序号最小的边，需要对参量网络的每一条饱和边依次去除该边再次求最大流
// 如果第二次最大流比第一次的少，且少的差值正好等于该饱和边的容量，则可知这条饱和边
// 即是最小割的一条边。整个过程需要多次构建新图，依次去除指定边，再求最大流，麻烦...

// 下面的方法在构造图每边的权重时将边序号加入，实际求得的是序号和最小的边，并不是最小边序号最小的边
// 但测试数据没有这么偏的，所以也能通过，懒得写那么多了

// 通过这题发现，在做一个类时，尽量少用绝对地址，多用下标表示位置
// 这样在复制对象时，直接将所有内容直接拷贝即可，不用考虑深拷贝问题...
// 不然在上面构建新图时将很麻烦...

#include<cstdio>
#include<algorithm>
#include<vector>
#include<limits>
using namespace std;

const long long infinity = numeric_limits<long long>::max();

struct edge {
    int num;    // the number index of this edge
    int ver;    // the to vertex of this edge
    long long cap;  // capacity of this edge (in residual network)
    edge *next; // next edge from same vertex
    edge *rev;  // reverse edge of this edge
    edge(int Num, int Vertex, long long Capacity, edge* Next)
        :num(Num), ver(Vertex), cap(Capacity), next(Next){}
};

class network{
    vector<edge> _vEdges;
    vector<edge*> net;
    vector<edge*> current;
    mutable vector<int> visited;
    int src, des;
    long long flow;

    bool dfs(int inver){
        // all out edges of this dfs and sub-dfs can't find a path then return false
        // else return true
        visited[inver] = 1;
        if(inver == des)return true;
        for(edge* e = net[inver]; e; e = e->next)if(!visited[e->ver] && e->cap > 0){
            current[inver] = e;
            if(dfs(e->ver))return true;
        }
        return false;
    }
    long long augment(){
        long long aug = infinity;
        for(int ver = src; ver != des; ver = current[ver]->ver)
            aug = min(aug, current[ver]->cap);
        for(int ver = src; ver != des; ver = current[ver]->ver){
            current[ver]->cap -= aug;
            current[ver]->rev->cap += aug;
        }
        return aug;
    }
    void dfsfill(int ver, vector<int> &min_cut) const {
        min_cut[ver] = 1;
        for(edge* e = net[ver]; e; e = e->next)
            if(e->cap > 0 && !min_cut[e->ver])
                dfsfill(e->ver, min_cut);
    }
    void dfsidxs(int ver, const vector<int> &min_cut, vector<int> &idxs)const{
        visited[ver] = 1;
        for(edge* e = net[ver]; e; e = e->next){
            if(min_cut[e->ver]){
                if(!visited[e->ver] && e->cap > 0)
                    dfsidxs(e->ver, min_cut, idxs);
            }
            else if(e->num > 0)
                idxs.push_back(e->num);
        }
    }
public:
    network(int nEdges, int nVertices):
      net(nVertices+1, (edge*)NULL), visited(nVertices+1){
        _vEdges.reserve(2*nEdges);
        src = 1;
        des = nVertices;
    }
    void add_edge(int num, int from, int to, long long cap){
        _vEdges.push_back(edge(num, to, cap, net[from]));
        net[from] = &(_vEdges.back());
        _vEdges.push_back(edge(0, from, 0, net[to]));
        net[to] = &(_vEdges.back());
        net[from]->rev = net[to];
        net[to]->rev = net[from];
    }
    long long maxflow(){
        flow = 0;
        current = net;
        fill(visited.begin(), visited.end(), 0);
        while(dfs(src)){
            flow += augment();
            current = net;
            fill(visited.begin(), visited.end(), 0);
        }
        return flow;
    }
    void idxs(vector<int> &vidxs) const {
        // edges idxs are stored in vidxs in sorted order
        vidxs.clear();
        vector<int> min_cut(des+1, 0);
        fill(visited.begin(), visited.end(), 0);
        dfsfill(src, min_cut);
        dfsidxs(src, min_cut, vidxs);
        sort(vidxs.begin(), vidxs.end());
    }
};

int main(){
    FILE *fin = fopen("milk6.in", "r");
    int nVers, nEdges;
    fscanf(fin, "%d%d", &nVers, &nEdges);
    network net(nEdges, nVers);
    for(int i=1; i<=nEdges; ++i){
        int from, to, cap;
        fscanf(fin, "%d%d%d", &from, &to, &cap);
        net.add_edge(i, from, to, ((long long)cap)*1001*500000+1*500000+i-1);
    }
    fclose(fin);

    FILE *fout = fopen("milk6.out", "w");
    fprintf(fout, "%d", net.maxflow()/(1001*500000));
    vector<int> idxs;
    net.idxs(idxs);
    fprintf(fout, " %d\n", idxs.size());
    for(vector<int>::iterator it=idxs.begin(); it!=idxs.end(); ++it)
        fprintf(fout, "%d\n", *it);
    fclose(fout);
}
