#include<iostream>
#include<queue>
#include<cmath>
using namespace std;
const int maxN = 125;
const int infinity = 100000000;

int map[maxN][maxN];
int d[maxN][maxN];
int N;
int dir[4][2] = {{0,1},{1,0},{0,-1},{-1,0}};

inline bool validpos(int x, int y){
    return (x >= 0 && y >= 0 && x < N && y < N);
}

bool fillmap(){
    if(cin>>N && N>0 && N<=maxN){
        for(int i=0; i<N; ++i)
            for(int j=0; j<N; ++j)
                cin >> map[i][j];
        return true;
    }
    return false;
}

int minlen(){
    queue<int> q;
    for(int i=0; i<N; ++i)
        for(int j=0; j<N; ++j)
            d[i][j] = infinity;
    d[0][0] = map[0][0];
    q.push(0);
    while(!q.empty()){
        div_t pos = div(q.front(), maxN);
        q.pop();
        for(int i=0; i<4; ++i){
            int x = pos.quot + dir[i][0];
            int y = pos.rem  + dir[i][1];
            if(validpos(x, y) && d[pos.quot][pos.rem] + map[x][y] < d[x][y]){
                d[x][y] = d[pos.quot][pos.rem] + map[x][y];
                q.push(x*maxN + y);
            }
        }
    }
    return d[N-1][N-1];
}

int main(){
    freopen("i.txt", "r", stdin);
    freopen("o.txt", "w", stdout);
    cin.tie(NULL);
    int probnum = 0;
    while(fillmap())
        cout << "Problem " << ++probnum << ": " << minlen() << '\n';
    cout.flush();
}
