#include<cstdio>
#include<algorithm>

using namespace std;

int milks[10003], N;

bool input(){
    if(scanf("%d", &N) == EOF)return false;
    for(int i=0; i<N; ++i) scanf("%d", milks+i);
    return true;
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("i.txt", "r", stdin);
    freopen("o.txt", "w", stdout);
#endif
    while(input()){
        nth_element(milks, milks+N/2, milks+N);
        printf("%d\n", milks[N/2]);
    }
}
