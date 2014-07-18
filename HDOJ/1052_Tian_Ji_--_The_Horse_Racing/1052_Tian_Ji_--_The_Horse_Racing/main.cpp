#include<cstdio>
#include<algorithm>

int main(){
#ifndef ONLINE_JUDGE
    freopen("i.txt", "r", stdin);
    freopen("o.txt", "w", stdout);
#endif
    int tian[1003], king[1003], n;
    while(scanf("%d", &n) == 1 && n){
        int i, *ti, *tj, *ki, *kj, rst = 0;
        for(i=n-1; i>=0; --i)scanf("%d", tian+i);
        for(i=n-1; i>=0; --i)scanf("%d", king+i);
        std::sort(tian, tian+n);
        std::sort(king, king+n);
        ti = tian; tj = tian + n-1;
        ki = king; kj = king + n-1;
        while(n--){
            if(*ti > *ki){
                ++ti; ++ki; rst += 200;
            } else if(*tj > *kj){
                --tj; --kj; rst += 200;
            } else if(*ti == *kj){ // *ti == *ki == *(ki+1) == ... == *kj
                ++ti; --kj;
            } else { // *ti <= *ki <= ... <= *kj && *ti < *kj
                ++ti; --kj; rst -= 200;
            }
        }
        printf("%d\n", rst);
    }
}

