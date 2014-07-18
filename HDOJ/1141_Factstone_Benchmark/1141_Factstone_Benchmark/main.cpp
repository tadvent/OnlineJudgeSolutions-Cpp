#include<cstdio>

class BigFloat{
    double tail;
    int idx;
    void regular(){
        while(tail > 10.0){
            tail /= 10.0;
            ++idx;
        }
    }
public:
    BigFloat(double num):tail(num), idx(0){
        regular();
    }
    BigFloat& operator *= (int n){
        tail *= n;
        regular();
        return *this;
    }
    BigFloat& operator *= (const BigFloat &bf){
        tail *= bf.tail;
        idx += bf.idx;
        regular();
        return *this;
    }
    bool operator<(const BigFloat &bf)const{
        return (idx < bf.idx ||
            idx == bf.idx && tail < bf.tail);
    }
};

int ans[21];
void init(){
    int k = 3;
    BigFloat jiech(6.0), up(16.0);
    for(int i=0; i<21; ++i){
        while(jiech < up){
            jiech *= ++k;
        }
        ans[i] = k-1;
        up *= up;
    }
}

int main(){
    int year;
    init();
    while(scanf("%d", &year) != EOF && year){
        printf("%d\n", ans[(year-1960)/10]);
    }
}
