#include<cstdio>
#include<algorithm>
using namespace std;

int N, sum;
int maze[105][105];
int buf[10005];

bool myfill(int x, int y, int idx){
    if(y >= N){
        int s = 0;
        for(int i=0; i<N; ++i) s += maze[x][i];
        if(s != sum) return false;
        ++x; y=0;
    }
    if(x >= N){
        for(int c=0; c<N; ++c){
            int s = 0;
            for(int r=0; r<N; ++r) s += maze[r][c];
            if(s != sum) return false;
        }
        int s = 0;
        for(int i=0; i<N; ++i) s += maze[i][i];
        if(s != sum) return false;
        s = 0;
        for(int i=0; i<N; ++i) s += maze[i][N-1-i];
        if(s != sum) return false;
        return true;
    }

    for(int i=idx; i<N*N; ++i){
        maze[x][y] = buf[i];
        swap(buf[idx], buf[i]);
        if(myfill(x, y+1, idx+1)) return true;
        swap(buf[idx], buf[i]);
    }
    return false;
}

void output(){
    for(int i=0; i<N; ++i) {
        for(int j=0; j<N; ++j) printf("%d ", maze[i][j]);
        putchar('\n');
    }
    putchar('\n');
}

bool input(){
    if(scanf("%d", &N) != 1 || N <= 0) return false;
    sum = N*(N*N+1)/2;
    for(int i=0; i<N*N; ++i) buf[i] = i+1;
    return true;
}

int main(){
    freopen("i.txt", "r", stdin);
    freopen("o.txt", "w", stdout);
    while(input()){
        if(myfill(0,0,0)) output();
    }
}
