/*
ID: wjl1241
PROG: milk6
LANG: C++
*/
// ������Ͷ���ķ�����
// ������˵��һ�������Ҫ�ҵ������С�ı�(���鷳)
// Ȼ��ȥ���ñ�����һ����������ó�ʣ�����С��

// ��һ����������������С�ıߣ���Ҫ�Բ��������ÿһ�����ͱ�����ȥ���ñ��ٴ��������
// ����ڶ���������ȵ�һ�ε��٣����ٵĲ�ֵ���õ��ڸñ��ͱߵ����������֪�������ͱ�
// ������С���һ���ߡ�����������Ҫ��ι�����ͼ������ȥ��ָ���ߣ�������������鷳...

// ����ķ����ڹ���ͼÿ�ߵ�Ȩ��ʱ������ż��룬ʵ����õ�����ź���С�ıߣ���������С�������С�ı�
// ����������û����ôƫ�ģ�����Ҳ��ͨ��������д��ô����

// ͨ�����ⷢ�֣�����һ����ʱ���������þ��Ե�ַ�������±��ʾλ��
// �����ڸ��ƶ���ʱ��ֱ�ӽ���������ֱ�ӿ������ɣ����ÿ����������...
// ��Ȼ�����湹����ͼʱ�����鷳...

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
