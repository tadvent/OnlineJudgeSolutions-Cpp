#include<cstdio>
#include<set>
#include<utility>
using namespace std;

char maze[12][12];
int M, N;

void input(){
    scanf("%d%d ", &M, &N);
    for(int i=0; i<M; ++i) for(int j=0; j<N; ++j)
        scanf("%c ", &maze[i][j]);
}

set< pair<int,int> > toerase;

void jeraserow(int row){
    int cnt = 0;
    char last = '0';
    for(int i=0; i<N; ++i){
        if(maze[row][i] == last){
            if(last != '0'){
                ++cnt;
            }
        } else {
            if(cnt >= 3 && last != '0'){
                for(int j=i-1; j>=0 && maze[row][j] == last; --j) toerase.insert(pair<int,int>(row,j));
            }
            cnt = 1;
            last = maze[row][i];
        }
    }
    if(cnt >= 3 && last != '0')
        for(int j=N-1; j>=0 && maze[row][j] == last; --j) toerase.insert(pair<int,int>(row,j));
}
void jerasecol(int col){
    int cnt = 0;
    char last = '0';
    for(int i=0; i<M; ++i){
        if(maze[i][col] == last){
            if(last != '0'){
                ++cnt;
            }
        } else {
            if(cnt >= 3 && last != '0'){
                for(int j=i-1; j>=0 && maze[j][col] == last; --j) toerase.insert(pair<int,int>(j,col));
            }
            cnt = 1;
            last = maze[i][col];
        }
    }
    if(cnt >= 3 && last != '0')
        for(int j=M-1; j>=0 && maze[j][col] == last; --j) toerase.insert(pair<int,int>(j,col));
}

bool jerase(){
    toerase.clear();
    for(int r=0; r<M; ++r) jeraserow(r);
    for(int c=0; c<N; ++c) jerasecol(c);
    return !toerase.empty();
}

void drop(){
    for(set<pair<int,int> >::iterator it = toerase.begin(); it != toerase.end(); ++it){
        maze[it->first][it->second] = '0';
    }
    for(int c=0; c<N; ++c){
        int e = M-1;
        for(int r = M-1; r >= 0; --r){
            if(maze[r][c] != '0') maze[e--][c] = maze[r][c];
        }
        for(; e>=0; --e) maze[e][c] = '0';
    }
}

void output(){
    for(int i=0; i<M; ++i){
        for(int j=0; j<N; ++j) printf("%c", maze[i][j]);
        putchar('\n');
    }
}

int main(){
    freopen("i.txt", "r", stdin);
    freopen("o.txt", "w", stdout);

    int C;
    scanf("%d", &C);
    while(C--){
        input();
        while(jerase()){
            drop();
            output();
        }
    }
}
