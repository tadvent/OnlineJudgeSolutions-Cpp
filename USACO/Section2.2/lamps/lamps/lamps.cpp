/*
ID: wjl1241
PROG: lamps
LANG: C++
*/

#include<fstream>
#include<vector>
#include<set>
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
            if(i<0)return false;    //Ñ­»·½áÊø
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

class bits{
    unsigned char lamps;//six bits on the right represent the six lamps

public:
    bits():lamps(0x00){}
    int operator[](int n)const{
        n=(n-1)%6;
        return (lamps>>n)&0x01;
    }
    bool IsAccord(const bits &flag, const bits &dest){
        return ((lamps&flag.lamps) == dest.lamps);
    }
    void setbit(int n, int value){
        n=(n-1)%6;
        lamps|=(value<<n);
    }
    void setbits(unsigned char value){
        lamps=value;
    }
    unsigned char getbits(void){
        return lamps;
    }
    void op(const int idx){
        switch(idx){
            case 1:
                lamps^=0x3f;
                break;
            case 2:
                lamps^=0x15;
                break;
            case 3:
                lamps^=0x2a;
                break;
            case 4:
                lamps^=0x09;
                break;
        }
    }
    void init(void){
        setbits(0x3f);
    }
    bool operator<(const bits& comp)const{
        for(int i=0;i<6;++i){
            if(((lamps>>i)&0x1) < ((comp.lamps>>i)&0x1))return true;
            else if(((lamps>>i)&0x1) > ((comp.lamps>>i)&0x1))return false;
        }
        return false;
    }
};

int main(){
    ifstream fin("lamps.in");
    ofstream fout("lamps.out");
    int n,c,tmp;
    bits dest,flag;
    fin>>n>>c;
    fin>>tmp;
    while(tmp!=-1){
        dest.setbit(tmp,1);
        flag.setbit(tmp,1);
        fin>>tmp;
    }
    fin>>tmp;
    while(tmp!=-1){
        if(flag[tmp]==1){ //ON and OFF conflict
            fout<<"IMPOSSIBLE"<<endl;
            return 0;
        }
        flag.setbit(tmp,1);
        fin>>tmp;
    }

    bits lamps;
    set<bits> results;
    combination comb;
    switch(c){
        case 0:
            lamps.init();
            if(lamps.IsAccord(flag,dest))results.insert(lamps);
            break;
        case 1:
            comb.init(4,1);
            while(comb.next()){
                lamps.init();
                lamps.op(comb[0]+1);
                if(lamps.IsAccord(flag,dest))results.insert(lamps);
            }
            break;
        case 2:
            lamps.init();
            if(lamps.IsAccord(flag,dest))results.insert(lamps);
            comb.init(4,2);
            while(comb.next()){
                lamps.init();
                lamps.op(comb[0]+1);
                lamps.op(comb[1]+1);
                if(lamps.IsAccord(flag,dest))results.insert(lamps);
            }
            break;
        default:
            c&=0x1;
            if(c){  // c is odd
                comb.init(4,1);
                while(comb.next()){
                    lamps.init();
                    lamps.op(comb[0]+1);
                    if(lamps.IsAccord(flag,dest))results.insert(lamps);
                }
                comb.init(4,3);
                while(comb.next()){
                    lamps.init();
                    lamps.op(comb[0]+1);
                    lamps.op(comb[1]+1);
                    lamps.op(comb[2]+1);
                    if(lamps.IsAccord(flag,dest))results.insert(lamps);
                }
            }
            else {      // c is even
                lamps.init();
                if(lamps.IsAccord(flag,dest))results.insert(lamps);
                comb.init(4,2);
                while(comb.next()){
                    lamps.init();
                    lamps.op(comb[0]+1);
                    lamps.op(comb[1]+1);
                    if(lamps.IsAccord(flag,dest))results.insert(lamps);
                }
                lamps.init();
                lamps.op(1);
                lamps.op(2);
                lamps.op(3);
                lamps.op(4);
                if(lamps.IsAccord(flag,dest))results.insert(lamps);
            }
            break;
    }

    if(results.empty()){
        fout<<"IMPOSSIBLE"<<endl;
    }
    else for(set<bits>::iterator itr=results.begin();itr!=results.end();++itr){
        for(int i=1;i<=n;++i)fout<<(*itr)[i];
        fout<<endl;
    }

    return 0;
}