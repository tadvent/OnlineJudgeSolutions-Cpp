#include<cstdio>
#include<utility>
#include<algorithm>
using namespace std;

struct stu{
    int pro, time, sco, rank;
};

stu scs[102];
stu *pscs[102];
int cnt[6], N;

inline bool pstucmp(const stu *l, const stu *r){
    return l->time < r->time;
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("i.txt", "r", stdin);
    freopen("o.txt", "w", stdout);
#endif
    while(scanf("%d", &N) && N>0){
        for(int i=0; i<N; ++i){
            int h, m, s;
            scanf("%d%d:%d:%d", &scs[i].pro, &h, &m, &s);
            scs[i].time = h*3600 + m * 60 + s;
            scs[i].sco = 50 + 10*scs[i].pro;
            pscs[i] = scs + i;
        }
        sort(pscs, pscs+N, pstucmp);
        memset(cnt, 0, sizeof(cnt));
        for(int i=0; i<N; ++i)
            pscs[i]->rank = ++cnt[pscs[i]->pro];
        for(int i=0; i<N; ++i){
            if(scs[i].pro>0 && scs[i].pro<5 && scs[i].rank * 2 <= cnt[scs[i].pro])
                scs[i].sco += 5;
            printf("%d\n", scs[i].sco);
        }
        putchar('\n');
    }
}
