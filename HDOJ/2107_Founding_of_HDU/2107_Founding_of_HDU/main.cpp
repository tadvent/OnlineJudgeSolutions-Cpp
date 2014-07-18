#include<cstdio>
int main(){
    int n, max, cur;
    while(scanf("%d", &n) != EOF && n > 0){
        max = 0;
        while(n--){
            scanf("%d", &cur);
            if(cur > max)max = cur;
        }
        printf("%d\n", max);
    }
}
