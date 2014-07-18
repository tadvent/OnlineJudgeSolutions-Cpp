/*
ID: wjl1241
PROG: packrec
LANG: C++
*/

#include<fstream>
#include<vector>
#include<algorithm>
using namespace std;

class rect {
public:
    int x;
    int y;
public:
    rect(void):x(0),y(0){}
    rect(int _x, int _y):x(_x),y(_y){}
    void clear(void){
        x=0;y=0;
    }
    void swap(void){
        ::swap(x,y);
    }
    bool operator==(const rect &r)const{
        return (x==r.x && y==r.y);
    }
    bool operator<(const rect &r)const{
        if(x<r.x)return true;
        if(x>r.x)return false;
        if(y<r.y)return true;
        return false;
    }
};

//bool operator==(const rect&l,const rect &r){
//    return (l.x==r.x && l.y==r.y);
//}
//
//bool operator<(const rect &l,const rect &r){
//    if(l.x<r.x)return true;
//    if(l.x>r.x)return false;
//    if(l.y<r.y)return true;
//    return false;
//}

template <typename T>
class arrange{
    vector<T> vec;
    int n;
    int m;
    int im;
    int idx;
    int direct;
    bool turn;
public:
    arrange(void){}
    arrange(T *begin,int N):vec(begin,begin+N),
        n(N),m(1),im(0),idx(N-1),direct(-1),turn(false){
        for(int i=3;i<N;++i)m*=i;
    }
    bool init(T *begin, int N){
        vec.reserve(N);
        for(int i=0;i<N;++i)vec.push_back(*(begin+i));
        n=N;m=1;im=0;idx=N-1;direct=-1;turn=false;
        for(int i=3;i<N;++i)m*=i;
        return true;
    }
    const T &operator[](int i)const{
        return vec[i];
    }
    bool next(){
        if( idx==n-1 && turn ){
            ++im;
            if(im >= m)return false;
            swap(vec[0],vec[1]);
            turn=false;
            direct*=-1;
            return true;
        }
        if( idx==0 && turn ){
            swap(vec[n-1],vec[n-2]);
            turn=false;
            direct*=-1;
            return true;
        }
        swap(vec[idx],vec[idx+direct]);
        idx+=direct;
        if(idx==n-1 || idx==0)turn=true;
        return true;
    }
};

int minarea=10000;
vector<rect> minrectvec;
void check(int area,rect rec){
    if(rec.x>rec.y)rec.swap();
    if(area < minarea){
        minarea=area;
        minrectvec.clear();
        minrectvec.push_back(rec);
        return;
    }
    if(area == minarea){
        if(find(minrectvec.begin(),minrectvec.end(),rec)==minrectvec.end())
            minrectvec.push_back(rec);
    }
}

int main(){
    rect orec[4];   //Original rects
    rect rrec[4];   //rotated rects

    ifstream fin("packrec.in");
    ofstream fout("packrec.out");
    for(int i=0;i<4;++i)fin>>orec[i].x>>orec[i].y;
    int init[4]={0,1,2,3};
    arrange<int> idx(init,4);

    do {
        for(int rotate=0;rotate<16;++rotate){
            int bitmove=rotate;
            for(int i=0;i<4;++i){
                if( bitmove & 0x0001 ){
                    rrec[i].x=orec[i].y;
                    rrec[i].y=orec[i].x;
                }
                else {
                    rrec[i].x=orec[i].x;
                    rrec[i].y=orec[i].y;
                }
                bitmove>>=1;
            }


            //calculate the six layouts
            int tmparea;
            rect tmprec;

            tmprec.clear();
            for(int i=0;i<4;++i){
                tmprec.x+=rrec[idx[i]].x;
                if(rrec[idx[i]].y>tmprec.y)tmprec.y=rrec[idx[i]].y;
            }
            tmparea=tmprec.x*tmprec.y;
            check(tmparea,tmprec);

            tmprec.clear();
            for(int i=0;i<3;++i){
                tmprec.x+=rrec[idx[i]].x;
                if(rrec[idx[i]].y>tmprec.y)tmprec.y=rrec[idx[i]].y;
            }
            tmprec.x=(tmprec.x>rrec[idx[3]].x)?tmprec.x:rrec[idx[3]].x;
            tmprec.y+=rrec[idx[3]].y;
            tmparea=tmprec.x*tmprec.y;
            check(tmparea,tmprec);

            tmprec.clear();
            tmprec.x=rrec[idx[0]].x+rrec[idx[1]].x;
            tmprec.x=(tmprec.x>rrec[idx[2]].x)?tmprec.x:rrec[idx[2]].x;
            tmprec.x+=rrec[idx[3]].x;
            tmprec.y=(rrec[idx[0]].y>rrec[idx[1]].y)?rrec[idx[0]].y:rrec[idx[1]].y;
            tmprec.y+=rrec[idx[2]].y;
            tmprec.y=(tmprec.y>rrec[idx[3]].y)?tmprec.y:rrec[idx[3]].y;
            tmparea=tmprec.x*tmprec.y;
            check(tmparea,tmprec);

            tmprec.clear();
            tmprec.x=(rrec[idx[1]].x>rrec[idx[2]].x)?rrec[idx[1]].x:rrec[idx[2]].x;
            tmprec.x+=rrec[idx[0]].x+rrec[idx[3]].x;
            tmprec.y=rrec[idx[1]].y+rrec[idx[2]].y;
            if(tmprec.y<rrec[idx[0]].y)tmprec.y=rrec[idx[0]].y;
            if(tmprec.y<rrec[idx[3]].y)tmprec.y=rrec[idx[3]].y;
            tmparea=tmprec.x*tmprec.y;
            check(tmparea,tmprec);

            //tmprec.clear();
            //tmprec.x=(rrec[idx[0]].x>rrec[idx[1]].x)?rrec[idx[0]].x:rrec[idx[1]].x;
            //tmprec.x+=rrec[idx[2]].x+rrec[idx[3]].x;
            //tmprec.y=rrec[idx[0]].y+rrec[idx[1]].y;
            //if(tmprec.y<rrec[idx[2]].y)tmprec.y=rrec[idx[2]].y;
            //if(tmprec.y<rrec[idx[3]].y)tmprec.y=rrec[idx[3]].y;
            //tmparea=tmprec.x*tmprec.y;
            //check(tmparea,tmprec);

            tmprec.clear();
            int tmpx1=rrec[idx[0]].x+rrec[idx[3]].x;
            int tmpx2=rrec[idx[1]].x+rrec[idx[2]].x;
            int tmpy1=rrec[idx[0]].y+rrec[idx[1]].y;
            int tmpy2=rrec[idx[2]].y+rrec[idx[3]].y;
            tmprec.x=(tmpx1>tmpx2)?tmpx1:tmpx2;
            tmprec.y=(tmpy1>tmpy2)?tmpy1:tmpy2;
            if(rrec[idx[0]].x+rrec[idx[2]].x>tmprec.x
                && rrec[idx[0]].y+rrec[idx[2]].y>tmprec.y)continue;
            if(rrec[idx[1]].x+rrec[idx[3]].x>tmprec.x
                && rrec[idx[1]].y+rrec[idx[3]].y>tmprec.y)continue;
            tmparea=tmprec.x*tmprec.y;
            check(tmparea,tmprec);
        }
    }while(idx.next());

    stable_sort(minrectvec.begin(),minrectvec.end());

    fout<<minarea<<'\n';
    for(size_t i=0;i<minrectvec.size();++i)
        fout<<minrectvec[i].x<<' '<<minrectvec[i].y<<endl;

    //system("pause");
    return 0;
}