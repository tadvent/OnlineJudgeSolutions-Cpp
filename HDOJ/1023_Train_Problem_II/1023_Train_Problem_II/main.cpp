#include<iostream>
#include<vector>
using namespace std;

class bignum{
    vector<char> digits;
public:
    bignum(){}
    bignum(int num){
        div_t d;
        d.quot = num;
        while(d.quot){
            d = div(d.quot, 10);
            digits.push_back(d.rem);
        }
    }
    bignum(const bignum& r):digits(r.digits){}
    void addition(const bignum &l, const bignum &r){
        int i = 0;
        char carry = 0;
        if(l.digits.size() > r.digits.size()){
            digits = l.digits;
            digits.push_back(0);
            for(; i<(int)r.digits.size(); ++i){
                digits[i] += carry + r.digits[i];
                if(digits[i] > 9){
                    carry = 1;
                    digits[i] %= 10;
                } else carry = 0;
            }
        }
        else {
            digits = r.digits;
            digits.push_back(0);
            for(; i<(int)l.digits.size(); ++i){
                digits[i] += carry + l.digits[i];
                if(digits[i] > 9){
                    carry = 1;
                    digits[i] %= 10;
                } else carry = 0;
            }
        }
        if(carry == 1){
            for(;; ++i){
                ++digits[i];
                if(digits[i] == 10){
                    digits[i] = 0;
                } else break;
            }
        }
        if(digits.back() == 0)digits.pop_back();
    }
    ostream& output(ostream &o)const{
        if(digits.empty())o.put('0');
        else {
            for(int i=digits.size()-1; i>=0; --i)
                o.put(digits[i] + '0');
        }
        return o;
    }
};
inline ostream& operator<<(ostream &o, const bignum &b){
    return b.output(o);
}

bignum block[101][101];
void init(){
    block[0][0] = 0;
    for(int i=0; i<101; ++i)block[i][0] = 1;
    for(int line = 1; line < 101; ++line)
        for(int row = 1; row <= line; ++row)
            block[line][row].addition(block[line-1][row], block[line][row-1]);
}

int main(){
    int n;
    init();
    while(cin>>n && n>0)
        cout<<block[n][n]<<'\n';
}
