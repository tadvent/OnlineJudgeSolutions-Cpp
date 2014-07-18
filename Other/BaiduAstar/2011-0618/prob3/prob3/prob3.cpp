#include<iostream>
#include<cstdio>
using namespace std;

int main(){
#ifdef LOCAL
    freopen("i.txt", "r", stdin);
    freopen("o.txt", "w", stdout);
#endif
    int n;
    while(cin >> n && n != 0){
        cin.ignore();
        for(int i=0; i<n; ++i){
            cin.ignore(20, '\n');
        }
        cout << n << '\n';
    }
}
