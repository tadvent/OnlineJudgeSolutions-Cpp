#include<iostream>
#include<vector>
#include<cmath>
using namespace std;

const int maxnum = 6000000;
static vector<int> primes;
void init(){
    static int inits[] = {2,3,5,7,11,13,17,19,23,29,31};
    primes.reserve(370);
    primes.assign(inits, inits+sizeof(inits)/sizeof(inits[0]));
    for(int num = primes.back() + 2; num <= (int)ceil(sqrt(double(maxnum))); num += 2){
        int root = int(ceil(sqrt((double)num))), i;
        for(i = 1; primes[i] <= root; ++i)
            if(num % primes[i] == 0)break;
        if(primes[i] > root)primes.push_back(num);
    }
}
void factor(int num, vector<pair<int,int> > &facs){
    int idx = 0;
    facs.clear();
    while(num > 1){
        int root = int(ceil(sqrt((double)num)));
        while(primes[idx] <= root && num%primes[idx]) ++idx;
        if(primes[idx] > root){
            if(!facs.empty() && num == facs.back().first)
                ++facs.back().second;
            else facs.push_back(make_pair(num, 1));
            break;
        } else {
            if(!facs.empty() && primes[idx] == facs.back().first)
                ++facs.back().second;
            else facs.push_back(make_pair(primes[idx], 1));
            num /= primes[idx];
        }
    }
}
int facsum(int num){
    static vector< pair<int, int> > factors;
    factor(num, factors);
    int product = 1, sum, val, times;
    for(vector<pair<int,int> >::iterator it=factors.begin();
        it != factors.end(); ++it){
            sum = 1; val = it->first; times = it->second;
            while(times--){
                sum += val;
                val *= it->first;
            }
            product *= sum;
    }
    return product - num;
}
inline bool isQinhe(int a, int b){
    if(a>b)swap(a,b);
    return (facsum(a) == b && facsum(b) == a);
}

int main(){
    int m, a, b;
    init();
    cin >> m;
    while(m--){
        cin >> a >> b;
        cout << (isQinhe(a, b)? "YES\n" : "NO\n");
    }
}