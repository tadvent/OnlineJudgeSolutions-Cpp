/*
ID: wjl1241
PROG: contact
LANG: C++
*/

#include<fstream>
#include<vector>
#include<cmath>
#include<map>
//#include<iomanip>
using namespace std;

struct freq{
    int minlen;
    int maxlen;
    vector<vector<int> > matrix;
    vector<int> &operator[](int n){
        return matrix[n-minlen];
    }
    freq(void):minlen(0),maxlen(0){
    }

    void setlength(int minlength, int maxlength){
        minlen=minlength;
        maxlen=maxlength;
        matrix.resize(maxlen-minlen+1);
        for(int i=0;i<(int)matrix.size();++i){
            matrix[i].resize(int(pow(float(2),float(minlen+i))),0);
        }
    }
};

freq pfreq;
map<int,vector<pair<int,int> > >  freq_map;

int main(){
    ifstream fin("contact.in");
    ofstream fout("contact.out");
    int a,b,n,patten=0,cnt=2;
    char ch;
    fin>>a>>b>>n;
    pfreq.setlength(a,b);

    while(fin>>ch){
        switch(ch){
            case '0':
                patten<<=1;
                break;
            case '1':
                patten=(patten<<1)|0x1;
                break;
        }
        int upper=min(cnt,b+1);
        for(int len=a;len<upper;++len){
            ++pfreq[len][patten&(~((~0x0)<<len))];
        }
        ++cnt;
    }

    for(int len=a;len<=b;++len){
        for(int i=0;i<(int)pfreq[len].size();++i)if(pfreq[len][i]>0){
            if((int)freq_map.size()<n){
                map<int,vector<pair<int,int> > >::iterator itr;
                if((itr=freq_map.find(pfreq[len][i]))!=freq_map.end()){
                    itr->second.push_back(pair<int,int>(len,i));
                }
                else {
                    freq_map.insert(pair<int,vector<pair<int,int> > >(pfreq[len][i],vector<pair<int,int> >(1,pair<int,int>(len,i))));
                }
            }
            else if(pfreq[len][i]>=freq_map.begin()->first){
                map<int,vector<pair<int,int> > >::iterator itr;
                if((itr=freq_map.find(pfreq[len][i]))!=freq_map.end()){
                    itr->second.push_back(pair<int,int>(len,i));
                }
                else {
                    freq_map.erase(freq_map.begin());
                    vector<pair<int,int> > tmp;
                    tmp.push_back(pair<int,int>(len,i));
                    freq_map.insert(pair<int,vector<pair<int,int> > >(pfreq[len][i],tmp));
                }
            }
        }
    }

    for(map<int,vector<pair<int,int> > >::reverse_iterator ritr=freq_map.rbegin();ritr!=freq_map.rend();++ritr){
        fout<<ritr->first<<'\n';
        int printcnt=0;
        for(vector<pair<int,int> >::iterator itr=ritr->second.begin();itr!=ritr->second.end();++itr){
            if(printcnt%6!=0)fout<<' ';
            for(int i=itr->first-1;i>=0;--i)fout<<((itr->second>>i)&0x1);
            if((++printcnt)%6==0)fout<<'\n';
        }
        if(printcnt%6!=0)fout<<'\n';
    }

    return 0;
}