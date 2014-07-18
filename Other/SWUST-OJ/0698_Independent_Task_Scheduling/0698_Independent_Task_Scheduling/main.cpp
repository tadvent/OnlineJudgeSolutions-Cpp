#include<cstdio>
#include<utility>
#include<vector>
#include<climits>

int N, Ta[201], Tb[201], SumA;

bool input(){
    if(scanf("%d", &N) != 1 || !N) return false;
    SumA = 0;
    for(int i=0; i<N; ++i){
        scanf("%d", Ta+i);
        SumA += Ta[i];
    }
    for(int i=0; i<N; ++i)
        scanf("%d", Tb+i);
    return true;
}

int calc(){
    std::vector<int> tb1(SumA + 1);
    std::vector<int> tb2(SumA + 1);
    for(int i=0; i<N; ++i){
        int ta;
        for(ta=0; ta<Ta[i]; ++ta)
            tb2[ta] = tb1[ta] + Tb[i];
        for(; ta<=SumA; ++ta)
            if(
                (tb2[ta] = std::min(tb1[ta-Ta[i]], tb1[ta]+Tb[i])) == 0
            ) break;
        std::swap(tb1, tb2);
    }

    int minTime = INT_MAX;
    for(int ta=0; ta<=SumA; ++ta)
        minTime = std::min(minTime, std::max(ta, tb1[ta]));
    return minTime;
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("i.txt", "r", stdin);
    freopen("o.txt", "w", stdout);
#endif
    while(input())
        printf("%d\n", calc());
}
