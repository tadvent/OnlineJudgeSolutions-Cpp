/*
ID: wjl1241
PROG: spin
LANG: C++
*/

#include<fstream>
#include<vector>
//#include<list>
//#include<algorithm>
//#include<utility>
using namespace std;

struct Wedge{
    int start;
    int end;
    Wedge(void):start(0),end(0){}
    Wedge(int s, int e):start(s),end(e){}

    bool operator<(const Wedge &comp){
        return start<comp.start;
    }
};

struct Wheel{
    //int angle;
    int speed;
    vector< Wedge > wedge;

    Wheel(void){
    }
    void rotate(void){
        //angle=(angle+speed)%360;
        for(vector< Wedge >::iterator itr=wedge.begin();itr!=wedge.end();++itr){
            itr->start = (itr->start + speed)%360;
            itr->end = (itr->end + speed)%360;
            if(itr->end < itr->start)itr->end+=360;
        }
    }
};

Wheel wheel[5];

void nextsecond(void){
    for(int i=0;i<5;++i)wheel[i].rotate();
}

//bool cover ( vector< pair<int,int> > &wedge, int coverstart, int coverend ){ //start <= cover <= end
//    for(vector< pair<int,int> >::iterator itr=wedge.begin();itr!=wedge.end();++itr){
//        int end=itr->first+itr->second;
//        if(itr->first < coverstart){
//            if(end < coverstart)continue;
//        }
//        else {
//            if(coverend < itr->first)continue;
//        }
//        itr->first=max(itr->first,coverstart);
//        itr->second= min(end,coverend) - itr->first;
//    }
//}

bool compare( vector< Wedge > &wedge1, const vector< Wedge > &wedge2 ){
    vector< Wedge > newed;
    for(vector<Wedge>::iterator itr1=wedge1.begin();itr1!=wedge1.end();++itr1){
        for(vector<Wedge>::const_iterator itr2=wedge2.begin();itr2!=wedge2.end();++itr2){
            if(itr1->start < itr2->start){
                //if(itr1->end < itr2->start && (itr2->end - 360 < itr1->start) )continue;
                if(itr1->end >= itr2->start){
                    newed.push_back(Wedge( itr2->start, min(itr1->end,itr2->end) ));
                }
                if(itr2->end - 360 >= itr1->start){
                    newed.push_back(Wedge( itr1->start, min(itr1->end,itr2->end-360) ));
                }
            }
            else {
                //if(itr2->end < itr1->start && (itr1->end - 360 < itr2->start) )continue;
                if(itr2->end >= itr1->start){
                    newed.push_back(Wedge( itr1->start, min(itr1->end,itr2->end) ));
                }
                if(itr1->end - 360 >= itr2->start){
                    newed.push_back(Wedge( itr2->start, min(itr1->end-360,itr2->end) ));
                }
            }
            //newed.push_back(Wedge( max(itr1->start,itr2->start), min(itr1->end,itr2->end) ));
        }
    }
    //sort(newed.begin(),newed.end());
    if(newed.empty())return false;
    wedge1=newed;
    return true;
}

bool IsAlign(void){
    vector<Wedge> tmpwed=wheel[0].wedge;
    for(int i=1;i<5;++i){
        if(!compare(tmpwed,wheel[i].wedge))return false;
    }
    return true;
}

int main(){
    ifstream fin("spin.in");
    ofstream fout("spin.out");
    for(int i=0;i<5;++i){
        fin>>wheel[i].speed;
        int w;
        fin>>w;
        wheel[i].wedge.resize(w);
        for(int j=0;j<w;++j){
            int st,ext;
            fin>>st>>ext;
            wheel[i].wedge[j].start=st;
            wheel[i].wedge[j].end=st+ext;
        }
    }

    int time=0;
    while(!IsAlign() && time<360){
        ++time;
        nextsecond();
    }

    if( 360 == time)fout<<"none"<<endl;
    else fout<<time<<endl;

    return 0;
}