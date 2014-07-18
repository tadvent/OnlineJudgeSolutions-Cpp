#include<cstdio>

int main(){
    int n, x, y, s, d; // x >= y
    scanf("%d", &n);
    while(n--){
        scanf("%d%d", &s, &d);
        if(s < d || (s+d) % 2 != 0)
            printf("impossible\n");
        else {
            x = (s+d)/2;
            y = x - d;
            printf("%d %d\n", x, y);
        }
    }
}
