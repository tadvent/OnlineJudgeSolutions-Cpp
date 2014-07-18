/*
ID: wjl1241
PROG: ditch
LANG: C++
*/

//====================================================
// USACO 4.2 讲解算法，类似 Dijkstra 的方法寻找最大流增广路

//#include<fstream>
//#include<vector>
//#include<map>
//#include<algorithm>
//using namespace std;
//
//const int infinity = 2100000000;
//
//vector< map<int,int> > graph;
//
//int calmaxflow(vector< map<int,int> > &graph, int src, int des){
//    int totalflow = 0;
//    if(src == des)return infinity;
//
//    vector<int> flow(graph.size());
//    vector<int> prevloc(graph.size());
//    vector<bool> visited(graph.size());
//
//    while(true){
//        fill(flow.begin(),flow.end(),0);
//        fill(prevloc.begin(),prevloc.end(),-1);
//        fill(visited.begin(),visited.end(),false);
//        flow[src] = infinity;
//
//        while(true){
//            int maxflow = 0, maxloc = -1;
//            for(vector<map<int,int> >::size_type i=0; i<graph.size(); ++i)
//                if(flow[i] > maxflow && !visited[i]){
//                    //maxflow = flow[i];
//                    maxloc = i;
//                }
//            if(maxloc == des)break;
//            if(maxloc == -1)return totalflow;
//
//            visited[maxloc] = true;
//            for(map<int,int>::iterator itr=graph[maxloc].begin(); itr!=graph[maxloc].end();++itr)
//                if(flow[itr->first] < min(flow[maxloc], itr->second)){
//                    prevloc[itr->first] = maxloc;
//                    flow[itr->first]    = min(flow[maxloc], itr->second);
//                }
//        }
//
//        int pathflow = flow[des];
//        totalflow += pathflow;
//
//        int curloc = des;
//        while(curloc != src){
//            int nextloc = prevloc[curloc];
//            graph[nextloc][curloc] -= pathflow;
//            graph[curloc][nextloc] += pathflow;
//            curloc = nextloc;
//        }
//    }
//}
//
//int main(){
//    int N,M;
//    ifstream fin("ditch.in");
//    ofstream fout("ditch.out");
//    fin>>N>>M;
//    graph.resize(M);
//
//    {
//        int u,v,cap;
//        while(fin>>u>>v>>cap){
//            graph[u-1][v-1] += cap;
//        }
//    }
//
//    fout<<calmaxflow(graph,0,M-1)<<endl;
//    fin.close();
//    fout.close();
//
//    return 0;
//}

//===============================================================
// Heap (Priority Queue) 优化的最大流增广路实现

//#include<fstream>
//#include<vector>
//#include<map>
//#include<queue>
//#include<algorithm>
//using namespace std;
//
//const int infinity = 2100000000;
//vector< map<int,int> > graph;
//
//struct locflow{
//    int loc;
//    int flow;
//    locflow(){}
//    locflow(int Loc, int Flow):loc(Loc),flow(Flow){}
//    bool operator<(const locflow &comp)const{
//        return flow < comp.flow;
//    }
//};
//
//int augment(vector< map<int,int> > &graph, int src, int des){
//    vector<int> flow(graph.size());
//    vector<int> prevloc(graph.size());
//    vector<bool> visited(graph.size());
//    flow[src] = infinity;
//
//    priority_queue<locflow> pq;
//    pq.push(locflow(src,infinity));
//    while(!pq.empty()){
//        int maxloc = pq.top().loc;
//        int maxflow = pq.top().flow;
//        pq.pop();
//        if(visited[maxloc])continue;
//        if(maxloc == des)break;
//        visited[maxloc] = true;
//        for(map<int,int>::iterator itr=graph[maxloc].begin(); itr!=graph[maxloc].end(); ++itr)
//            if(flow[itr->first] < min(maxflow, itr->second)){
//                prevloc[itr->first] = maxloc;
//                flow[itr->first] = min(maxflow, itr->second);
//                pq.push(locflow(itr->first,flow[itr->first]));
//            }
//    }
//    if(flow[des] == 0)return 0;
//
//    int curloc = des;
//    while(curloc != src){
//        int nextloc = prevloc[curloc];
//        graph[nextloc][curloc] -= flow[des];
//        graph[curloc][nextloc] += flow[des];
//        curloc = nextloc;
//    }
//    return flow[des];
//}
//
//int main(){
//    int N,M,u,v,cap;
//    ifstream fin("ditch.in");
//    ofstream fout("ditch.out");
//    fin>>N>>M;
//    graph.resize(M);
//
//    while(fin>>u>>v>>cap){
//        graph[u-1][v-1] += cap;
//    }
//
//    int c, total = 0;
//    while(c = augment(graph, 0, M-1))total += c;
//    fout<<total<<endl;
//    fin.close();
//    fout.close();
//    return 0;
//}

