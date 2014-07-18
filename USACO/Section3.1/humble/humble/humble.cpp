/*
ID: wjl1241
PROG: humble
LANG: C++
*/

// Version 1.....TLE
/*
#include<fstream>
#include<queue>
#include<vector>
#include<algorithm>
using namespace std;

struct hum_idx_mulidx{
    long newhum;
    size_t idx;
    size_t mulidx;
    hum_idx_mulidx(long lnewhum, size_t lidx, size_t lmulidx):newhum(lnewhum),idx(lidx),mulidx(lmulidx){}
    bool operator>(const hum_idx_mulidx &comp)const{
        return newhum>comp.newhum;
    }
};

priority_queue<hum_idx_mulidx,vector<hum_idx_mulidx>,greater<hum_idx_mulidx> > humq;
vector<long> S;
vector<long> humnum;

//bool IsHumble(long num){
//    //the numbers less than num should be judged before
//    for(vector<long>::iterator itr=S.begin();itr!=S.end();++itr){
//        if(0 == num%(*itr)){
//            int tmp=num/(*itr);
//            if(1==tmp)return true;
//            return humnum.find(tmp)!=humnum.end();
//        }
//    }
//    return false;
//}

int main(){
    ifstream fin("humble.in");
    ofstream fout("humble.out");
    unsigned int k,n;
    fin>>k>>n;
    S.resize(k);
    for(size_t i=0;i<k;++i){
        fin>>S[i];
    }
    sort(S.begin(),S.end());

    humnum.push_back(1);
    humq.push(hum_idx_mulidx(S[0],0,0));
    while(humnum.size()<n+1){
        hum_idx_mulidx humidxpair=humq.top();
        humq.pop();
        humq.push(hum_idx_mulidx(humidxpair.newhum*S[0],humnum.size(),0));
        if(humidxpair.newhum>humnum.back()){
            humnum.push_back(humidxpair.newhum);
        }
        if(++humidxpair.mulidx<S.size()){
            humq.push(hum_idx_mulidx(humnum[humidxpair.idx]*S[humidxpair.mulidx],humidxpair.idx,humidxpair.mulidx));
        }
    }
    fout<<humnum[n]<<endl;

    return 0;
}

*/

//  Version 2.......

#include<fstream>
#include<queue>
#include<vector>
using namespace std;

struct humset{
    long num;
    int s_num;
    int hum_indx;
    humset(long new_humnum, int s, int hum_index)
        :num(new_humnum),s_num(s),hum_indx(hum_index){}

    bool operator> (const humset &comp) const {
        return num>comp.num;
    }
};

priority_queue<humset, vector<humset>, greater<humset> > pq;
vector<long> humnum;

int main(){
    ifstream fin("humble.in");
    ofstream fout("humble.out");
    int k,nth;
    fin>>k>>nth;
    for(int i=0;i<k;++i){
        long tmp;
        fin>>tmp;
        pq.push(humset(tmp,tmp,0));
    }
    humnum.push_back(1);

    while(int(humnum.size())<=nth){
        humset the_humset=pq.top();
        pq.pop();
        if(the_humset.num>humnum.back()){
            humnum.push_back(the_humset.num);
        }
        ++the_humset.hum_indx;
        pq.push(humset(the_humset.s_num*humnum[the_humset.hum_indx],the_humset.s_num,the_humset.hum_indx));
    }

    fout<<humnum[nth]<<endl;

    return 0;
}