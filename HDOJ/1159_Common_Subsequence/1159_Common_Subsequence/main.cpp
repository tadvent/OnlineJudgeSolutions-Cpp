#include<iostream>
#include<vector>
#include<string>
using namespace std;

int comlen(const string &str1, const string &str2){
    static vector<int> pre, cur;
    pre.assign(str1.length() + 1, 0);
    cur.assign(str1.length() + 1, 0);
    for(string::const_reverse_iterator it = str2.rbegin(); it != str2.rend(); ++it){
        for(int idx = str1.length() - 1; idx >= 0; --idx){
            if(str1[idx] == *it){
                cur[idx] = pre[idx + 1] + 1;
            } else {
                cur[idx] = max(cur[idx + 1], pre[idx]);
            }
        }
        pre.swap(cur);
    }
    return pre[0];
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("i.txt", "r", stdin);
    freopen("o.txt", "w", stdout);
#endif
    string str1, str2;
    while(cin >> str1 >> str2)
        cout << comlen(str1, str2) << '\n';
}
