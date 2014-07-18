#include<cstdio>
#include<cstring>

int selection[10000], nSel, nCat;

bool input(){
    if(scanf("%d", &nSel) == EOF || !nSel)return false;
    scanf("%d", &nCat);
    memset(selection, 0, sizeof(selection));
    while(nSel--){
        int course;
        scanf("%d", &course);
        selection[course] = 1;
    }
    return true;
}

bool check(){
    int c, r, course, cnt, err = 0;
    while(nCat--){
        if(!err){
            cnt = 0;
            scanf("%d%d", &c, &r);
            while(c--){
                scanf("%d", &course);
                if(selection[course])++cnt;
            }
            if(cnt < r)err = 1;
        }
        {
        while(getchar() != '\n');
        //scanf("%*[^\n]%*c");      // very weird
        }
    }
    if(err) return false;
    else return true;
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("i.txt", "r", stdin);
    freopen("o.txt", "w", stdout);
#endif
    while(input())
        puts(check()? "yes":"no");
}
