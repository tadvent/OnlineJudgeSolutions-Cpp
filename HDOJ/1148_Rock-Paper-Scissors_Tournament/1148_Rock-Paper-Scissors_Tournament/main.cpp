#include<cstdio>
#include<cstdlib>
#include<cstring>

int win[101], lose[101], nPlayer, nGame;

bool init(){
    if(scanf("%d", &nPlayer) == EOF || !nPlayer)return false;
    scanf("%d", &nGame);
    memset(win, 0, sizeof(win));
    memset(lose, 0, sizeof(lose));
    return true;
}
void readgames(){
    static const int judge[4][4] = {
        // paper, x, rock, scissors
         0,  0,  1, -1,
         0,  0,  0,  0,
        -1,  0,  0,  1,
         1,  0, -1,  0
    };
    int id1, id2, rst;
    char ch1[10], ch2[10];
    while(nGame--){
        scanf("%d%s%d%s", &id1, ch1, &id2, ch2);
        rst = judge[ch1[0]-'p'][ch2[0]-'p'];
        if(rst < 0){
            ++lose[id1-1];
            ++win[id2-1];
        } else if(rst > 0){
            ++win[id1-1];
            ++lose[id2-1];
        }
    }
}

void output(){
    static int idx = 0;
    if(idx++)putchar('\n');
    for(int i=0; i<nPlayer; ++i){
        if(win[i] + lose[i] == 0)puts("-");
        else printf("%.3f\n", double(win[i])/(win[i]+lose[i]));
    }
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("i.txt", "r", stdin);
    freopen("o.txt", "w", stdout);
#endif
    while(init()){
        readgames();
        output();
    }
}
