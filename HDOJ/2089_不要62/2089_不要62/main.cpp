#include<iostream>
#include<cstring>
#include<vector>
#include<algorithm>
using namespace std;
vector<int> buji;
void init(){
    char buf[10];
    buji.reserve(501000);
    for(int num = 1; num <= 1000000; ++num){
        sprintf(buf, "%d", num);
        if(strstr(buf, "4") != NULL || strstr(buf, "62") != NULL)
            buji.push_back(num);
    }
}
int main(){
    int n, m;
    init();
    while(cin>>n>>m && (n||m)){
        cout<<(m-n+1) - (upper_bound(buji.begin(), buji.end(), m) - lower_bound(buji.begin(), buji.end(), n))<<'\n';
    }
}