//==============================================================
// Dinic 算法
// map<int,int> 存储图，适于稀疏的情况

//#include<fstream>
//#include<vector>
//#include<queue>
//#include<map>
//#include<list>
//using namespace std;
//
//const int infinity = 2100000000;
//
//int src, des;   // 源点与汇点
//
//vector< map<int,int> > Net; // 当前网络
//vector< list<int> > ADNet;  // 分层增量网络
//// list 表为此结点的出弧
//
//// 根据当前增量网络构建分层增量网络。
//// 若汇点 des 在网络中，返回 true；否则返回 false
//bool build(void){
//    ADNet.assign(Net.size(), list<int>());
//
//    // BFS 遍历当前网络
//    vector<bool> visited(Net.size());   // 访问标记
//    queue<int> Q;
//    Q.push(src);
//    while(!Q.empty()){
//        int curnode = Q.front();
//        Q.pop();
//        if(visited[curnode])continue;
//        visited[curnode] = true;
//
//        if(curnode == des)return true;  // 到达汇点
//        // 对所有相邻结点
//        for(map<int,int>::iterator itr=Net[curnode].begin(); itr!=Net[curnode].end(); ++itr)
//            if(!visited[itr->first] && itr->second > 0){
//                ADNet[curnode].push_back(itr->first);    // 当前结点添加到相邻结点的出弧
//                Q.push(itr->first);
//            }
//    }
//    return false;
//}
//
//// DFS 分层增量网络寻找增广路，修改当前网络，返回此路径流。
//int augment(int node, int flow = infinity){
//    if(0 == flow)return 0;
//    if(node == des)return flow;
//    for(list<int>::iterator itr=ADNet[node].begin(); itr!=ADNet[node].end();){
//        int augflow = augment(*itr, min(flow,Net[node][*itr]));
//        if(0 == augflow){
//            list<int>::iterator tmp = itr++;
//            ADNet[node].erase(tmp);
//            continue;
//        } else {
//            Net[node][*itr] -= augflow;
//            Net[*itr][node] += augflow;
//            return augflow;
//        }
//    }
//    return 0;
//}
//
//int main(){
//    int N,M,u,v,cap;
//    ifstream fin("ditch.in");
//    ofstream fout("ditch.out");
//    fin>>N>>M;
//    Net.resize(M);
//    src = 0;
//    des = M-1;
//
//    while(fin>>u>>v>>cap)
//        Net[u-1][v-1] += cap;
//
//    int c, total = 0;
//    while(build())
//        while(c = augment(src))total += c;
//    fout<<total<<endl;
//
//    fin.close();
//    fout.close();
//    return 0;
//}

//=========================================================================
// Dinic 算法
// 邻接矩阵 vector< vector<int> > 存储图，显式构造分层增量网络

