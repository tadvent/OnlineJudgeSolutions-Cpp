#include<iostream>
#include<algorithm>
using namespace std;
int num[100], n, x;
int main(){
    while(cin>>n>>x && (n||x)){
        for(int i=0; i<n; ++i)cin>>num[i];
        int *pos = upper_bound(num, num+n, x);
        for(int *p = num; p != pos; ++p)
            cout << *p << ' ';
        cout << x;
        for(int *p = pos; p != num+n; ++p)
            cout << ' ' << *p;
        cout << '\n';
    }
}
