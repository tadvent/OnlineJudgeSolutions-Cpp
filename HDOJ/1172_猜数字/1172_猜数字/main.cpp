#include<cstdio>
#include<cstring>
#include<sstream>
#include<algorithm>

bool check(const char stdstr[], const char gesstr[], int ga, int gb){
    int a = 0, b = 0;
    char stdbuf[6], gesbuf[6], *p1, *p2;
    for(int i=0; i<4; ++i)if(gesstr[i] == stdstr[i])++b;
    if(b != gb)return false;
    strcpy(stdbuf, stdstr); strcpy(gesbuf, gesstr);
    std::sort(stdbuf, stdbuf+4); std::sort(gesbuf, gesbuf+4);
    for(p1=stdbuf,p2=gesbuf; *p1 && *p2;){
        if(*p1 < *p2) ++p1;
        else if(*p1 > *p2) ++p2;
        else { ++a; ++p1; ++p2; }
    }
    if(a != ga)return false;
    else return true;
}

bool chkall(const char stdstr[], const char gesstr[][6], const int gessco[][2], int n){
    for(int i=0; i<n; ++i){
        if(!check(stdstr, gesstr[i], gessco[i][0], gessco[i][1]))
            return false;
    }
    return true;
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("i.txt", "r", stdin);
    freopen("o.txt", "w", stdout);
#endif
    int n, gessco[102][2];
    char stdstr[6], gesstr[102][6];
    std::ostringstream os;

    while(scanf("%d", &n) != EOF && n){
        for(int i=0; i<n; ++i){
            scanf("%s%d%d", gesstr[i], &gessco[i][0], &gessco[i][1]);
        }

        int ans = 0;
        for(int num=1000; num<10000; ++num){
            os.str("");
            os<<num;
            stdstr[os.str().copy(stdstr, 6)] = 0;

            if(chkall(stdstr, gesstr, gessco, n)){
                if(ans == 0){
                    ans = num;
                } else {
                    ans = 0;
                    break;
                }
            }
        }
        if(ans)printf("%d\n", ans);
        else printf("Not sure\n");
    }
}
