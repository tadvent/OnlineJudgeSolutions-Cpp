#include<iostream>
#include<iomanip>
#include<string>
#include<vector>
#include<algorithm>
using namespace std;

struct member{
    string name;
    int solve;
    int score;
    member(const string& nm):solve(0), score(0), name(nm){}
    bool operator>(const member &sc)const{
        if(solve > sc.solve ||
            solve == sc.solve && (score < sc.score ||
            score == sc.score && name < sc.name))
            return true;
        return false;
    }
};

vector<member> results;
vector<int> idxs;

template<class Con_T>
class _greatersc{
    const Con_T &con;
public:
    _greatersc(const Con_T &C):con(C){}
    bool operator()(int idx1, int idx2)const{
        return con[idx1] > con[idx2];
    }
};

template<class Con_T>
_greatersc<Con_T> greatersc(const Con_T &C){
    return _greatersc<Con_T>(C);
}

int main(){
    freopen("i.txt", "r", stdin);
    freopen("o.txt", "w", stdout);
    int nProb, mScore;
    string name;
    name.reserve(10);

    // input
    cin>>nProb>>mScore;
    while(cin>>name){
        results.push_back(member(name));
        member &mb(results.back());
        int sc, fail;
        for(int i=0; i<nProb; ++i){
            cin>>sc;
            if(sc<=0)continue;
            ++mb.solve;
            mb.score += sc;
            if(cin.get() == '('){
                cin>>fail;
                mb.score += mScore*fail;
                cin.ignore();
            }
        }
    }

    // sort
    idxs.resize(results.size());
    for(int i=0; i<(int)idxs.size(); ++i)
        idxs[i] = i;
    sort(idxs.begin(), idxs.end(), greatersc(results));

    // output
    for(vector<int>::const_iterator it = idxs.begin();
        it != idxs.end(); ++it){
            const member &mb(results[*it]);
            cout<<left<<setw(10)<<mb.name
                <<right<<setw(3)<<mb.solve
                <<setw(5)<<mb.score<<'\n';
    }
}
