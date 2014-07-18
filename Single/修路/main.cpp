/************************************************/
/* 蒙特卡洛。。。随机问题随机模拟 = =
// 看样子不够精确。。。标准结果接近整数时，容易造成在相邻两整数间的摇摆

#include<cstdio>
#include<cstdlib>
#include<cassert>
#include<ctime>
#include<algorithm>
#include<vector>
using namespace std;

const int MAX_N = 35;
struct GLOBAL_INIT{
    GLOBAL_INIT(){
        srand((unsigned)time(NULL));
    }
};
GLOBAL_INIT global_init;

////////// union_sets ///////////
class union_sets{
    vector<int> belong;
public:
    void init(int n){
        belong.resize(n);
        for(int i=0; i<n; ++i) belong[i] = i;
    }
    int gid(const int x){
        int grpid = x;
        while(belong[grpid] != grpid)
            grpid = belong[grpid];
        return belong[x] = grpid;
    }
    bool link(int x, int y){
        // true if x,y turned into same group
        // false if x,y already in same group before
        int idx = gid(x);
        int idy = gid(y);
        if(idx < idy){
            belong[idy] = idx;
            return true;
        } else if(idx > idy){
            belong[idx] = idy;
            return true;
        }
        return false;
    }
};

////////// get random edge  ////////////
class rand_edge{
    int nEdges;
    vector<int> edges;
    int myrand(const int upper) const {
        return int((double)rand()/(RAND_MAX+1) * upper);
    }
    int e2i(const int x, const int y) const {
        return x*MAX_N + y;
    }
    void i2e(const int i, int &x, int &y) const {
        y = i % MAX_N;
        x = i / MAX_N;
    }
public:
    void init(int nVex){
        assert(nVex < MAX_N);
        nEdges = nVex*(nVex-1)/2;
        edges.clear();
        edges.reserve(nEdges);
        for(int x=0; x<nVex; ++x)for(int y=x+1; y<nVex; ++y)
            edges.push_back(e2i(x,y));
        assert(edges.size() == nEdges);
    }
    bool getEdge(int &x, int &y){
        if(edges.size() == 0) return false;
        int pos = myrand(edges.size());
        i2e(edges[pos], x, y);
        swap(edges[pos], edges.back());
        edges.pop_back();
        return true;
    }
};

//////////////////////////////////////////
int take_exp(int n){
    // init experiment
    union_sets us;
    rand_edge re;
    us.init(n);
    re.init(n);

    int cnt = 0, nSet = n, x, y;
    while(re.getEdge(x, y)){
        ++cnt;
        if(us.link(x, y)){
            if(--nSet == 1) break;
        }
    }
    return cnt;
}


double calculate(int n){
    int total_edge = 0;
    const int total_exp = 1000000;
    int t = total_exp;
    while(t--){
        total_edge += take_exp(n);
    }
    return (double)total_edge / total_exp + 1e-7;
}

int main(){
    int n;
    for(;;){
        scanf("%d", &n);
        if(n <= 0 || n > 30) break;
        for(int i=0; i<10; ++i){
            printf("%f  ", calculate(n));
        }
        putchar('\n');
    }
}


/************************************************/
//* 寻找解析解好了
//

#include<cassert>
#include<cstdio>
#include<cstdlib>
#include<algorithm>
using namespace std;

// Utilities /////////////////////////////////////
class Combination{
    double _c[450][450];
public:
    Combination(){
        for(int i=0; i<450; ++i)for(int j=0; j<450; ++j)
            _c[i][j] = -1;
    }
    double operator()(int ttl, int sel){
        assert(ttl >= 0 && ttl < 450);
        assert(sel >= 0 && sel < 450);
        if(_c[ttl][sel] > -1e-7) return _c[ttl][sel];
        if(ttl == sel) return _c[ttl][sel] = 1;
        if(ttl < sel) return _c[ttl][sel] = 0;
        if(sel > ttl/2) sel = ttl - sel;
        double r = 1;
        while(sel > 0){
            r *= double(ttl--) / sel--;
        }
        return _c[ttl][sel] = r;
    }
};
Combination C;

class EdgeNumOfVertices{
    int _e[35];   // number of edges among n vertices
public:
    EdgeNumOfVertices(){
        _e[0] = 0;
        for(int i=1; i<sizeof(_e)/sizeof(_e[0]); ++i) _e[i] = i*(i-1)/2;
    }
    int operator[](int n) const {
        assert(n > 0 && n < 35);
        return _e[n];
    }
};
EdgeNumOfVertices eov;

// 在 n1 和 n2 两组共 n 个点中，任意划 d 条边，其中有 d1 条落入 n1 内且 d2 条落入 n2 内的概率
inline double pd(int n1, int n2, int d1, int d2){
    return C(eov[n1], d1) * C(eov[n2], d2) / C(eov[n1+n2], d1+d2);
}

// Calculation ///////////////////////////////////

double _p[35][450];   // n 个点中，任意连边，第 k 条边刚好全连通的概率为 p(n,k)
double _pp[35][450];  // n 个点中，任意连够 m 条边后，能够全连通的概率为 pp(n,m)
void calcInit(){
    for(int i=0; i<35; ++i)for(int j=0; j<450; ++j)
        _p[i][j] = _pp[i][j] = -1;
    for(int i=0; i<35; ++i)
        _p[0][i] = _p[1][i] = _p[2][i] = 0;
    _p[0][0] = _p[1][0] = _p[2][1] = 1;
}

double p(int n, int k);
double pp(int n, int m){    // pp(n, m)
    assert(n > 0 && n < 35 && m >= 0 && m < 450);
    if(_pp[n][m] > -1e-7) return _pp[n][m];
    if(m > eov[n]) return _pp[n][m] = 0;
    double r = 0;
    for(int i=0; i<=m; ++i) r += p(n, i);
    return _pp[n][m] = r;
}

double ps(int n1, int n2, int d){
    // 在 n (=n1+n2) 个点中，任意加入 d 条边，使得 n1 n2 成为两个连通子集的概率
    double r = 0;
    int lim = min(eov[n1], d);
    for(int d1=0; d1<=lim; ++d1){
        r += pd(n1, n2, d1, d-d1) * pp(n1, d1) * pp(n2, d-d1);
    }
    r *= C(n1+n2, n1);
    if(n1 == n2) r /= 2;
    return r;
}

double p(int n, int k){
    assert(n > 0 && n < 35 && k >= 0 && k < 450);
    if(_p[n][k] > -1e-7) return _p[n][k];
    double r = 0;
    for(int n1 = 1; n1 <= n/2; ++n1){
        r += ps(n1, n-n1, k-1) * n1 * (n-n1) / (eov[n] - k + 1);
    }
    return _p[n][k] = r;
}

struct GLOBAL_INIT{
    GLOBAL_INIT(){
        calcInit();
    }
};
GLOBAL_INIT globalInit;

double calc(int n){
    double r = 0;
    for(int e = 1; e <= eov[n]; ++e){
        r += e * p(n, e);
    }
    return r;
}

int calculate(int n){
    return int(calc(n) + 1e-7);
}

int main(){
    for(int i=1; i<=30; ++i){
        printf("%2d: %d\n", i, calculate(i));
    }
    system("pause");
}

/************************************************/