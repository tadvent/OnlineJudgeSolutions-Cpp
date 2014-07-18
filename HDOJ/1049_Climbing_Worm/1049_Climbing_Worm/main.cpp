#include<cstdio>
int Climb(int n, int u, int d){
    if(u>=n)return 1;
    return (n-d-1)/(u-d)*2 + 1;
}
int main(){
    int n, u, d;
    while(scanf("%d%d%d", &n, &u, &d) != EOF && n>0){
        printf("%d\n", Climb(n, u, d));
    }
}
