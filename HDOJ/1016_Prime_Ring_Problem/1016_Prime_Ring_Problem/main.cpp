#include<iostream>
#include<iterator>
#include<algorithm>
#include<cmath>
using namespace std;

int isPrime[51] = {0};
void calprime(){
    for(int i = 2; i <= 50; ++i){
        bool prime = true;
        int root = int(sqrt(double(i)) + 1e-8);
        for(int j = 2; j <= root; ++j){
            if(isPrime[j] && i%j == 0)prime = false;
        }
        if(prime)isPrime[i] = 1;
    }
}

int nums[21] = {1}, N;
void dfs(int idx = 1){
    if(idx == N){
        if(isPrime[nums[0] + nums[N-1]]){
            copy(nums, nums + N - 1, ostream_iterator<int>(cout, " "));
            cout << nums[N-1] << '\n';
        }
        return;
    }
    for(int i = 2; i <= N; ++i){
        bool dup = false;
        for(int j = 0; j < idx; ++j)if(nums[j] == i){
            dup = true; break;
        }
        if(dup)continue;
        if(isPrime[nums[idx - 1] + i]){
            nums[idx] = i;
            dfs(idx + 1);
        }
    }
}

int main(){
    calprime();
    int idx = 0;
    while(cin>>N && N){
        cout << "Case " << ++idx << ":\n";
        dfs();
        cout << '\n';
    }
}