//#include<fstream>
//#include<vector>
//#include<queue>
//#include<list>
//using namespace std;
//
//const int infinity = 2100000000;
//
//int src, des;   // 源点与汇点
//
//vector< vector<int> > Net; // 当前网络
//vector< list<int> > ADNet;  // 分层增量网络
//// list 表为此结点的出弧
//
//// 根据当前增量网络构建分层增量网络。
//// 若汇点 des 在网络中，返回 true；否则返回 false
//bool build(void){
//    ADNet.assign(Net.size(), list<int>());
//
//    // BFS 遍历当前网络
//    vector<bool> visited(Net.size());   // 访问标记
//    queue<int> Q;
//    Q.push(src);
//    while(!Q.empty()){
//        int curnode = Q.front();
//        Q.pop();
//        if(visited[curnode])continue;
//        visited[curnode] = true;
//
//        if(curnode == des)return true;  // 到达汇点
//        // 对所有相邻结点
//        for(vector<int>::size_type i=0; i<Net.size(); ++i)
//            if(!visited[i] && Net[curnode][i] > 0){
//                ADNet[curnode].push_back(i);    // 当前结点添加到相邻结点的出弧
//                Q.push(i);
//            }
//    }
//    return false;
//}
//
//// DFS 分层增量网络寻找增广路，修改当前网络，返回此路径流。
//int augment(int node, int flow = infinity){
//    if(0 == flow)return 0;
//    if(node == des)return flow;
//    for(list<int>::iterator itr=ADNet[node].begin(); itr!=ADNet[node].end();){
//        int augflow = augment(*itr, min(flow,Net[node][*itr]));
//        if(0 == augflow){
//            list<int>::iterator tmp = itr++;
//            ADNet[node].erase(tmp);
//            continue;
//        } else {
//            Net[node][*itr] -= augflow;
//            Net[*itr][node] += augflow;
//            return augflow;
//        }
//    }
//    return 0;
//}
//
//int main(){
//    int N,M,u,v,cap;
//    ifstream fin("ditch.in");
//    ofstream fout("ditch.out");
//    fin>>N>>M;
//    Net.resize(M, vector<int>(M, 0));
//    src = 0;
//    des = M-1;
//
//    while(fin>>u>>v>>cap)
//        Net[u-1][v-1] += cap;
//
//    int c, total = 0;
//    while(build())
//        while(c = augment(src))total += c;
//    fout<<total<<endl;
//
//    fin.close();
//    fout.close();
//    return 0;
//}

//=============================================================
// Dinic 算法，不显式构造分层增量网络，采用邻接表存储原始图
// 通常写法 递归实现

//#include<cstdio>
//#include<memory>
//using namespace std;
//const int infinity = 2100000000;
//const int MAXM = 1024;
//
//typedef struct Edge{
//    int vertex;
//    int capacity;
//    Edge *next;
//    Edge *back;
//    Edge(){}
//    Edge(int Vertex, int Capacity, Edge *Next)
//        :vertex(Vertex), capacity(Capacity), next(Next), back((Edge*)(NULL)){}
//    void* operator new(size_t, void *p){    // 重载 new 算符自己管理内存分配，效果很明显
//		return p;
//    }
//}*EdgeList;
//
//EdgeList Net[MAXM];     // 当前容量网络
//int Dist[MAXM];         // 各顶点距源点距离标号
//
//int src, des;           // 源点、汇点
//
//bool build(void){   // BFS 计算各顶点距离标号
//    memset(Dist, -1, sizeof(Dist));
//
//    int Q[MAXM], head = 0, tail = 0;    // 每顶点最多进队列一次，因此 MAXM 足够
//    Q[tail++] = src;
//    Dist[src] = 0;
//
//    while(head != tail){
//        int curnode = Q[head++];
//        if(curnode == des)return true;
//
//        for(EdgeList e = Net[curnode]; e; e = e->next)
//            if(e->capacity > 0 && -1 == Dist[e->vertex]){
//                Dist[e->vertex] = Dist[curnode] + 1;
//                Q[tail++] = e->vertex;
//            }
//    }
//    return false;
//}
//
//// 一遍 DFS 即可完成对当前分层图存在的全部路径的计算
//int augment(int curnode, int flow = infinity){
//    if(curnode == des)return flow;
//    if(0 == flow)return 0;
//
//    int augflow = 0;
//    for(EdgeList e = Net[curnode]; e; e = e->next)
//        if(e->capacity > 0 && Dist[curnode] + 1 == Dist[e->vertex]){
//            int branchflow = augment(e->vertex, min(flow - augflow, e->capacity));
//            augflow += branchflow;  // 注意，找到增广路后不返回。
//            e->capacity -= branchflow;
//            e->back->capacity += branchflow;
//        }
//    return augflow;
//}
//
//int main(){
//    int N, M, u, v, w;
//    FILE *fin = fopen("ditch.in", "r");
//    FILE *fout = fopen("ditch.out", "w");
//    fscanf(fin, "%d%d", &N, &M);
//    memset(Net, NULL, sizeof(Net));
//    Edge *data = new Edge[2*N];
//    src = 1;
//    des = M;
//
//    while(N--){
//        fscanf(fin, "%d%d%d", &u, &v, &w);
//        Net[u] = new((void*)data++) Edge(v, w, Net[u]);
//        Net[v] = new((void*)data++) Edge(u, 0, Net[v]);
//        Net[u]->back = Net[v];
//        Net[v]->back = Net[u];
//    }
//
//    int total = 0;
//    while(build())
//        total += augment(src);  // 每次 BFS 后只 DFS 一次即可
//    fprintf(fout, "%d\n", total);
//
//    fclose(fin);
//    fclose(fout);
//    return 0;
//}

