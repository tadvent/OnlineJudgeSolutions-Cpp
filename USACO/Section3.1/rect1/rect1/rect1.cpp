/*
ID: wjl1241
PROG: rect1
LANG: C++
*/

#include<fstream>
#include<vector>
using namespace std;

struct layout{
    int x1;
    int y1;
    int x2;
    int y2;
    int color;
    layout(void):x1(0),x2(0),y1(0),y2(0),color(0){}
    layout(int X1, int Y1, int X2, int Y2, int Color)
        :x1(X1),x2(X2),y1(Y1),y2(Y2),color(Color){}
};

vector<layout> papers(1);
vector<int> area(2501);
int n;

void put(layout paper, int z){
    while(z<=n && (paper.x1>=papers[z].x2 || paper.y1>=papers[z].y2 || paper.x2<=papers[z].x1 || paper.y2<=papers[z].y1))++z;
    if(z>n){
        area[paper.color]+=(paper.x2-paper.x1)*(paper.y2-paper.y1);
        return;
    }
    if(paper.x1<papers[z].x1){
        put(layout(paper.x1,paper.y1,papers[z].x1,paper.y2,paper.color),z+1);
        paper.x1=papers[z].x1;
    }
    if(paper.x2>papers[z].x2){
        put(layout(papers[z].x2,paper.y1,paper.x2,paper.y2,paper.color),z+1);
        paper.x2=papers[z].x2;
    }
    if(paper.y1<papers[z].y1)put(layout(paper.x1,paper.y1,paper.x2,papers[z].y1,paper.color),z+1);
    if(paper.y2>papers[z].y2)put(layout(paper.x1,papers[z].y2,paper.x2,paper.y2,paper.color),z+1);
}

int main(){
    ifstream fin("rect1.in");
    ofstream fout("rect1.out");
    papers[0].x1=papers[0].y1=0;
    papers[0].color=1;
    fin>>papers[0].x2>>papers[0].y2>>n;
    papers.resize(n+1);
    for(int i=1;i<=n;++i)
        fin>>papers[i].x1>>papers[i].y1>>papers[i].x2>>papers[i].y2>>papers[i].color;

    for(int i=n;i>=0;--i)put(papers[i],i+1);
    for(int i=1;i<2501;++i)if(area[i]>0)fout<<i<<' '<<area[i]<<'\n';
    return 0;
}