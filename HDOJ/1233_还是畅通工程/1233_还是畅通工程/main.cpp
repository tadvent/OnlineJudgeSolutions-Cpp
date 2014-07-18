//prim + heap  109ms
#include<cstdio>
#include<climits>
#include<cstring>
#include<algorithm>
#include<functional>
using namespace std;
const int maxN = 101;

int matrix[maxN][maxN], N;

bool input(){
    int i, j, d, cnt;
    if(scanf("%d", &N) == EOF || !N)return false;
    for(i=1; i<=N; ++i)for(j=1; j<=N; ++j)
        matrix[i][j] = INT_MAX;
    cnt = N*(N-1)/2;
    while(cnt--){
        scanf("%d%d%d", &i, &j, &d);
        if(d < matrix[i][j])
            matrix[i][j] = matrix[j][i] = d;
    }
    return true;
}

int prim(){
    int d[maxN], inset[maxN] = {0}, setn = 0, hpn = 0, msum = 0;
    pair<int, int> heap[maxN*(maxN-1)/2]; // <dist, ver>
    greater<pair<int, int> > gt;

    for(int i=1; i<=N; ++i)d[i] = INT_MAX;
    heap[hpn++] = make_pair(0, 1);
    while(setn < N){
        if(hpn <= 0)return INT_MAX;
        pair<int, int> top = heap[0];
        pop_heap(heap, heap + hpn--, gt);
        if(inset[top.second])continue;
        inset[top.second] = 1;
        ++setn;
        msum += top.first;

        for(int i=1; i<=N; ++i)if(!inset[i] && matrix[top.second][i] < d[i]){
            d[i] = matrix[top.second][i];
            heap[hpn] = make_pair(d[i], i);
            push_heap(heap, heap + (++hpn), gt);
        }
    }
    return msum;
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("i.txt", "r", stdin);
    freopen("o.txt", "w", stdout);
#endif
    while(input())printf("%d\n", prim());
}

//////////////////////////////////////////////////////////////////
// Kruskal : 218ms slower than prim+heap
/*
#include<cstdio>
#include<climits>
#include<algorithm>
using namespace std;
const int maxN = 101;

pair<int, pair<int,int> > edges[maxN*(maxN-1)/2]; // d, <i, j>
int nedge, N;

bool input(){
    int i, j, d;
    if(scanf("%d", &N) == EOF || !N)return false;
    nedge = N*(N-1)/2;
    for(int ii=0; ii<nedge; ++ii){
        scanf("%d%d%d", &i, &j, &d);
        edges[ii] = make_pair(d, make_pair(i,j));
    }
    return true;
}

int kruskal(){
    int msum = 0, setid[maxN], finaledge = 0, i;
    sort(edges, edges+nedge);

    for(i=1; i<=N; ++i)setid[i] = i;
    for(i=0; i<nedge && finaledge<N-1; ++i){
        int &fr = edges[i].second.first, &to = edges[i].second.second;
        int idf = fr, idt = to;
        while(idf != setid[idf])idf = setid[idf];
        while(idt != setid[idt])idt = setid[idt];
        if(idf == idt)continue;
        msum += edges[i].first;
        ++finaledge;

        int up, lo;
        if(idf < idt){
            for(up=to, lo=setid[to]; up != idf; up=lo, lo=setid[lo])
                setid[up] = idf;
        } else { // idf > idt
            for(up=fr, lo=setid[fr]; up != idt; up=lo, lo=setid[lo])
                setid[up] = idt;
        }
    }
    if(finaledge == N-1)return msum;
    else return INT_MAX;
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("i.txt", "r", stdin);
    freopen("o.txt", "w", stdout);
#endif
    while(input())printf("%d\n", kruskal());
}
*/
