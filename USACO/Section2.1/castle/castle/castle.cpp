/*
ID: wjl1241
PROG: castle
LANG: C++
*/

#include<fstream>
using namespace std;

const int size=50;
int castle[size][size]; //walls code of each square
int mark[size][size];   //marked number of each room
int space[size*size+1]; //how many squares the marked room has
int m,n,color,maxspace=0,maxcrtspace=0;        // M x N

int rx,ry;
char rch;
int makemark(const int x, const int y);
void domark(const int x, const int y, const int color);

int main(){
    ifstream fin("castle.in");
    ofstream fout("castle.out");

    fin>>m>>n;
    for(int j=0;j<n;++j)for(int i=0;i<m;++i){
        fin>>castle[i][j];
    }

    for(int i=0;i<size;++i)space[i]=0;
    for(int i=0;i<size;++i)for(int j=0;j<size;++j)mark[i][j]=0;

    for(int j=0;j<n;++j)for(int i=0;i<m;++i)color=makemark(i,j);
    for(int i=1;i<=color;++i)if(space[i]>maxspace)maxspace=space[i];
    fout<<color<<'\n';
    fout<<maxspace<<'\n';

    //try to remove each wall to find the maxcreatable space
    for(int i=0;i<m;++i)for(int j=n-1;j>=0;--j){
        int wallcode=castle[i][j];
        if(((wallcode>>1)&1) && j>0){ //North has a wall
            if(mark[i][j]!=mark[i][j-1]){
                int tmp;
                if((tmp=space[mark[i][j]]+space[mark[i][j-1]])>maxcrtspace){
                    maxcrtspace=tmp;
                    rx=i;ry=j;rch='N';
                }
            }
        }
        if(((wallcode>>2)&1) && i<m-1){ //East has a wall
            if(mark[i][j]!=mark[i+1][j]){
                int tmp;
                if((tmp=space[mark[i][j]]+space[mark[i+1][j]])>maxcrtspace){
                    maxcrtspace=tmp;
                    rx=i;ry=j;rch='E';
                }
            }
        }
    }
    fout<<maxcrtspace<<'\n';
    fout<<ry+1<<' '<<rx+1<<' '<<rch<<'\n';

    return 0;
}

int makemark(const int x, const int y){ //return the marked number
    static int color=0;
    if(0!=mark[x][y])return color;
    domark(x,y,++color);
    return color;
}

void domark(const int x, const int y, const int color){
    if(0!=mark[x][y])return;
    mark[x][y]=color;
    ++space[color];
    int wallcode=castle[x][y];
    if(!(wallcode&1))domark(x-1,y,color);
    if(!((wallcode>>1)&1))domark(x,y-1,color);
    if(!((wallcode>>2)&1))domark(x+1,y,color);
    if(!((wallcode>>3)&1))domark(x,y+1,color);
}

//====================================================================

//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//#include <assert.h>
//
//#define MAXDIM 50
//#define MAXN 100
//#define MAXCOLOR 100
//#define MAXROOM (MAXDIM*MAXDIM)
//
//enum {
//    Wwest = 1,
//    Wnorth = 2,
//    Weast = 4,
//    Wsouth = 8
//};
//
//typedef struct Square Square;
//struct Square {
//    int wall;
//    int numbered;
//    int room;
//};
// 
//int wid, ht;
//Square castle[MAXDIM][MAXDIM];
//int roomsize[MAXROOM];
//
//void number(int room, int x, int y)
//{
//    int w;
//
//    if(castle[x][y].numbered){
//        assert(castle[x][y].room == room);
//        return;
//    }
//
//    castle[x][y].numbered = 1;
//    castle[x][y].room = room;
//    roomsize[room]++;
//
//    w = castle[x][y].wall;
//
//    if(x > 0 && !(w & Wwest))number(room, x-1, y);
//    if(x+1 < wid && !(w & Weast))number(room, x+1, y);
//    if(y > 0 && !(w & Wnorth))number(room, x, y-1);
//    if(y+1 < ht && !(w & Wsouth))number(room, x, y+1);
//}
//
//int main(void)
//{
//    FILE *fin, *fout;
//    int x, y, w, nroom, bigroom;
//    int i, n, m, mx, my;
//    char mc;
//
//    fin = fopen("castle.in", "r");
//    fout = fopen("castle.out", "w");
//    assert(fin != NULL && fout != NULL);
//
//    fscanf(fin, "%d %d", &wid, &ht);
//
//    /* read in wall info */
//    for(y=0; y<ht; y++) {
//        for(x=0; x<wid; x++) {
//            fscanf(fin, "%d", &w);
//            castle[x][y].wall = w;
//        }
//    }
//
//    /* number rooms */
//    nroom = 0;
//    for(y=0; y<ht; y++)
//    for(x=0; x<wid; x++)
//        if(!castle[x][y].numbered)
//            number(nroom++, x, y);
//
//    /* find biggest room */
//    bigroom = roomsize[0];
//    for(i=1; i<nroom; i++)
//        if(bigroom < roomsize[i])
//            bigroom = roomsize[i];
//
//    /* look at best that can come of removing an east or north wall */
//    m = 0;
//    for(x=0; x<wid; x++)for(y=ht-1; y>=0; y--){
//        if(y > 0 && castle[x][y].room != castle[x][y-1].room) {
//            n = roomsize[castle[x][y].room] + roomsize[castle[x][y-1].room];
//            if(n > m) {
//                m = n;
//                mx = x;
//                my = y;
//                mc = 'N';
//            }
//        }
//        if(x+1 < wid && castle[x][y].room != castle[x+1][y].room) {
//            n = roomsize[castle[x][y].room] + roomsize[castle[x+1][y].room];
//            if(n > m) {
//                m = n;
//                mx = x;
//                my = y;
//                mc = 'E';
//            }
//        }
//    }
//
//    fprintf(fout, "%d\n", nroom);
//    fprintf(fout, "%d\n", bigroom);
//    fprintf(fout, "%d\n", m);
//    fprintf(fout, "%d %d %c\n", my+1, mx+1, mc);
//    exit(0);
//    return 0;
//}