#include<cstdio>
const int maxn = 22;

char room[maxn][maxn];
int w, h, sx, sy;

bool input(){
    int i, j;
    if(scanf("%d%d", &w, &h) == EOF || !(w||h))
        return false;
    for(i=1; i<=h; ++i)for(j=1; j<=w; ++j){
        scanf(" %c", &room[i][j]);
        if(room[i][j] == '@'){
            sx = i;
            sy = j;
        }
    }
    for(i=0; i<=h+1; ++i)
        room[i][0] = room[i][w+1] = '#';
    for(j=1; j<=w; ++j)
        room[0][j] = room[h+1][j] = '#';
    return true;
}

int calc(){
    int rst = 0, head = 0, tail = 0, x, y, i;
    int dir[4][2] = {0,1, 0,-1, 1,0, -1,0};
    unsigned queue[maxn * maxn];
    queue[tail++] = sx + (sy<<16);
    room[sx][sy] = '#';

    while(head != tail){
        x = queue[head] & 0xff;
        y = queue[head++]>>16;
        ++rst;

        for(i=0; i<4; ++i){
            int tx = x + dir[i][0], ty = y + dir[i][1];
            if(room[tx][ty] == '.'){
                room[tx][ty] = '#';
                queue[tail++] = tx + (ty<<16);
            }
        }
    }
    return rst;
}

int main(){
    //freopen("i.txt", "r", stdin);
    //freopen("o.txt", "w", stdout);
    while(input())
        printf("%d\n", calc());
}
