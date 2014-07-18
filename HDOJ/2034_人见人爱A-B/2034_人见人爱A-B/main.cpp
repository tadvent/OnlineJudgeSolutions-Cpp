#include<iostream>
#include<iterator>
#include<vector>
#include<numeric>
#include<algorithm>
using namespace std;
int main(){
    int n,m;
    vector<int> A,B,C;
    A.reserve(100); B.reserve(100); C.reserve(100);
    while(cin>>n>>m&&(n||m)){
        A.clear(); B.clear(); C.clear();
        int num;
        while(n--){cin>>num; A.push_back(num);}
        while(m--){cin>>num; B.push_back(num);}
        sort(A.begin(),A.end());
        sort(B.begin(),B.end());
        set_difference(A.begin(), A.end(), B.begin(), B.end(), back_inserter(C));
        if(C.empty())cout<<"NULL";
        else copy(C.begin(), C.end(), ostream_iterator<int>(cout, " "));
        cout.put('\n');
    }
}