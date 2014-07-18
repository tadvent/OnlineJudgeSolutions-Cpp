/*
ID: wjl1241
PROG: clocks
LANG: C++
*/

#include<fstream>
#include<vector>
using namespace std;

class clocks {
public:
    int clock[9];

    bool check(void){
        for(int i=0;i<9;++i)
            if(clock[i]!=0)return false;
        return true;
    }

    void op(int i){
        switch(i){
            case 1:
                clock[0]=(clock[0]+3)%12;
                clock[1]=(clock[1]+3)%12;
                clock[3]=(clock[3]+3)%12;
                clock[4]=(clock[4]+3)%12;
                break;
            case 2:
                clock[0]=(clock[0]+3)%12;
                clock[1]=(clock[1]+3)%12;
                clock[2]=(clock[2]+3)%12;
                break;
            case 3:
                clock[1]=(clock[1]+3)%12;
                clock[2]=(clock[2]+3)%12;
                clock[5]=(clock[5]+3)%12;
                clock[4]=(clock[4]+3)%12;
                break;
            case 4:
                clock[0]=(clock[0]+3)%12;
                clock[6]=(clock[6]+3)%12;
                clock[3]=(clock[3]+3)%12;
                break;
            case 5:
                clock[5]=(clock[5]+3)%12;
                clock[1]=(clock[1]+3)%12;
                clock[3]=(clock[3]+3)%12;
                clock[4]=(clock[4]+3)%12;
                clock[7]=(clock[7]+3)%12;
                break;
            case 6:
                clock[2]=(clock[2]+3)%12;
                clock[5]=(clock[5]+3)%12;
                clock[8]=(clock[8]+3)%12;
                break;
            case 7:
                clock[6]=(clock[6]+3)%12;
                clock[7]=(clock[7]+3)%12;
                clock[3]=(clock[3]+3)%12;
                clock[4]=(clock[4]+3)%12;
                break;
            case 8:
                clock[6]=(clock[6]+3)%12;
                clock[7]=(clock[7]+3)%12;
                clock[8]=(clock[8]+3)%12;
                break;
            case 9:
                clock[5]=(clock[5]+3)%12;
                clock[7]=(clock[7]+3)%12;
                clock[8]=(clock[8]+3)%12;
                clock[4]=(clock[4]+3)%12;
        }
    }
};

template<typename T>
class result{
public:
    vector<T> vec;
    bool operator<(const result &r)const{
        if(vec.size()<r.vec.size())return true;
        if(vec.size()>r.vec.size())return false;
        for(size_t i=0;i<vec.size();++i){
            if(vec[i]<r.vec[i])return true;
            if(vec[i]>r.vec[i])return false;
        }
        return false;
    }
};

result<int> minrst;
result<int> tmprst;
int callnum[10]={0,0,0,0,0,0,0,0,0,0};

void nextsearch(clocks clk,int callid){
    if(callnum[callid]>=3)return;
    clk.op(callid);
    tmprst.vec.push_back(callid);
    ++callnum[callid];

    if(clk.check()){
        if(minrst.vec.empty() || tmprst<minrst)minrst=tmprst;
        tmprst.vec.pop_back();
        --callnum[callid];
        return;
    }

    for(int i=callid;i<10;++i)nextsearch(clk,i);
    tmprst.vec.pop_back();
    --callnum[callid];
}

void search(clocks clk){
    if(clk.check())return;
    for(int i=1;i<10;++i){
        nextsearch(clk,i);
    }
}

int main(){
    ifstream fin("clocks.in");
    ofstream fout("clocks.out");
    clocks clk;
    for(int i=0;i<9;++i)fin>>clk.clock[i];
    for(int i=0;i<9;++i)clk.clock[i]%=12;

    search(clk);
    fout<<minrst.vec[0];
    for(size_t i=1;i<minrst.vec.size();++i)
        fout<<' '<<minrst.vec[i];
    fout<<endl;

    return 0;
}