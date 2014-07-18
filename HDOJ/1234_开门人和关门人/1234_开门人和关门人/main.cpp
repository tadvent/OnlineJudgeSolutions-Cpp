#include<cstdio>
#include<cstring>

struct Time{
    int h, m, s;
    Time(){}
    Time(int H, int M, int S):h(H), m(M), s(S){}
    bool input(){
        if(scanf("%d:%d:%d", &h, &m, &s) == EOF)
            return false;
        return true;
    }
    bool operator<(const Time &r){
        return (h < r.h ||
            h == r.h && m < r.m ||
            h == r.h && m == r.m && s < r.s);
    }
};

int main(){
#ifndef ONLINE_JUDGE
    freopen("i.txt", "r", stdin);
    freopen("o.txt", "w", stdout);
#endif
    int N, M;
    scanf("%d", &N);
    while(N--){
        char begid[16], endid[16], tmpid[16];
        Time beg(24, 60, 60), end(0, 0, 0), tmpbeg, tmpend;
        scanf("%d", &M);
        while(M--){
            scanf("%s", tmpid);
            tmpbeg.input();
            tmpend.input();
            if(tmpbeg < beg){
                beg = tmpbeg;
                strcpy(begid, tmpid);
            }
            if(end < tmpend){
                end = tmpend;
                strcpy(endid, tmpid);
            }
        }
        printf("%s %s\n", begid, endid);
    }
}
