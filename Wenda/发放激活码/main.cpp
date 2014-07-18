#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;

int N, C;
int a[105];
int buf[2][6000];
int *prv, *nxt;

void case_input(){
    scanf("%d%d", &N, &C);
    scanf("%d", &a[0]);
    for(int i=1; i<N; ++i){
        while(getchar() != ',');
        scanf("%d", &a[i]);
    }
}

int case_proc(){
    if(C > 5050) return 0;
    prv = buf[0];
    nxt = buf[1];
    prv[0] = 1;
    for(int i=1; i<=C; ++i) prv[i] = 0;
    for(int m=0; m<N; ++m){
        for(int n=0; n<=C; ++n){
            int t = n - a[m];
            if(t < 0){
                nxt[n] = prv[n];
            } else {
                nxt[n] = prv[n] + prv[t];
            }
        }
        swap(prv, nxt);
    }
    return prv[C];
}

int main(){
    freopen("i.txt", "r", stdin);
    freopen("o.txt", "w", stdout);
    int M;
    scanf("%d", &M);
    while(M--){
        case_input();
        printf("%d\n", case_proc());
    }
}
