/*
ID: wjl1241
PROG: cowtour
LANG: C++
*/

#include<fstream>
#include<vector>
#include<cmath>
using namespace std;

const double infinite=10000000.0;

struct point{
    double x;
    double y;
};

int N;
vector<point> points;
vector<vector<double> > dist;
vector<vector<int> > maze;
vector<int> visited;

void devidemaze(vector<int> &maze, const int num, const int mark){
    visited[num]=mark;
    maze.push_back(num);
    for(int i=0;i<N;++i)if(dist[num][i]<infinite && visited[i]==-1){
        devidemaze(maze,i,mark);
    }
}

void floyd(const vector<int> &maze){
    for(int k=0;k<(int)maze.size();++k)
        for(int i=0;i<(int)maze.size();++i)
            for(int j=0;j<(int)maze.size();++j){
                if(dist[maze[i]][maze[j]]>dist[maze[i]][maze[k]]+dist[maze[k]][maze[j]]){
                    dist[maze[i]][maze[j]]=dist[maze[j]][maze[i]]=dist[maze[i]][maze[k]]+dist[maze[k]][maze[j]];
                }
            }
}

void calcmaxdist(const vector<int> &maze, vector<double> &maxdist){
    for(int i=0;i<(int)maze.size();++i){
        double max=0.0;
        for(int j=0;j<(int)maze.size();++j){
            if(dist[maze[i]][maze[j]]>max)max=dist[maze[i]][maze[j]];
        }
        maxdist[maze[i]]=max;
    }
}

int main(){
    ifstream fin("cowtour.in");
    ofstream fout("cowtour.out");
    fin>>N;
    points.resize(N);
    dist.resize(N);
    for(int i=0;i<N;++i){
        dist[i].resize(N);
        for(int j=0;j<N;++j)dist[i][j]=infinite;
    }
    for(int i=0;i<N;++i)dist[i][i]=0.0;
    for(int i=0;i<N;++i)fin>>points[i].x>>points[i].y;

    char ch;
    for(int i=0;i<N;++i)for(int j=0;j<N;++j){
        fin>>ch;
        if('1'==ch){
            double dx=points[i].x-points[j].x;
            double dy=points[i].y-points[j].y;
            dist[i][j]=sqrt(dx*dx+dy*dy);
        }
    }

    visited.resize(N,-1);
    int mark=0;
    for(int i=0;i<N;++i){
        if(visited[i]==-1){
            maze.push_back(vector<int>(0));
            devidemaze(maze[maze.size()-1],i,mark++);
        }
    }

    for(int i=0;i<(int)maze.size();++i)floyd(maze[i]);

    vector<double> maxdist(N);

    for(int i=0;i<(int)maze.size();++i)calcmaxdist(maze[i],maxdist);
    vector<double> diameter(maze.size(),0.0);

    for(int i=0;i<(int)maze.size();++i){
        for(int j=0;j<(int)maze[i].size();++j)
            if(diameter[i]<maxdist[maze[i][j]])diameter[i]=maxdist[maze[i][j]];
    }

    double Gdiameter=infinite;
    for(int i=0;i<N;++i)for(int j=0;j<N;++j)if(visited[i]!=visited[j]){
        double dx=points[i].x-points[j].x;
        double dy=points[i].y-points[j].y;
        double td=maxdist[i]+sqrt(dx*dx+dy*dy)+maxdist[j];
        if(diameter[visited[i]]>td)td=diameter[visited[i]];
        if(diameter[visited[j]]>td)td=diameter[visited[j]];
        if(td<Gdiameter)Gdiameter=td;
    }

    fout.precision(6);
    fout<<fixed<<Gdiameter<<endl;

    return 0;
}