#include<iostream>
#include<vector>
using namespace std;
int main(){
    vector<int> rems;
    int a, b, c;
    while(cin>>a>>b){
        a %= 10;
        rems.assign(1, a);
        while((c=(rems.back()*a)%10) != rems.front())
            rems.push_back(c);
        if(b == 0)cout << "1\n";
        else cout << rems[(b-1)%rems.size()] << '\n';
    }
}