//=============================================================
// Dinic 算法，不显式构造分层增量网络，采用邻接表存储原始图
// 稍作优化 递归实现 ---------> 将此定为 Dinic 标程。

//#include<cstdio>
//#include<memory>
//using namespace std;
//const int infinity = 2100000000;
//const int MAXM = 1024;
//
//typedef struct Edge{
//    int vertex;
//    int capacity;
//    Edge *next;
//    Edge *back;
//    Edge(){}
//    Edge(int Vertex, int Capacity, Edge *Next)
//        :vertex(Vertex), capacity(Capacity), next(Next), back((Edge*)(NULL)){}
//    void* operator new(size_t, void *p){    // 重载 new 算符自己管理内存分配，效果很明显
//        return p;
//    }
//}*EdgeList;
//
//EdgeList Net[MAXM];     // 当前容量网络
//int Dist[MAXM];         // 各顶点距源点距离标号
//int src, des;           // 源点、汇点
//
//bool build(void){   // BFS 计算各顶点距离标号
//    memset(Dist, -1, sizeof(Dist));
//
//    int Q[MAXM], head = 0, tail = 0;    // 每顶点最多进队列一次，因此 MAXM 足够
//    Q[tail++] = src;
//    Dist[src] = 0;
//
//    while(head != tail){
//        int curnode = Q[head++];
//        if(curnode == des)return true;
//
//        for(EdgeList e = Net[curnode]; e; e = e->next)
//            if(e->capacity > 0 && -1 == Dist[e->vertex]){
//                Dist[e->vertex] = Dist[curnode] + 1;
//                Q[tail++] = e->vertex;
//            }
//    }
//    return false;
//}
//
//// 一遍 DFS 即可完成对当前分层图存在的全部路径的计算
//int augment(int curnode, int flow = infinity){
//    if(curnode == des)return flow;
//
//    int augflow = 0, branchflow;
//    for(EdgeList e = Net[curnode]; e && flow; e = e->next)
//        if(e->capacity > 0 && Dist[curnode] + 1 == Dist[e->vertex]){
//            branchflow = augment(e->vertex, min(flow, e->capacity));
//            flow -= branchflow;
//            augflow += branchflow;  // 注意，找到增广路后不返回。
//            e->capacity -= branchflow;
//            e->back->capacity += branchflow;
//        }
//    return augflow;
//}
//
//int main(){
//    int N, M, u, v, w;
//    freopen("ditch.in", "r", stdin);
//    freopen("ditch.out", "w", stdout);
//    while(scanf("%d%d", &N, &M) != EOF){
//        memset(Net, NULL, sizeof(Net));
//        Edge *buffer = new Edge[2*N];
//        Edge *data = buffer;
//        src = 1;
//        des = M;
//
//        while(N--){
//            scanf("%d%d%d", &u, &v, &w);
//            Net[u] = new((void*)data++) Edge(v, w, Net[u]);
//            Net[v] = new((void*)data++) Edge(u, 0, Net[v]);
//            Net[u]->back = Net[v];
//            Net[v]->back = Net[u];
//        }
//
//        int total = 0;
//        while(build())
//            total += augment(src);  // 每次 BFS 后只 DFS 一次即可
//        printf("%d\n", total);
//        delete [] buffer;
//    }
//    return 0;
//}

//=============================================================
// Dinic 算法，不显式构造分层增量网络，采用邻接表存储原始图
// 极限优化 栈实现... 效率与递归几乎相同...

