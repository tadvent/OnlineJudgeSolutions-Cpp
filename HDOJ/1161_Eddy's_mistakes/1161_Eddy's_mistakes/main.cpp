#include<iostream>
#include<iterator>
#include<algorithm>
using namespace std;

int main(){
#ifndef ONLINE_JUDGE
    freopen("i.txt", "r", stdin);
    freopen("o.txt", "w", stdout);
#endif
    transform(istreambuf_iterator<char>(cin), istreambuf_iterator<char>(),
        ostreambuf_iterator<char>(cout), tolower);
}
