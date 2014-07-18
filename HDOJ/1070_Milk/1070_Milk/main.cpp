#include<cstdio>
#include<cstdlib>
#include<climits>
#include<cstring>
#include<algorithm>
using namespace std;

struct Milk{
    char brand[102];
    int price, vol;
    double cperday;
    void calc(){
        int day = vol / 200;
        if(day == 0){
            cperday = INT_MAX;
            return;
        } else if(day > 5){
            day = 5;
        }
        cperday = double(price) / day;
    }
    bool operator<(const Milk &r)const{
        return (cperday < r.cperday - 1e-8 ||
            abs(cperday - r.cperday) < 1e-8 && vol > r.vol);
    }
};
Milk milks[102];
int milks_sz;

int main(){
#ifndef ONLINE_JUDGE
    freopen("i.txt", "r", stdin);
    freopen("o.txt", "w", stdout);
#endif
    int nTest;
    scanf("%d", &nTest);
    while(nTest--){
        scanf("%d", &milks_sz);
        for(int i=0; i<milks_sz; ++i){
            scanf("%s %d %d", milks[i].brand, &milks[i].price, &milks[i].vol);
            milks[i].calc();
        }
        printf("%s\n", min_element(milks, milks+milks_sz)->brand);
    }
}
