#include<iostream>
#include<string>
#include<functional>
#include<algorithm>
using namespace std;

int target;
string s;
int crack[5];

bool dfs(int idx = 0){
    if(idx == 5){
        int a(s[crack[0]]), b(s[crack[1]]), c(s[crack[2]]), d(s[crack[3]]), e(s[crack[4]]);
        if(a - b*b + c*c*c - d*d*d*d + e*e*e*e*e == target)return true;
        else return false;
    }
    int &il(crack[idx]);
    bool dup;
    for(il = 0; il < (int)s.size(); ++il){
        dup = false;
        for(int i = 0; i < idx; ++i)if(crack[i] == il)dup = true;
        if(dup)continue;
        if(dfs(idx + 1))
            return true;
    }
    return false;
}

int main(){
    while(cin>>target>>s && (target || s != "END")){
        transform(s.begin(), s.end(), s.begin(), bind2nd(minus<char>(), 'A'-1));
        sort(s.begin(), s.end(), greater<char>());
        if(dfs()){
            for(int i=0; i<5; ++i)
                cout << char(s[crack[i]] + 'A' - 1);
            cout << '\n';
        }
        else
            cout << "no solution\n";
    }
}
