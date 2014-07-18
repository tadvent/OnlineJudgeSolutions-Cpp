#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>

const int maxn = 105;

//void build_sa(char line[], int len, int sa[]){
//    int i, j, k;
//    int acc[maxn]; // 累加，辅助基数排序
//    int rnk[maxn]; // rank, 范围[0, len-1]
//}

class sub_less{
    char *p;
public:
    sub_less(char *Arr):p(Arr){}
    bool operator()(int i, int j) const {
        return p[i] < p[j];
    }
};

void build_sa(char line[], int n, int sa[]){
    int i, j, k, cl; // cl: cmp len
    int rnk[maxn];

    // init
    for(i=0; i<n; ++i)sa[i] = i;
    std::sort(sa, sa+n, sub_less(line));
    rnk[sa[0]] = 1;
    for(k=1, i=1; i<n; ++i)rnk[i] = (line[sa[i]] == line[sa[i-1]])? k: ++k;

    // sa 为上一趟的排序结果，取值范围是 0 ~ n-1
    // rnk 的取值范围是 1 ~ n
    for(cl=1; rnk[sa[n-1]] < n; cl<<=1){
    }

    // sa 为上一趟的排序结果，取值范围是 0 ~ len-1
    // rank 的取值范围是 1 ~ len
    do{
        int y[maxn]; // 基数排序 按后半段所得结果
        int acc[maxn]; // 累计，辅助按前半段的基数排序

        // 按后半段基数排序，利用上次 sa[] 的结果
        for(j=0, i=n-cl; i<len; ++i)y[j++] = i;
        for(i=0; i<n; ++i)if(sa[i]>=cl)y[j++] = sa[i] - cl;

        // 按前半段基数排序
        memset(acc, 0, sizeof(acc));
        for(i=0; i<n; ++i)++acc[rnk[i]];
        for(i=1; i<n; ++i)acc[i] += acc[i-1];
        for(i=n-1; i>=0; --i)sa[--acc[y[i]]] = i;
    }while(rank[sa[n-1]] < n);
    // 当 rank 最大值达到 len 时，说明所有 rank 值无重复
    // 那么后序更长的比较已无需再进行了。
}

int main(){
    char line[maxn];
    int sfx_array[maxn], n;

    while(*gets(line)){
        n = strlen(line);
        build_sa(line, n, sfx_array);
        for(int i=0; i<n; ++i)
            printf("%d ", sfx_array[i]);
        puts("\n");
    }

    system("pause");
}
