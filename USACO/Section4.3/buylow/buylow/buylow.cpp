/*
ID: wjl1241
PROG: buylow
LANG: C++
*/

#include<fstream>
#include<list>
#include<vector>
#include<iomanip>
using namespace std;

class bignum{
    vector<int> numseq; // 0~9999 in an integer
    // numseq.begin() ~> numseq.end() base is 10000^0 ~> 10000^n
public:
    bignum():numseq(1,0){}
    bignum(int _Value):numseq(1,_Value){}
    bignum(const bignum &_Value):numseq(_Value.numseq){}
    bignum& operator=(const bignum &_Value){
        numseq = _Value.numseq;
        return *this;
    }
    bignum &operator+=(const bignum &_Right){
        numseq.resize(max(numseq.size(),_Right.numseq.size()) + 1, 0);
        int carry = 0;
        vector<int>::size_type i;
        for(i = 0; i<_Right.numseq.size(); ++i){
            int nsum = numseq[i] + _Right.numseq[i] + carry;
            numseq[i] = nsum % 10000;
            carry = nsum / 10000;
        }
        while(carry){
            int nsum = numseq[i] + carry;
            numseq[i++] = nsum % 10000;
            carry = nsum / 10000;
        }
        if(numseq.back() == 0)numseq.pop_back();
        return *this;
    }
    friend ostream &operator<<(ostream &o, const bignum &bn);
};
ostream &operator<<(ostream &o, const bignum &bn){
    o<<bn.numseq.back();
    vector<int>::const_reverse_iterator itr = bn.numseq.rbegin() + 1;
    while(itr != bn.numseq.rend()){
        o<<setfill('0')<<setw(4)<<(*itr++);
    }
    return o;
}

struct node{
    int price;
    int len;
    bignum cnt;
    node():price(0), len(1), cnt(1){}
    node(int Price):price(Price), len(1), cnt(1){}
};

list<node> stprice;
void addprice(int price){
    node cur(price);
    int lastprice = 0;
    list<node>::iterator itr=stprice.begin();
    for(;itr!=stprice.end() && cur.price < itr->price; ++itr){
        if(itr->len >= cur.len){
            lastprice = itr->price;
            cur.cnt = itr->cnt;
            cur.len = itr->len + 1;
        } else if(itr->len == cur.len - 1 && lastprice != itr->price){
            lastprice = itr->price;
            cur.cnt += itr->cnt;
        }
    }
    if(itr != stprice.end() && itr->price == cur.price)
        *itr = cur;
    else
        stprice.insert(itr, cur);
}

int main(){
    ifstream fi("buylow.in");
    int n, p;
    fi>>n;
    while(n--){
        fi>>p;
        addprice(p);
    }
    addprice(0);
    fi.close();

    ofstream fo("buylow.out");
    fo<<stprice.back().len-1<<' '<<stprice.back().cnt<<endl;
    fo.close();
    return 0;
}