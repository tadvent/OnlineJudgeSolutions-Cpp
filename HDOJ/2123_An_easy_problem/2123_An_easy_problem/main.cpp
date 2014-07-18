#include<cstdio>
int main(){
    int c, n;
    scanf("%d", &c);
    while(c--){
        scanf("%d", &n);
        for(int i=1; i<=n; ++i){
            int num = i;
            printf("%d", num);
            for(int j=1; j<n; ++j){
                num += i;
                printf(" %d", num);
            }
            putchar('\n');
        }
    }
}
