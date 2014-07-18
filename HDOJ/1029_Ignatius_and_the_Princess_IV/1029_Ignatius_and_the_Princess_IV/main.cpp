// 垃圾题，测试数据真要和叙述中一样强，有大数据，还有 2M 内存限制就非常难写了。

#include<cstdio>
#include<vector>
#include<algorithm>
#include<utility>
using namespace std;

class hashmap{
    const int sz;
    vector<pair<int,int> > hashtable;
public:
    hashmap():sz(99997){
        hashtable.resize(sz);
    }
    int add(int key){
        vector<pair<int,int> >::iterator it = hashtable.begin() + key%sz;
        while(it != hashtable.end() && it->first != 0 && it->first != key)++it;
        if(it == hashtable.end()){
            it = hashtable.begin();
            while(it->first != 0 && it->first != key)++it;
        }
        if(it->first == 0){
            it->first = key;
            return it->second = 1;
        } else return ++(it->second);
    }
};

int special(int n){
    hashmap hmp;
    int tar = (n+1)/2;
    pair<int,int> first(0,0), second(0,0);
    while(n--){
        int val, num;
        scanf("%d", &val);
        num = hmp.add(val);
        if(num > first.second){
            second = first;
            first = make_pair(val, num);
        } else if(num > second.second){
            second = make_pair(val, num);
        }
        if(second.second + n < tar || first.second >= tar){
            scanf("%*[^\n]%*c");
            return first.first;
        }
    }
    return 0;
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("i.txt", "r", stdin);
    freopen("o.txt", "w", stdout);
#endif
    int n;
    while(scanf("%d", &n) != EOF)
        printf("%d\n", special(n));
}
