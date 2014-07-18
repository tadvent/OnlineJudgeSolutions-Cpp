/*
ID: wjl1241
PROG: holstein
LANG: C++
*/

#include<fstream>
#include<vector>
using namespace std;

class combination {
    vector<size_t> vec;
    int n;
    int r;
public:
    bool init(int N, int r){
        if(N<r || N<0 || r<0)return false;
        combination::n=N;
        combination::r=r;
        vec.resize(r);
        for(int i=0;i<r;++i)vec[i]=i;
        if(r>0)vec[r-1]=r-2;
        return true;
    }
    bool next(void){
        if(vec.empty())return false;
        int i=r-1;
        while((int)vec[i]>=n-r+i){
            --i;
            if(i<0)return false;
        }
        size_t tmp=vec[i];
        for(int idx=i;idx<r;++idx){
            vec[idx]=++tmp;
        }
        return true;
    }
    size_t operator[](const int i)const{
        return vec[i];
    }
};

int main(){
    int nv,ng;
    vector<int> vitm;
    vector< vector<int> > feed;

    ifstream fin("holstein.in");
    ofstream fout("holstein.out");

    fin>>nv;
    vitm.resize(nv);
    for(int i=0;i<nv;++i)fin>>vitm[i];
    fin>>ng;
    feed.resize(ng);
    for(int i=0;i<ng;++i){
        feed[i].resize(nv);
        for(int j=0;j<nv;++j)fin>>feed[i][j];
    }

    combination comb;
    for(int i=1;i<=ng;++i){
        comb.init(ng,i);
        while(comb.next()){
            int vitmidx;
            for(vitmidx=0;vitmidx<nv;++vitmidx){
                int eachvitm=0;
                for(int j=0;j<i;++j){
                    eachvitm+=feed[comb[j]][vitmidx];
                }
                if(eachvitm<vitm[vitmidx])break;
            }
            if(vitmidx<nv)continue;
            fout<<i;
            for(int ii=0;ii<i;++ii)fout<<' '<<comb[ii]+1;
            fout<<endl;
            return 0;
        }
    }

    return 0;
}