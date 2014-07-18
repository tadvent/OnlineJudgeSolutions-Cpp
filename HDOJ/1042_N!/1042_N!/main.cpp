#include<iostream>
#include<cstdlib>
#include<vector>
#include<map>
using namespace std;

class bignum{
    vector<unsigned long long> digits;
public:
    void reset(){
        digits.assign(1, 1);
    }
    bignum& operator*=(int num){
        unsigned long long carry = 0;
        int idx;
        for(idx = 0; idx < (int)digits.size(); ++idx){
            carry += digits[idx]*num;
            digits[idx] = carry%1000000000;
            carry /= 1000000000;
        }
        while(carry > 0){
            digits.push_back(carry%1000000000);
            carry /= 1000000000;
        }
        return *this;
    }
    ostream& output(ostream& os)const{
        os << digits.back();
        char oldfill = os.fill('0');
        for(vector<unsigned long long>::const_reverse_iterator rit=digits.rbegin()+1;
            rit != digits.rend(); ++rit){
                os.width(9);
                os << *rit;
        }
        os.fill(oldfill);
        return os;
    }
};

int main(){
    int n, lastmax;
    bignum bn;
    map<int, bignum> mb;
    while(cin>>n){
        int m = n;
        if(mb.empty()){
            bn.reset();
            lastmax = 1;
        } else {
            map<int, bignum>::iterator it=mb.upper_bound(n);
            if(it == mb.begin()){
                bn.reset();
                lastmax = 1;
            } else {
                --it;
                bn = it->second;
                lastmax = it->first;
            }
        }
        while(n>lastmax)bn*=n--;
        if(mb.find(m)==mb.end())mb.insert(make_pair(m, bn));
        bn.output(cout);
        cout.put('\n');
    }
}
