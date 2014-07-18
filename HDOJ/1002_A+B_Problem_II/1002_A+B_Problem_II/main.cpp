#include<cstdio>
#include<iostream>
#include<vector>
#include<string>
#include<functional>
#include<algorithm>
using namespace std;

class maxnum{
    vector<char> digits;
public:
    istream& input(istream& is){
        string chardigits;
        chardigits.reserve(digits.size());
        is >> chardigits;
        if(is){
            digits.clear();
            transform(chardigits.rbegin(), chardigits.rend(), back_inserter(digits),
                bind2nd(minus<char>(), '0'));
        }
        return is;
    }
    ostream& output(ostream &os) const {
        transform(digits.rbegin(), digits.rend(), ostreambuf_iterator<char>(os),
            bind2nd(plus<char>(), '0'));
        return os;
    }
    maxnum& operator+=(const maxnum& r){
        digits.reserve(max(digits.size(), r.digits.size()) + 1);
        vector<char>::iterator it(digits.begin());
        vector<char>::const_iterator itr(r.digits.begin());
        char carry = 0;
        for(;it != digits.end() && itr != r.digits.end(); ++it, ++itr){
            *it += *itr + carry;
            if(*it > 9){
                carry = 1;
                *it -= 10;
            } else {
                carry = 0;
            }
        }
        if(it != digits.end()){
            if(carry > 0){
                while(++(*it) > 9){
                    *it++ = 0;
                    if(it == digits.end()){
                        digits.push_back(1);
                        return *this;
                    }
                }
            }
        } else if(itr != r.digits.end()){
            if(carry > 0){
                for(;;){
                    digits.push_back((*itr++) + 1);
                    if(digits.back() > 9)digits.back() = 0;
                    else break;
                    if(itr == r.digits.end()){
                        digits.push_back(1);
                        return *this;
                    }
                }
            }
            copy(itr, r.digits.end(), back_inserter(digits));
        } else {
            if(carry > 0)digits.push_back(1);
        }
        return *this;
    }
};

inline istream& operator>>(istream& is, maxnum& m){
    return m.input(is);
}
inline ostream& operator<<(ostream& os, const maxnum& m){
    return m.output(os);
}

int main(){
    freopen("i.txt", "r", stdin);
    freopen("o.txt", "w", stdout);
    int n;
    maxnum l, r;

    cin >> n;
    for(int i = 1; i <= n; ++i){
        if(i > 1)cout << '\n';
        cin >> l >> r;
        cout << "Case " << i << ":\n" << l << " + " << r;
        l += r;
        cout << " = " << l << '\n';
    }
}
