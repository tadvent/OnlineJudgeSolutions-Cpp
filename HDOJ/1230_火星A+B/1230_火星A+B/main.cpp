#include<iostream>
#include<vector>
#include<cmath>
#include<functional>
#include<algorithm>
using namespace std;
class marsnum{
    vector<int> digits;
    static int carry[];
    void norm(){
        int c = 0;
        for(int i=0; i<(int)digits.size(); ++i){
            digits[i] += c; c = 0;
            while(digits[i] >= carry[i]){
                digits[i] -= carry[i];
                ++c;
            }
        }
        while(c > 0){
            digits.push_back(c); c = 0;
            while(digits.back() >= carry[digits.size() - 1]){
                digits.back() -= carry[digits.size() - 1];
                ++c;
            }
        }
    }
public:
    marsnum(){}
    marsnum(int D){
        digits.push_back(D);
        norm();
    }
    static void init(){
        int idx = 1, num = 3;
        while(idx < 26){
            int root = int(sqrt((double)num) + 1e-8);
            bool prime = true;
            for(int i=2; i<= root; ++i)if(num%i == 0)prime = false;
            if(prime)carry[idx++] = num;
            num += 2;
        }
    }
    istream& input(istream& is){
        vector<int> ds; ds.reserve(25);
        int d;
        is >> d;
        ds.push_back(d);
        while(is.get() == ','){
            is >> d;
            ds.push_back(d);
        }
        digits.clear();
        reverse_copy(ds.begin(), ds.end(), back_inserter(digits));
        //norm();
        return is;
    }
    ostream& output(ostream &os)const{
        copy(digits.rbegin(), digits.rend() - 1, ostream_iterator<int>(os, ","));
        return (os << digits.front());
    }
    marsnum& operator+=(const marsnum& r){
        if(digits.size() < r.digits.size())
            digits.resize(r.digits.size(), 0);
        transform(r.digits.begin(), r.digits.end(), digits.begin(), digits.begin(), plus<int>());
        norm();
        return *this;
    }
    bool operator!=(const marsnum& r)const{
        return digits != r.digits;
    }
};
int marsnum::carry[26] = {2};

inline istream& operator>>(istream &is, marsnum &n){
    return n.input(is);
}
inline ostream& operator<<(ostream &os, const marsnum &n){
    return n.output(os);
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("i.txt", "r", stdin);
    freopen("o.txt", "w", stdout);
#endif
    marsnum::init();
    marsnum zero(0), left, right;
    while(cin>>left>>right && left != zero && right != zero){
        left += right;
        cout << left << '\n';
    }
}