//#include<cstdio>
//#include<memory>
//using namespace std;
//const int infinity = 2100000000;
//const int MAXM = 1024;
//
//typedef struct Edge{
//    int vertex;
//    int capacity;
//    Edge *next;
//    Edge *back;
//    Edge(){}
//    Edge(int Vertex, int Capacity, Edge *Next)
//        :vertex(Vertex), capacity(Capacity), next(Next), back((Edge*)(NULL)){}
//    void* operator new(size_t, void *p){    // 重载 new 算符自己管理内存分配，效果很明显
//		return p;
//	}
//}*EdgeList;
//
//EdgeList Net[MAXM];             // 当前容量网络
//int Dist[MAXM];                 // 各顶点距源点距离标号
//int Q[MAXM], head, tail;        // 顶点队列
//EdgeList *EdgeS;                // DFS 边栈
//struct {
//    int inflow;
//    int augflow;
//}FLOW[MAXM];                    // 流栈
//int Etop, Ftop;                 // 栈顶指标
//
//int src, des;       // 源点、汇点
//
//bool build(void){   // BFS 计算各顶点距离标号
//    memset(Dist, -1, sizeof(Dist));
//
//    head = tail = 0;
//    Q[tail++] = src;
//    Dist[src] = 0;
//
//    while(head != tail){
//        int curnode = Q[head++];
//        if(curnode == des)return true;
//
//        for(EdgeList e = Net[curnode]; e; e = e->next)
//            if(e->capacity > 0 && -1 == Dist[e->vertex]){
//                Dist[e->vertex] = Dist[curnode] + 1;
//                Q[tail++] = e->vertex;
//            }
//    }
//    return false;
//}
//
//int augment(void){
//    int depth = 0;  // 记录上条边的深度，判断回溯
//    Etop = Ftop = 0;
//    for(EdgeList e=Net[src]; e; e=e->next)
//        if(e->capacity > 0)
//            EdgeS[Etop++] = e;
//    FLOW[Ftop].inflow = infinity;
//    FLOW[Ftop].augflow = 0;
//
//    while(Etop){
//        Edge *e = EdgeS[Etop-1];
//        if(Dist[e->vertex] > depth){        // 下层
//            FLOW[Ftop+1].inflow = min(FLOW[Ftop].inflow - FLOW[Ftop].augflow, e->capacity);
//            FLOW[++Ftop].augflow = 0;
//            depth = Dist[e->vertex];
//        } else if(Dist[e->vertex] < depth){ // 回溯
//            --Ftop;--Etop;
//            e->capacity -= FLOW[Ftop].augflow;
//            e->back->capacity += FLOW[Ftop].augflow;
//            FLOW[Ftop-1].augflow += FLOW[Ftop].augflow;
//            depth = Dist[e->vertex];
//            continue;
//        } else {                            // 同层
//            FLOW[Ftop].inflow = min(FLOW[Ftop-1].inflow - FLOW[Ftop-1].augflow, e->capacity);
//            FLOW[Ftop].augflow = 0;
//        }
//
//        if(e->vertex == des){
//            e->capacity -= FLOW[Ftop].inflow;
//            e->back->capacity += FLOW[Ftop].inflow;
//            FLOW[Ftop-1].augflow += FLOW[Ftop].inflow;
//            --Etop; // 不需下层递进，当前边直接退栈
//            continue;
//        }
//        bool endnode = true;
//        for(Edge *ce = Net[e->vertex]; ce; ce=ce->next)
//            if(ce->capacity > 0 && Dist[e->vertex] + 1 == Dist[ce->vertex]){
//                endnode = false;
//                EdgeS[Etop++] = ce;
//            }
//        if(endnode){
//            --Etop;
//        }
//    }
//    return FLOW[0].augflow;
//}
//
//int main(){
//    int N, M, u, v, w;
//    FILE *fin = fopen("ditch.in", "r");
//    FILE *fout = fopen("ditch.out", "w");
//    fscanf(fin, "%d%d", &N, &M);
//    memset(Net, NULL, sizeof(Net));
//    Edge *data = new Edge[2*N];
//    EdgeS = new EdgeList[N];
//    src = 1;
//    des = M;
//
//    while(N--){
//        fscanf(fin, "%d%d%d", &u, &v, &w);
//        Net[u] = new((void*)data++) Edge(v, w, Net[u]);
//        Net[v] = new((void*)data++) Edge(u, 0, Net[v]);
//        Net[u]->back = Net[v];
//        Net[v]->back = Net[u];
//    }
//
//    int total = 0;
//    while(build())
//        total += augment();
//    fprintf(fout, "%d\n", total);
//
//    fclose(fin);
//    fclose(fout);
//    return 0;
//}

