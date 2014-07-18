// Kruskal algorithm

#include<cstdio>
#include<vector>
#include<algorithm>
using std::sort;
using std::vector;

class UNset{
    vector<int> elem2grp;
    vector<int> belong;
    int lowestidx(int elem){
        int idx = elem2grp[elem];
        while(belong[idx] != idx)
            idx = belong[idx];
        elem2grp[elem] = idx;
        return idx;
    }
public:
    void reset(int n){
        elem2grp.resize(n+1);
        belong.resize(n+1);
        for(int i=0; i<=n; ++i)
            elem2grp[i] = belong[i] = i;
    }
    bool uni(int e1, int e2){
        e1 = lowestidx(e1);
        e2 = lowestidx(e2);
        if(e1 < e2){
            belong[e2] = e1;
        } else if(e1 > e2){
            belong[e1] = e2;
        } else return false;  // equal before
        return true;
    }
};

struct Edge{
    int fr, to, cost;
    Edge(int From, int To, int Cost)
        :fr(From), to(To), cost(Cost){}
    bool operator<(const Edge &r)const{
        return cost < r.cost;
    }
};

vector<Edge> edges;
UNset uset;

int input(){
    int N, costsum = 0;;
    if(scanf("%d", &N) == EOF)return -1;
    edges.clear();
    edges.reserve(N*(N-1)/2);
    for(int i=1; i<=N; ++i)for(int j=1; j<=N; ++j){
        int cost;
        scanf("%d", &cost);
        if(i<j)edges.push_back(Edge(i,j,cost));
    }
    uset.reset(N);

    int Q, f, t;
    scanf("%d", &Q);
    while(Q--){
        scanf("%d%d", &f, &t);
        uset.uni(f,t);
    }

    sort(edges.begin(), edges.end());
    for(vector<Edge>::iterator it=edges.begin();
        it != edges.end(); ++it){
            if(uset.uni(it->fr, it->to)){
                costsum += it->cost;
            }
    }
    return costsum;
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("i.txt", "r", stdin);
    freopen("o.txt", "w", stdout);
#endif
    int rst;
    while((rst = input()) >= 0)
        printf("%d\n", rst);
}

/////////////////////////////////////////////////////////////////
// try prim, shorter and clearer
//#include<cstdio>
//#include<utility>
//#include<queue>
//using std::pair;
//using std::make_pair;
//using std::vector;
//using std::greater;
//using std::priority_queue;
//
//const int inf = 100000000;
//const int maxn = 102;
//int matrix[maxn][maxn], N;
//
//bool input(){
//    if(scanf("%d", &N) == EOF)return false;
//    for(int i=1; i<=N; ++i)for(int j=1; j<=N; ++j)
//        scanf("%d", &matrix[i][j]);
//    int Q;
//    scanf("%d", &Q);
//    while(Q--){
//        int i,j;
//        scanf("%d%d", &i, &j);
//        matrix[i][j] = matrix[j][i] = 0;
//    }
//    return true;
//}
//
//int prim(){
//    int Inset[maxn] = {0}, set_sz = 0, sum = 0;
//    int dist[maxn];
//    for(int i=1; i<=N; ++i)dist[i] = inf;
//    priority_queue<pair<int, int>, vector<pair<int, int> >, greater<pair<int,int> > > pq;
//    pq.push(make_pair(0, 1));
//
//    while(set_sz < N && !pq.empty()){
//        pair<int, int> top = pq.top();
//        pq.pop();
//        if(Inset[top.second])continue;
//        Inset[top.second] = 1;
//        ++set_sz;
//        sum += top.first;
//
//        for(int j=1; j<=N; ++j){
//            if(!Inset[j] && matrix[top.second][j] < dist[j]){
//                dist[j] = matrix[top.second][j];
//                pq.push(make_pair(dist[j], j));
//            }
//        }
//    }
//    if(set_sz < N)return inf;
//    return sum;
//}
//
//int main(){
//#ifndef ONLINE_JUDGE
//    freopen("i.txt", "r", stdin);
//    freopen("o.txt", "w", stdout);
//#endif
//    while(input())
//        printf("%d\n", prim());
//}
