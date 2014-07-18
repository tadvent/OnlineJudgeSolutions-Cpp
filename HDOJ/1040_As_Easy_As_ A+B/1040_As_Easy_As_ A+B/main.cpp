#include<cstdio>
#include<algorithm>
using namespace std;
int seq[1001];
int main(){
    int T, N;
    scanf("%d", &T);
    while(T--){
        scanf("%d", &N);
        for(int i=0; i<N; ++i)scanf("%d", &seq[i]);
        sort(seq, seq + N);
        for(int i=0; i<N-1; ++i)printf("%d ", seq[i]);
        printf("%d\n", seq[N-1]);
    }
}