//============================================================
// DD_engi 的程序，效率非常高。研究一下，呵呵

//#include <cstdio>
//#include <cstring>
//#include <climits>
//using namespace std;
//
//const int maxn=1024,OO=1000000000;
//struct edge{
//	int x,y;//两个顶点 
//	int c;//容量 
//	int f;
//	edge *next,*back;
//	edge(){}
//	edge(int x,int y,int c,edge* next):x(x),y(y),c(c),f(0),next(next),back(0){}
//	void* operator new(size_t, void *p){
//		return p;
//	}
//}*E[maxn];
//int N,S,T;
//
//int Q[maxn];
//int D[maxn];
//void BFS()
//{
//    memset(D,-1,sizeof(D));
//    int head=0,tail=0;
//    Q[tail++]=S;
//    D[S]=0;
//    for(;;){
//        int i=Q[head++];
//        for(edge* e=E[i];e;e=e->next){
//            if(e->c==0)continue;
//            int j=e->y;
//            if(D[j]==-1){
//                D[j]=D[i]+1;
//                Q[tail++]=j;
//                if(j==T)return;
//            }
//        }
//        if(head==tail)break;
//    }
//}
//edge* cur[maxn];
//edge* path[maxn];
//int flow()
//{
//    int res=0;
//    int path_n;
//    for(;;){
//        BFS();
//        if(D[T]==-1)break;
//        memcpy(cur,E,sizeof(E));
//        path_n=0;
//        int i=S;
//        for(;;){
//            if(i==T){
//                int mink=0;
//                int delta=INT_MAX;
//                for(int k=0;k<path_n;++k){
//                    if(path[k]->c < delta){
//                        delta = path[k]->c;
//                        mink=k;
//                    }
//                }
//                for(int k=0;k<path_n;++k){
//                    path[k]->c -= delta;
//                    path[k]->back->c += delta;
//                }
//                path_n=mink;
//                i=path[path_n]->x;
//                res+=delta;
//            }
//            edge* e;
//            for(e=cur[i];e;e=e->next){
//                if(e->c==0)continue;
//                int j=e->y;
//                if(D[i]+1==D[j])break;
//            }
//            cur[i]=e;
//            if(e){
//                path[path_n++]=e;
//                i=e->y;
//            }
//            else{
//                D[i]=-1;
//                if(path_n==0)break;
//                path_n--;
//                i=path[path_n]->x;
//            }
//        }
//    }
//    return res;
//}
//void input(){
//	int m;
//	scanf("%d%d",&m,&N);
//	memset(E,0,sizeof(E));
//	edge* data=new edge[2*m];
//	while(m--){
//		int x,y,w;
//		scanf("%d%d%d",&x,&y,&w);
//		E[x]=new((void*)data++) edge(x,y,w,E[x]);
//		E[y]=new((void*)data++) edge(y,x,0,E[y]);
//		E[x]->back = E[y];
//		E[y]->back = E[x];
//	}
//	S=1;
//	T=N;
//}
//int main(){
//	freopen("ditch.in","r",stdin);
//	freopen("ditch.out","w",stdout);
//	input();
//	int res=flow();
//	printf("%d\n",res);
//}

//============================================================
// Improved SAP algorithm
// 加不加 BFS 效率相差 5% 左右，代码量 15 行左右。自己把握吧
// 在递归版本中加 GAP 剪枝写起来不好看，好几个地方都要判断。
// 经实验，GAP 剪枝效果非常明显，一定要加
// 而在非递归版本中只是一句 break 的问题。

