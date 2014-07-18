#define MY

#ifdef MY


#include<cstdio>
#include<algorithm>

int N, L;
int l[600];
int ans[600], ans_size, ans_sum;

int* sortPt[600];

bool input(){
    if(scanf("%d%d", &N, &L) != 2)return false;
    for(int i=0; i<N; ++i)scanf("%d", l+i);
    ans_size = 0;
    ans_sum = 0;
    return true;
}

void output(){
    printf("%d %d\n", ans_size, ans_sum);
    if(ans_size > 0)printf("%d", ans[0]);
    for(int i=1; i<ans_size; ++i)
        printf(" %d", ans[i]);
    putchar('\n');
}

template<class T>
class ptLess{
public:
    bool operator()(const T *const p1, const T *const p2) const {
        return *p1 < *p2;
    }
};

int ptIdx[600];
int **tmpAs, **tmpAs2, *buf1[600], *buf2[600];

// 排 ptIdx 的第 k 个位置，算上这个还要排 kl 个位置
// 之前的值和为 sum
// 从 sortPt[] 的第 m 个指针开始到第 n 个指针所指元素中组合选数
// 能生成有效排列返回 true 否则返回 false
bool dfs(const int k, const int kl, const int sum, const int m, const int n){
    if(kl == 0){
        if(sum > ans_sum){
            ans_sum = sum;
            for(int i=0; i<k; ++i)
                tmpAs[i] = sortPt[ptIdx[i]];
        } else if(sum == ans_sum){
            for(int i=0; i<k; ++i)
                tmpAs2[i] = sortPt[ptIdx[i]];
            std::sort(tmpAs2, tmpAs2+ans_size);
            std::sort(tmpAs, tmpAs+ans_size);
            if(std::lexicographical_compare(tmpAs2, tmpAs2+ans_size, tmpAs, tmpAs+ans_size))
                std::swap(tmpAs, tmpAs2);
        }
        return true;
    }
    bool ret = false;
    for(int i=m; i<=n-kl; ++i){
        if(sum + *sortPt[i] > L)break;
        ptIdx[k] = i;
        if(!dfs(k+1, kl-1, sum+*sortPt[i], i+1, n))break;
        ret = true;
    }
    return ret;
}

void calc(){
    // init
    for(int i=0; i<N; ++i)
        sortPt[i] = l+i;
    std::sort(sortPt, sortPt+N, ptLess<int>());

    int empty = L;
    for(ans_size=0; ans_size<N; ++ans_size){
        if(*sortPt[ans_size] <= empty){
            empty -= *sortPt[ans_size];
        } else break;
    }

    // dfs
    tmpAs = buf1;
    tmpAs2 = buf2;
    if(!dfs(0, ans_size, 0, 0, N)) return;
    std::sort(tmpAs, tmpAs+ans_size);
    for(int i=0; i<ans_size; ++i)
        ans[i] = *tmpAs[i];
}

int main(){
    freopen("i.txt", "r", stdin);
    freopen("o.txt", "w", stdout);
    while(input()){
        calc();
        output();
    }
}


#else
///////////////////////////////////////////////////////////////////////
// this program is wrong ... although it gets a PE

#include <stdio.h> 
#include <algorithm> 
using namespace std; 
int dp[601][6001]; 
struct node{ 
    int w,num; 
}; 
int cmp(const void *a,const void *b){ 
    node *c=(node*)a; 
    node *d=(node*)b; 
    return c->w-d->w; 
} 
int main() 
{ 
    freopen("i.txt", "r", stdin);
    freopen("o.txt", "w", stdout);
    int n,l,i,j,v[601],th[600],t; 
    node v0[601]; 
    for(;;){
        if(scanf("%d%d",&n,&l) == EOF)break;
        for(i=1;i<=n;i++){ 
            scanf("%d",&v[i]); 
            v0[i].num=i; 
            v0[i].w=v[i]; 
        } 
        qsort(v0+1,n,sizeof(node),cmp); 
        for(i=0;i<=l;i++) dp[0][i]=0; 
        for(i=1;i<=n;i++){ 
            for(j=l;j>=v0[i].w;j--){ 
                if(dp[i-1][j]<(dp[i-1][j-v0[i].w]+1)) dp[i][j]=dp[i-1][j-v0[i].w]+1; 
                else dp[i][j]=dp[i-1][j]; 
            } 
            for(j=v0[i].w-1;j>=0;j--) dp[i][j]=dp[i-1][j]; 
        } 
        for(i=n,j=l,t=0;i&&j;i--){ 
            if(j>=v0[i].w&&dp[i][j]==(dp[i-1][j-v0[i].w]+1)){ 
                j-=v0[i].w; 
                th[t++]=v0[i].num; 
            } 
        } 
        sort(th,th+t); 
        for(j=0,i=0;i<t;i++) j+=v[th[i]]; 
        printf("%d %d \n",dp[n][l],j); 
        printf("%d",v[th[0]]); 
        for(i=1;i<t;i++) printf(" %d",v[th[i]]); 
        printf(" \n"); 
    }
    return 0; 
}


#endif
