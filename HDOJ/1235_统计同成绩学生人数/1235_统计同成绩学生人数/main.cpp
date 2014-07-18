//#include<cstdio>
//#include<cstring>
//
//int main(){
//    int N, st[101], sc;
//    while(scanf("%d", &N) != EOF && N){
//        memset(st, 0, sizeof(st));
//        while(N--){
//            scanf("%d", &sc);
//            ++st[sc];
//        }
//        scanf("%d", &sc);
//        printf("%d\n", st[sc]);
//    }
//}


// faster :
#include<cstdio>
#include<cstring>

int main(){
#ifndef ONLINE_JUDGE
    freopen("i.txt", "r" , stdin);
    freopen("o.txt", "w" , stdout);
#endif
    char line[4005] = {' '}, key[6] = {' '}, *p;
    int N, len, cnt;
    while(scanf("%d ", &N) != EOF && N){
        p = line + 1; while((*p++ = getchar()) != '\n'); *(p-1) = ' '; *p = 0;
        p = key  + 1; while((*p++ = getchar()) != '\n'); *(p-1) = ' '; *p = 0;
        len = p - key - 1;
        p = line;
        cnt = 0;
        while(p = strstr(p, key)){
            ++cnt; p += len;
        }
        printf("%d\n", cnt);
    }
}
