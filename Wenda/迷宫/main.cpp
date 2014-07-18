#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;

int M, N;
int maze[20][20];

void caseInput(){
    scanf("%d%d ", &M, &N);
    char c;
    for(int i=0; i<M; ++i) for(int j=0; j<N; ++j){
        scanf("%c ", &c);
        maze[i][j] = c - '0';
    }
}

int calc(int x, int y){
    if(x < 0 || x >= M || y < 0 || y >= N || maze[x][y] == 0) return 0;
    if(x == M-1 && y == N-1) return maze[x][y];
    int tmp = maze[x][y];
    maze[x][y] = 0;
    int m = 0, t;
    if((t = calc(x-1, y)) > m) m = t;
    if((t = calc(x+1, y)) > m) m = t;
    if((t = calc(x, y-1)) > m) m = t;
    if((t = calc(x, y+1)) > m) m = t;
    maze[x][y] = tmp;
    if(m == 0) return 0;
    return m + tmp;
}

int main(){
    freopen("i.txt", "r", stdin);
    freopen("o.txt", "w", stdout);
    int C;
    scanf("%d", &C);
    while(C--){
        caseInput();
        printf("%d\n", calc(0, 0));
    }
}
