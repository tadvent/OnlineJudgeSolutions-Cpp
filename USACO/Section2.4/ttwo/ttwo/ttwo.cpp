/*
ID: wjl1241
PROG: ttwo
LANG: C++
*/

#include<fstream>
using namespace std;

char matrix[12][12];
int cx,cy,cd,fx,fy,fd;
int dir[4][2]={
    {0,-1},{1,0},{0,1},{-1,0}
};

const char space='.';
const char obstacle='*';
const char cow='C';
const char farmer='F';
const char border=' ';

bool domove(void){
    int tx,ty;
    tx=cx+dir[cd][0];
    ty=cy+dir[cd][1];
    if(matrix[tx][ty]==space){
        cx=tx;cy=ty;
    }
    else {
        cd=(cd+1)%4;
    }

    tx=fx+dir[fd][0];
    ty=fy+dir[fd][1];
    if(matrix[tx][ty]==space){   //catch the cows
        fx=tx;fy=ty;
    }
    else {
        fd=(fd+1)%4;
    }

    if(cx==fx && cy==fy)return false;
    return true;
}

int main(){
    ifstream fin("ttwo.in");
    ofstream fout("ttwo.out");

    int time=1;
    for(int i=0;i<12;++i){
        matrix[i][0]=matrix[i][11]=matrix[0][i]=matrix[11][i]=border;
    }
    for(int j=1;j<11;++j)for(int i=1;i<11;++i){
        char tmp;
        fin>>tmp;
        if(tmp==cow){
            matrix[i][j]=space;
            cx=i;cy=j;
        }
        else if(tmp==farmer){
            matrix[i][j]=space;
            fx=i;fy=j;
        }
        else matrix[i][j]=tmp;
    }

    cd=0;fd=0;
    while(time<160000 && domove())time++;
    if(time==160000)time=0;
    fout<<time<<endl;

    return 0;
}