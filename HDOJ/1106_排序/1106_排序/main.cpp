#include<iostream>
#include<sstream>
#include<string>
#include<iterator>
#include<vector>
#include<algorithm>
using namespace std;
struct ch5{
    char operator()(char ch)const{
        return (ch == '5')? ' ':ch;
    }
};
int main(){
#ifndef ONLINE_JUDGE
    freopen("i.txt", "r", stdin);
    freopen("o.txt", "w", stdout);
#endif
    vector<long> v;
    v.reserve(500);
    stringstream ss;
    string str;
    str.reserve(1001);
    while(getline(cin, str)){
        transform(str.begin(), str.end(), ostreambuf_iterator<char>(ss), ch5());
        copy(istream_iterator<long>(ss), istream_iterator<long>(), back_inserter(v));
        sort(v.begin(), v.end());
        copy(v.begin(), --v.end(), ostream_iterator<long>(cout, " "));
        cout << v.back() << '\n';
        ss.clear();
        v.clear();
    }
}
