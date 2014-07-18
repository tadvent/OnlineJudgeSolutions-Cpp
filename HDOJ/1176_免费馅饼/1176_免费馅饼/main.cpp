#include<cstdio>
#include<utility>
#include<algorithm>
using namespace std;

pair<int, int> pie[100002];
int pie_sz, maxlayer;

bool input(){
    if(scanf("%d", &pie_sz) == EOF || pie_sz == 0)
        return false;
    for(int i=0; i<pie_sz; ++i){
        scanf("%d %d", &pie[i].second, &pie[i].first);
        if(pie[i].first > maxlayer)maxlayer = pie[i].first;
    }
    return true;
}

void fillayer(int *sc, int *nsc, int layer, int &idx){
    fill_n(nsc, 13, 0);
    while(idx >= 0 && pie[idx].first == layer){
        ++nsc[pie[idx].second+1];
        --idx;
    }
    for(int i=1; i<=11; ++i){
        int maxsc = max(sc[i-1], sc[i]);
        maxsc = max(maxsc, sc[i+1]);
        nsc[i] += maxsc;
    }
}

int calc(){
    int buf1[13] = {0}, buf2[13];
    int *sc, *nsc, idx = pie_sz-1;

    sc = buf1;
    nsc = buf2;
    sort(pie, pie+pie_sz);
    for(int layer = maxlayer; layer >= 0; --layer){
        fillayer(sc, nsc, layer, idx);
        swap(sc, nsc);
    }
    return sc[6];
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("i.txt", "r", stdin);
    freopen("o.txt", "w", stdout);
#endif
    while(input())
        printf("%d\n", calc());
}
