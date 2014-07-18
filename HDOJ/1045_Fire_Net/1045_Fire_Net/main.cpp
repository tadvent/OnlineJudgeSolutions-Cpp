#include<cstdio>

char city[6][6];
int city_sz;  // <= 4

bool input(){
    if(scanf("%d", &city_sz) == EOF || city_sz <= 0)
        return false;
    for(int i = 0; i <= city_sz+1; ++i){
        city[0][i] = city[i][0] = city[city_sz+1][i] = city[i][city_sz+1] = 'X';
    }
    for(int i = 1; i <= city_sz; ++i)for(int j = 1; j <= city_sz; ++j){
        scanf(" %c", &city[i][j]);
    }
    return true;
}
// X: wall  .: empty   c: castle
int dfs(int x, int y){  // return the num of castle can be put
    if(city[x][y] != '.')return 0;

    for(int i = x-1; city[i][y] != 'X'; --i) // left:
        if(city[i][y] == 'c')return 0;
    //for(int i = x+1; city[i][y] != 'X'; ++i) // right:
    //    if(city[i][y] == 'c')return 0;
    for(int j = y-1; city[x][j] != 'X'; --j) // up:
        if(city[x][j] == 'c')return 0;
    //for(int j = y+1; city[x][j] != 'X'; ++j) // down:
    //    if(city[x][j] == 'c')return 0;
    city[x][y] = 'c';

    int dfscastle = 0, dfstmp;
    for(int j = y+1; j <= city_sz; ++j){
        if((dfstmp = dfs(x, j)) > dfscastle)
            dfscastle = dfstmp;
    }
    for(int i = x+1; i <= city_sz; ++i)for(int j = 1; j <= city_sz; ++j){
        if((dfstmp = dfs(i, j)) > dfscastle)
            dfscastle = dfstmp;
    }
    city[x][y] = '.';
    return 1 + dfscastle;
}

int castle_count(){
    int maxcnt = 0, tmpcnt;
    for(int i=1; i<=city_sz; ++i)for(int j=1; j<=city_sz; ++j)
        if((tmpcnt = dfs(i,j)) > maxcnt)maxcnt = tmpcnt;
    return maxcnt;
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("i.txt", "r", stdin);
    freopen("o.txt", "w", stdout);
#endif
    while(input())
        printf("%d\n", castle_count());
}
