#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<algorithm>
using namespace std;

int ddx[105][1500];
int ps1[105][1500];
int ddx_sz[105];
int ps1_sz[105];

struct bar{
    int y;
    int xl, xr;
    bar(){}
    bar(int Y, int XL, int XR): y(Y), xl(XL), xr(XR){}

    bool operator<(const bar &r) const {
        return y < r.y;
    }
};

bar bars[1005]; // x i, y j
int bars_sz;

int N, M, K;

void input(){
    // init
    memset(ddx, 0, sizeof(ddx));
    memset(ps1, 0, sizeof(ps1));
    memset(ddx_sz, 0, sizeof(ddx_sz));
    memset(ps1_sz, 0, sizeof(ps1_sz));
    //memset(bars, 0, sizeof(bars));
    bars_sz = 0;

    // read
    scanf("%d%d%d", &N, &M, &K);
    for(int i=0; i<M; ++i){
        int xl, xr, y;
        scanf("%d%d%d", &xl, &xr, &y);
        bars[bars_sz++] = bar(y, xl, xr);
    }
}

int walkdn(int pos){
    int y = 1000001;
    for(int i=bars_sz-1; i>=0; --i){
        if(pos == bars[i].xl){
            ddx[pos][ddx_sz[pos]++] = y;
            ddx[pos][ddx_sz[pos]++] = bars[i].y;
            pos = bars[i].xr;
            y = bars[i].y;
        } else if(pos == bars[i].xr) {
            ddx[pos][ddx_sz[pos]++] = y;
            ddx[pos][ddx_sz[pos]++] = bars[i].y;
            pos = bars[i].xl;
            y = bars[i].y;
        }
    }
    return pos;
}

int walkup(int pos){
    int y = 0;
    for(int i=0; i<bars_sz; ++i){
        if(pos == bars[i].xl){
            ps1[pos][ps1_sz[pos]++] = y;
            ps1[pos][ps1_sz[pos]++] = bars[i].y;
            pos = bars[i].xr;
            y = bars[i].y;
        } else if(pos == bars[i].xr) {
            ps1[pos][ps1_sz[pos]++] = y;
            ps1[pos][ps1_sz[pos]++] = bars[i].y;
            pos = bars[i].xl;
            y = bars[i].y;
        }
    }
    return pos;
}

bool calc(){
    // sort
    sort(bars, bars+bars_sz);

    // walk
    int kk = walkdn(K);
    if(kk == 1 || kk == 2) return true;

    int II = walkup(1);
    if(abs(II - K) == 1) return true;

    // calc

    return false;
}

int main(){
    freopen("i.txt", "r", stdin);
    freopen("o.txt", "w", stdout);

    int T;
    scanf("%d", &T);
    while(T--){
        input();
        printf(calc()? "Yes\n" : "No\n");
    }

    return 0;
}