//#include<cstdio>
//#include<memory>
//using namespace std;
//
//const int infinity = 2100000000;
//const int maxnode = 2008;
//
//struct edge{
//    int ver;    // arc: xxx --> ver
//    int cap;    // Capacity
//    int flow;   // Current flow in this arc
//    edge *next; // out arcs list
//    edge *rev;  // pointer to the reverse arc
//    edge(){}
//    edge(int Vertex, int Capacity, edge *Next)
//        :ver(Vertex),cap(Capacity),flow(0),next(Next),rev((edge*)NULL){}
//    void* operator new(size_t, void *p){
//        return p;
//    }
//}*Net[maxnode];
//int Dist[maxnode], numbs[maxnode] = {0}, src, des, n;
//
//void rev_BFS(){
//    int Q[maxnode], head = 0, tail = 0;
//    for(int i=1; i<=n; ++i)
//        Dist[i] = maxnode;
//    Q[tail++] = des;
//    Dist[des] = 0;
//    numbs[0] = 1;
//    while(head != tail){
//        int v = Q[head++];
//        for(edge *e = Net[v]; e; e = e->next){
//            if(e->rev->cap == 0 || Dist[e->ver] < maxnode)continue;
//            Dist[e->ver] = Dist[v] + 1;
//            numbs[Dist[e->ver]]++;
//            Q[tail++] = e->ver;
//        }
//    }
//}
//
////bool gap = true;
//int augment(int node, int flow = infinity){
//    if(node == des)return flow;
//
//    int augflow = 0, branchflow;
//    bool endnode = true;
//    for(edge *e = Net[node]; e && flow /*&& gap*/; e = e->next){
//        if(e->cap == 0 || Dist[node] != Dist[e->ver] + 1)continue;
//        endnode = false;
//        branchflow = augment(e->ver, min(flow, e->cap));
//        augflow += branchflow;
//        flow -= branchflow;
//        e->cap -= branchflow;
//        e->rev->cap += branchflow;
//        e->flow += branchflow;
//        e->rev->flow -= branchflow;
//    }
//    if(endnode){
//        if(--numbs[Dist[node]]){
//            int mind = n;
//            for(edge *e = Net[node]; e; e = e->next)
//                if(e->cap > 0)mind = min(mind, Dist[e->ver]);
//            Dist[node] = mind + 1;
//            numbs[mind + 1]++;
//        } else
//            /*gap = false*/;
//    }
//    return augflow;
//}
//
//int main(){
//    int m, u, v, w;
//    freopen("ditch.in", "r", stdin);
//    freopen("ditch.out", "w", stdout);
//    while(scanf("%d%d", &m, &n) != EOF){
//        memset(Net, 0, sizeof(Net));
//        edge *buffer = new edge[2*m];
//        edge *data = buffer;
//        src = 1;
//        des = n;
//
//        while(m--){
//            scanf("%d%d%d", &u, &v, &w);
//            Net[u] = new((void*)data++) edge(v, w, Net[u]);
//            Net[v] = new((void*)data++) edge(u, 0, Net[v]);
//            Net[u]->rev = Net[v];
//            Net[v]->rev = Net[u];
//        }
//        //rev_BFS();
//
//        int total = 0;
//        while(Dist[src] < n /*&& gap*/)
//            total += augment(src);
//        printf("%d\n", total);
//        delete [] buffer;
//    }
//    return 0;
//}

//===============================================================
// Improved SAP 非递归 + GAP，可作为 ISAP 标程

