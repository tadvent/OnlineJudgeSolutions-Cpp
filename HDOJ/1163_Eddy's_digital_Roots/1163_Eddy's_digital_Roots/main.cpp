#include<cstdio>
#include<cstdlib>

int roots(int n){
    int r = n % 9;

    int cir2[] = {2, 4, 8, 7, 5, 1};
    int cir4[] = {4, 7, 1};
    int cir5[] = {5, 7, 8, 4, 2, 1};
    int cir7[] = {7, 4, 1};
    int cir8[] = {8, 1};

    switch(r){
        case 0: case 3: case 6: return 9;
        case 1: return 1;
        case 2: return cir2[(n-1)%6];
        case 4: return cir4[(n-1)%3];
        case 5: return cir5[(n-1)%6];
        case 7: return cir7[(n-1)%3];
        case 8: return cir8[(n-1)%2];
    }

    //for(int i=1; i<=9; ++i){
    //    printf("%2d:", i);
    //    int j = 10, n = i;
    //    while(j--){
    //        printf("%2d", n%9);
    //        n *= i;
    //    }
    //    putchar('\n');
    //}
    return 0;
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("i.txt", "r", stdin);
    freopen("o.txt", "w", stdout);
#endif
    int n;
    while(scanf("%d", &n) != EOF && n > 0){
        printf("%d\n", roots(n));
    }
}
