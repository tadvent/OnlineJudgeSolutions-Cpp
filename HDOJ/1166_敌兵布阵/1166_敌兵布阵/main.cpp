// 学会使用树状数组
// 对一个数组进行：求前 n 项和、调整第 n 项的值，复杂度都是 O(logN)
// 代价是取得第 n 项的值时复杂度也是 O(logN)

#include<cstdio>
#include<cstring>
#include<vector>
using namespace std;

class TreeSum{
    vector<int> vec;
    int lowbit(int n)const{
        return n & (n ^ (n-1));
    }
public:
    TreeSum(){}
    TreeSum(int N):vec(N+1){}
    void reset(int N){
        vec.assign(N+1, 0);
    }
    void add(int pos, int num){
        while(pos < (int)vec.size()){
            vec[pos] += num;
            pos += lowbit(pos);
        }
    }
    int sum(int n)const{
        int rst = 0;
        while(n>0){
            rst += vec[n];
            n -= lowbit(n);
        }
        return rst;
    }
    int sum(int from, int to)const{ // sum [from, to]
        return sum(to) - sum(from-1);
    }
};

int main(){
#ifndef ONLINE_JUDGE
    freopen("i.txt", "r", stdin);
    freopen("o.txt", "w", stdout);
#endif
    int T;
    TreeSum ts;

    scanf("%d", &T);
    for(int iTest = 1; iTest <= T; ++iTest){
        printf("Case %d:\n", iTest);

        int m, n;
        scanf("%d", &n);
        ts.reset(n);
        for(int i=1; i<=n; ++i){
            scanf("%d", &m);
            ts.add(i, m);
        }

        for(;;){
            char op[8];
            scanf("%s", op);
            if(strcmp(op, "End") == 0)break;
            scanf("%d%d", &m, &n);
            if(strcmp(op, "Add") == 0){
                ts.add(m, n);
            } else if(strcmp(op, "Sub") == 0){
                ts.add(m, -n);
            } else if(strcmp(op, "Query") == 0){
                printf("%d\n", ts.sum(m, n));
            }
        }
    }
}
