#include<map>
#include<string>
#include<iostream>
using namespace std;

class Judger{
    map<string, int> lose;
public:
    void add(const string &w, const string &l){
        map<string, int>::iterator pos;
        if((pos = lose.find(w)) == lose.end()){
            lose.insert(make_pair(w, 0));
        }
        if((pos = lose.find(l)) == lose.end()){
            lose.insert(make_pair(l, 1));
        } else ++(pos->second);
    }
    void clear(){
        lose.clear();
    }
    bool CanJudge(){
        bool can = false;
        for(map<string, int>::const_iterator it = lose.begin();
            it != lose.end(); ++it){
                if(it->second == 0){
                    if(can)return false;
                    else can = true;
                }
        }
        return can;
    }
};

int main(){
    freopen("i.txt", "r", stdin);
    freopen("o.txt", "w", stdout);
    int n;
    string winner, loser;
    Judger jug;
    while(cin>>n && n){
        jug.clear();
        while(n--){
            cin>>winner>>loser;
            jug.add(winner, loser);
        }
        cout<<(jug.CanJudge()? "Yes\n":"No\n");
    }
}
