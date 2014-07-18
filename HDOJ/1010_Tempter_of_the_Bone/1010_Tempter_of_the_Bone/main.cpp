#include<iostream>
#include<cmath>
using namespace std;
const int maxsize = 7;

char maze[maxsize+2][maxsize+2];
int dx, dy;

bool CanSurvive(int x, int y, int td){
    // sx, sy: start postion
    // td: time of door to open
    if(td == 0){
        if(x == dx && y == dy)return true;
        else return false;
    } else if(x == dx && y == dy)return false;
    maze[x][y] = '1';
    if(maze[x+1][y] == '.'){
        if(CanSurvive(x+1, y, td-1))return true;
    }
    if(maze[x-1][y] == '.'){
        if(CanSurvive(x-1, y, td-1))return true;
    }
    if(maze[x][y+1] == '.'){
        if(CanSurvive(x, y+1, td-1))return true;
    }
    if(maze[x][y-1] == '.'){
        if(CanSurvive(x, y-1, td-1))return true;
    }
    maze[x][y] = '.';
    return false;
}

int main(){
    //freopen("i.txt", "r", stdin);
    //freopen("o.txt", "w", stdout);
    int h, w, t, sx, sy;
    while(cin>>h>>w>>t && (h||w||t)){
        bool survive = true;
        int nblocks = 0;
        for(int j=0; j<=w+1; ++j)
            maze[0][j] = maze[h+1][j] = 'X';
        for(int i=1; i<=h; ++i){
            maze[i][0] = maze[i][w+1] = 'X';
            for(int j=1; j<=w; ++j){
                cin>>maze[i][j];
                if(maze[i][j] == '.'){
                    ++nblocks;
                } else if(maze[i][j] == 'S'){
                    sx = i;
                    sy = j;
                } else if(maze[i][j] == 'D'){
                    dx = i;
                    dy = j;
                    maze[i][j] = '.';
                    ++nblocks;
                }
            }
        }
        if(nblocks < t)survive = false;
        else {
            int mindist = abs(sx - dx) + abs(sy - dy);
            if((t - mindist) % 2 != 0)survive = false;
        }
        cout<<((survive && CanSurvive(sx, sy, t))? "YES\n":"NO\n");
    }
}
