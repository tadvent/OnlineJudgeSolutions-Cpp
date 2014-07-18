/*
ID: wjl1241
PROG: camelot
LANG: C++
*/

#include<fstream>
#include<vector>
using namespace std;
const int infinite=100000;

int R,C,nKnight;
pair<int,int> king;
vector< pair<int,int> > knights;
int minimove[5][5]={
    0,3,2,3,2,
    3,2,1,2,3,
    2,1,4,3,2,
    3,2,3,2,3,
    2,3,2,3,4
};

inline bool OnBoard(int x, int y){
    return ( 0<=x && 0<=y && y<R && x<C );
}

int kgmove(int sx, int sy, int ex, int ey){
    if(sx>ex)swap(sx,ex);
    if(sy>ey)swap(sy,ey);
    return max(ex-sx,ey-sy);
}

int knmove(int sx, int sy, int ex, int ey){ //R>=3 && C>=3
    if(C ==3 && R ==3){
        if(sx==ex && sy==ey)return 0;
        if( (sx==1 && sy==1) || (ex==1 && ey==1))return infinite;
        int dx=ex-sx,dy=ey-sy;
        if(dx<0)dx=-dx;
        if(dy<0)dy=-dy;
        if(dx+dy==1)return 5;
    }
    if( (sx==0 && sy==0 && ex==1 && ey==1) || (ex==0 && ey==0 && sx==1 && sy==1) ||
        (sx==C-1 && sy==0 && ex==C-2 && ey==1) || (ex==C-1 && ey==0 && sx==C-2 && sy==1) ||
        (sx==0 && sy==R-1 && ex==1 && ey==R-2) || (ex==0 && ey==R-1 && sx==1 && sy==R-2) ||
        (sx==C-1 && sy==R-1 && ex==C-2 && ey==R-2) || (ex==C-1 && ey==R-1 && sx==C-2 && sy==R-2) )
        return 4;
    int move=0,dx,dy;
    if(sx>ex)swap(sx,ex);
    if(sy>ey)swap(sy,ey);
    dx=ex-sx;
    dy=ey-sy;
    while( dx>4 || dy>4){
        if(dx>dy){
            sx+=2;
            sy+=1;
        }
        else {
            sx+=1;
            sy+=2;
        }
        ++move;
        dx=ex-sx;
        if(dx<0){swap(ex,sx);dx=-dx;}
        dy=ey-sy;
        if(dy<0){swap(ey,sy);dy=-dy;}
    }
    return move+minimove[dx][dy];
}

int knmove_narrow(int sx, int sy, int ex, int ey){//R==2 || C==2
    if(sx>ex)swap(sx,ex);
    if(sy>ey)swap(sy,ey);
    int dx=ex-sx,dy=ey-sy;
    if(dy>dx)swap(dx,dy);
    if(dx%2==0){
        int move=dx/2;
        if(move%2==dy)return move;
        else return infinite;
    }
    return infinite;
}

int main(){
    ifstream fin("camelot.in");
    ofstream fout("camelot.out");
    fin>>R>>C;
    int innum;
    char inch;
    fin>>inch>>innum;
    king.first=int(inch-'A');
    king.second=innum-1;

    while(fin>>inch){
        fin>>innum;
        knights.push_back(pair<int,int>(int(inch-'A'),innum-1));
    }

    int xsum=0,ysum=0;
    if(knights.size()>1){
        for(vector< pair<int,int> >::iterator itr=knights.begin();itr!=knights.end();++itr){
            xsum+=itr->first;
            ysum+=itr->second;
        }
        xsum/=knights.size();
        ysum/=knights.size();
    }
    else if(!knights.empty()){
        xsum=king.first;
        ysum=king.second;
    }
    else {
        fout<<0<<endl;
        return 0;
    }

    if(R==1 || C==1){
        int i,smove=0;
        int knx=knights[0].first,kny=knights[0].second;
        for(i=1;i<(int)knights.size();++i)
            if(knights[i].first!=knx || knights[i].second!=kny)break;
        if(i<(int)knights.size()){
            fout<<0<<endl;
            return 0;
        }

        smove=(knx-king.first)+(kny-king.second);
        if(smove<0)smove=-smove;
        fout<<smove<<endl;
        return 0;
    }

    int minmove=infinite;
    for(int gx=xsum-2;gx<=xsum+2;++gx)
        for(int gy=ysum-2;gy<=ysum+2;++gy){
            if(!OnBoard(gx,gy))continue;
            int tmpsum=0;
            if(R>=3 && C>=3){
                for(int i=0;i<(int)knights.size();++i)
                    tmpsum+=knmove(knights[i].first,knights[i].second,gx,gy);
            }
            else {
                for(int i=0;i<(int)knights.size();++i){
                    tmpsum+=knmove_narrow(knights[i].first,knights[i].second,gx,gy);
                }
            }
            if(tmpsum>=minmove)continue;
            for(int px=king.first-2;px<=king.first+2;++px)
                for(int py=king.second-2;py<=king.second+2;++py){
                    if(!OnBoard(px,py))continue;
                    if(R>=3 && C>=3){
                        for(int i=0;i<(int)knights.size();++i){
                            int tmp=tmpsum
                                -knmove(knights[i].first,knights[i].second,gx,gy)
                                +knmove(knights[i].first,knights[i].second,px,py)
                                +knmove(px,py,gx,gy)
                                +kgmove(king.first,king.second,px,py);
                            minmove=min(minmove,tmp);
                        }
                    }
                    else {
                        for(int i=0;i<(int)knights.size();++i){
                            int tmp=tmpsum
                                -knmove_narrow(knights[i].first,knights[i].second,gx,gy)
                                +knmove_narrow(knights[i].first,knights[i].second,px,py)
                                +knmove_narrow(px,py,gx,gy)
                                +kgmove(king.first,king.second,px,py);
                            minmove=min(minmove,tmp);
                        }
                    }
                }
        }

    fout<<minmove<<endl;
    return 0;
}