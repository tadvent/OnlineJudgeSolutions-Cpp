/*
ID: wjl1241
PROG: maze1
LANG: C++
*/

//#define dbg

#include<fstream>
#include<vector>
#include<queue>

#ifdef dbg
#include<iomanip>
#endif
using namespace std;

vector<vector<char> > maze;
vector<vector<int > > dist;
vector<vector<bool> > visited;

queue<int> qx;
queue<int> qy;
queue<int> qn;

const char space=' ';
const char wall='&';

void walk(void){
    int x=qx.front();
    int y=qy.front();
    int n=qn.front();
    qx.pop();qy.pop();qn.pop();
    if(n<dist[x][y])dist[x][y]=n;
    if(maze[x+1][y]==space)if(!visited[x+2][y]){
        qx.push(x+2);qy.push(y);qn.push(n+1);
        visited[x+2][y]=true;
    }
    if(maze[x-1][y]==space)if(!visited[x-2][y]){
        qx.push(x-2);qy.push(y);qn.push(n+1);
        visited[x-2][y]=true;
    }
    if(maze[x][y+1]==space)if(!visited[x][y+2]){
        qx.push(x);qy.push(y+2);qn.push(n+1);
        visited[x][y+2]=true;
    }
    if(maze[x][y-1]==space)if(!visited[x][y-2]){
        qx.push(x);qy.push(y-2);qn.push(n+1);
        visited[x][y-2]=true;
    }
}

int main(){
    ifstream fin("maze1.in");
    ofstream fout("maze1.out");
    int width,height,start1x,start1y,start2x,start2y;
    char ch;
    fin>>width>>height;
    fin>>noskipws>>ch;
    width=width*2+1;
    height=height*2+1;
    maze.resize(height);
    dist.resize(height);
    visited.resize(height);
    for(int i=0;i<height;++i){
        maze[i].resize(width);
        dist[i].resize(width);
        visited[i].resize(width);
        for(int j=0;j<=width;++j){
            if(!(fin>>noskipws>>ch))break;
            switch(ch){
                case '+':
                case '|':
                case '-':
                    maze[i][j]=wall;
                    dist[i][j]=100000;
                    break;
                case ' ':
                    maze[i][j]=space;
                    dist[i][j]=100000;
                    break;
            }
        }
    }
    int startnum=0;
    for(int i=0;i<height;++i){
        if(maze[i][0]==space){
            maze[i][0]=wall;
            switch(++startnum){
                case 1:
                    start1x=i;start1y=1;
                    break;
                case 2:
                    start2x=i;start2y=1;
                    break;
            }
        }
        if(maze[i][width-1]==space){
            maze[i][width-1]=wall;
            switch(++startnum){
                case 1:
                    start1x=i;start1y=width-2;
                    break;
                case 2:
                    start2x=i;start2y=width-2;
                    break;
            }
        }
    }
    for(int j=0;j<width;++j){
        if(maze[0][j]==space){
            maze[0][j]=wall;
            switch(++startnum){
                case 1:
                    start1x=1;start1y=j;
                    break;
                case 2:
                    start2x=1;start2y=j;
                    break;
            }
        }
        if(maze[height-1][j]==space){
            maze[height-1][j]=wall;
            switch(++startnum){
                case 1:
                    start1x=height-2;start1y=j;
                    break;
                case 2:
                    start2x=height-2;start2y=j;
                    break;
            }
        }
    }

    for(int i=0;i<height;++i)for(int j=0;j<width;++j)visited[i][j]=false;
    qx.push(start1x);qy.push(start1y);qn.push(1);
    visited[start1x][start1y]=true;
    while(!qn.empty())walk();

    for(int i=0;i<height;++i)for(int j=0;j<width;++j)visited[i][j]=false;
    qx.push(start2x);qy.push(start2y);qn.push(1);
    visited[start2x][start2y]=true;
    while(!qn.empty())walk();

    int &maxstep=startnum;
    maxstep=0;
    for(int i=1;i<height;i+=2)for(int j=1;j<width;j+=2)
        if(maxstep<dist[i][j])maxstep=dist[i][j];

    fout<<maxstep<<endl;

#ifdef dbg
    for(int i=0;i<height;++i){
        for(int j=0;j<width;++j)fout<<maze[i][j];
        fout<<'\n';
    }
    for(int i=0;i<height;++i){
        for(int j=0;j<width;++j)fout<<setw(8)<<dist[i][j];
        fout<<'\n';
    }
#endif

    return 0;
}