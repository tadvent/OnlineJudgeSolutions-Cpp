#include<iostream>
#include<vector>
#include<cmath>
#include<algorithm>
using namespace std;
vector<int> prime;

void init(){
    prime.push_back(2);
    prime.push_back(3);
    for(int num=5; num <10000; num+=2){
        int root = int(sqrt(double(num))+0.1);
        int *it;
        for(it=&prime[1]; *it<=root; ++it){
            if(num % *it == 0)break;
        }
        if(*it > root)prime.push_back(num);
    }
}

int sepcnt(int num){
    int half = num/2, cnt = 0;
    for(int *it=&prime.back(); it>=&prime[0] && *it>half; --it)
        if(binary_search(&prime[0], it, num-(*it)))
            ++cnt;
    return cnt;
}

int main(){
    int num;
    init();
    while(cin>>num && num)
        cout<<sepcnt(num)<<'\n';
}
