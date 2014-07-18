#include<iostream>
#include<vector>
using namespace std;

struct CSubject{
    int score;
    int nsubjects;
    CSubject(){}
    CSubject(int sc, int nsub)
        :score(sc), nsubjects(nsub){}
};
vector<CSubject> subs;

long long ncomb(int ttsc){
    vector<long long> last, cur;
    last.assign(ttsc+1, 0);
    cur.resize(ttsc+1);

    last[0] = 1;
    for(int i=0; i<(int)subs.size(); ++i){
        for(int j=0; j<=ttsc; ++j){
            cur[j] = last[j];
            for(int idx=j-subs[i].score, cnt=1; idx>=0 && cnt<=subs[i].nsubjects; idx-=subs[i].score, ++cnt){
                cur[j] += last[idx];
            }
        }
        cur.swap(last);
    }
    return last[ttsc];
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("i.txt", "r", stdin);
    freopen("o.txt", "w", stdout);
#endif
    int t, totalscore, k, score, nsubject;
    cin>>t;
    while(t--){
        subs.clear();
        cin>>totalscore>>k;
        while(k--){
            cin>>score>>nsubject;
            subs.push_back(CSubject(score, nsubject));
        }
        cout<<ncomb(totalscore)<<'\n';
    }
}