//#include<cstdio>
//#include<new>
//#include<algorithm>
//using namespace std;
//
//const int maxnode = 1024;
//const int infinity = 2100000000;
//
//struct edge{
//    int ver;    // vertex
//    int cap;    // capacity
//    int flow;   // current flow in this arc
//    edge *next; // next arc
//    edge *rev;  // reverse arc
//    edge(){}
//    edge(int Vertex, int Capacity, edge *Next)
//        :ver(Vertex), cap(Capacity), flow(0), next(Next), rev((edge*)NULL){}
//}*Net[maxnode];
//int dist[maxnode]= {0}, numbs[maxnode] = {0}, src, des, n;
//
//void rev_BFS(){
//    int Q[maxnode], head = 0, tail = 0;
//    for(int i=1; i<=n; ++i){
//        dist[i] = maxnode;
//        numbs[i] = 0;
//    }
//
//    Q[tail++] = des;
//    dist[des] = 0;
//    numbs[0] = 1;
//    while(head != tail){
//        int v = Q[head++];
//        for(edge *e = Net[v]; e; e = e->next){
//            if(e->rev->cap == 0 || dist[e->ver] < maxnode)continue;
//            dist[e->ver] = dist[v] + 1;
//            ++numbs[dist[e->ver]];
//            Q[tail++] = e->ver;
//        }
//    }
//}
//
//int maxflow(){
//    int u, totalflow = 0;
//    edge *CurEdge[maxnode], *revpath[maxnode];
//    for(int i=1; i<=n; ++i)CurEdge[i] = Net[i];
//    u = src;
//    while(dist[src] < n){
//        if(u == des){
//            int augflow = infinity;
//            for(int i = src; i != des; i = CurEdge[i]->ver)
//                augflow = min(augflow, CurEdge[i]->cap);
//            for(int i = src; i != des; i = CurEdge[i]->ver){
//                CurEdge[i]->cap -= augflow;
//                CurEdge[i]->rev->cap += augflow;
//                CurEdge[i]->flow += augflow;
//                CurEdge[i]->rev->flow -= augflow;
//            }
//            totalflow += augflow;
//            u = src;
//        }
//
//        edge *e;
//        for(e = CurEdge[u]; e; e = e->next)
//            if(e->cap > 0 && dist[u] == dist[e->ver] + 1)break;
//        if(e){
//            CurEdge[u] = e;
//            revpath[e->ver] = e->rev;
//            u = e->ver;
//        } else {
//            if(0 == (--numbs[dist[u]]))break;
//            CurEdge[u] = Net[u];
//            int mindist = n;
//            for(edge *te = Net[u]; te; te = te->next)
//                if(te->cap > 0)mindist = min(mindist, dist[te->ver]);
//            dist[u] = mindist + 1;
//            ++numbs[dist[u]];
//            if(u != src)
//                u = revpath[u]->ver;
//        }
//    }
//    return totalflow;
//}
//
//int main(){
//    int m, u, v, w;
//    freopen("ditch.in", "r", stdin);
//    freopen("ditch.out", "w", stdout);
//    while(scanf("%d%d", &m, &n) != EOF){
//        edge *buffer = new edge[2*m];
//        edge *data = buffer;
//        src = 1; des = n;
//        while(m--){
//            scanf("%d%d%d", &u, &v, &w);
//            Net[u] = new((void*) data++) edge(v, w, Net[u]);
//            Net[v] = new((void*) data++) edge(u, 0, Net[v]);
//            Net[u]->rev = Net[v];
//            Net[v]->rev = Net[u];
//        }
//        rev_BFS();
//        printf("%d\n", maxflow());
//        delete [] buffer;
//    }
//}

//////////////////////////////////////////////////////////////////////////
// 深度优先寻找增广路，试试简短程序的效率。
// 模式一：每遍dfs只找一条路增广。

#include<cstdio>
#include<new>
#include<algorithm>
using namespace std;

const int maxnode = 1024;
const int infinity = 2100000000;

struct edge{
    int ver;    // vertex
    int cap;    // capacity
    int flow;   // current flow in this arc
    edge *next; // next arc
    edge *rev;  // reverse arc
    edge(){}
    edge(int Vertex, int Capacity, edge *Next)
        :ver(Vertex), cap(Capacity), flow(0), next(Next), rev((edge*)NULL){}
}*Net[maxnode];
int src, des, n;
bool visited[maxnode];

int dfs(int ver = src, int flow = infinity){
    if(ver == des)return flow;
    visited[ver] = true;
    for(edge* e = Net[ver]; e; e = e->next)if(!visited[e->ver] && e->cap > 0){
        int augflow = dfs(e->ver, min(flow, e->cap));
        if(augflow > 0){
            e->cap -= augflow;
            e->rev->cap += augflow;
            e->flow += augflow;
            e->rev->flow -= augflow;
            return augflow;
        }
    }
    return 0;
}

int maxflow(){
    int augflow, totalflow = 0;
    memset(visited, 0, sizeof(visited));
    while(augflow = dfs()){
        totalflow += augflow;
        memset(visited, 0, sizeof(visited));
    }
    return totalflow;
}

int main(){
    int m, u, v, w;
    freopen("ditch.in", "r", stdin);
    freopen("ditch.out", "w", stdout);
    while(scanf("%d%d", &m, &n) != EOF){
        edge *buffer = new edge[2*m];
        edge *data = buffer;
        src = 1; des = n;
        while(m--){
            scanf("%d%d%d", &u, &v, &w);
            Net[u] = new((void*) data++) edge(v, w, Net[u]);
            Net[v] = new((void*) data++) edge(u, 0, Net[v]);
            Net[u]->rev = Net[v];
            Net[v]->rev = Net[u];
        }
        printf("%d\n", maxflow());
        delete [] buffer;
    }
}