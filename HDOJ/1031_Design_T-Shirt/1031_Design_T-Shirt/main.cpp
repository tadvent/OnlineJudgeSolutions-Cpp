#include<cstdio>
#include<cmath>
#include<vector>
#include<algorithm>
#include<functional>
using namespace std;

int K;
vector<double> sat;
inline bool idxcmp(int idx1, int idx2){
    return (sat[idx1] > sat[idx2] + 1e-8 ||
        fabs(sat[idx1] - sat[idx2]) < 1e-8 && idx1 < idx2);
}

bool input(){
    int n, m;
    if(scanf("%d%d%d", &n, &m, &K) == EOF)return false;
    sat.assign(m, 0.0);
    while(n--){
        double s;
        for(int i=0; i<m; ++i){
            scanf("%lf", &s);
            sat[i] += s;
        }
    }
    return true;
}

void output(){
    vector<int> idxs;
    idxs.resize(sat.size());
    for(int i=0; i<(int)idxs.size(); ++i)idxs[i] = i;
    nth_element(idxs.begin(),idxs.begin()+K-1 , idxs.end(), idxcmp);
    sort(idxs.begin(), idxs.begin()+K, greater<int>());
    printf("%d", idxs.front()+1);
    for(int i=1; i<K; ++i)printf(" %d", idxs[i]+1);
    putchar('\n');
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("i.txt", "r", stdin);
    freopen("o.txt", "w", stdout);
#endif

    while(input())output();
}

