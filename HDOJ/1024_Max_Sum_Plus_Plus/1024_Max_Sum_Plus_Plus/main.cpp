#include<cstdio>
#include<algorithm>
using namespace std;
const int maxn = 1000000;

int m, n;
int v[maxn];

int buf1[maxn+1], buf2[maxn+1], *last_a, *a;
int last_b, b;

bool input(){
    if(scanf("%d %d", &m, &n) == EOF)return false;
    for(int i=0; i<n; ++i)
        scanf("%d", &v[i]);
    return true;
}

int calc(){
    memset(buf1, 0, sizeof(buf1));
    last_a = buf1; a = buf2;
    while(m--){
        a[0] = 0;
        last_b = 0;
        for(int i=1; i<=n; ++i){
            b = max(last_b, last_a[i-1]) + v[i-1];
            a[i] = max(a[i-1], b);
            last_b = b;
        }
        swap(a, last_a);
    }
    return last_a[n];
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("i.txt", "r", stdin);
    freopen("o.txt", "w", stdout);
#endif
    while(input())
        printf("%d\n", calc());
}


////////////////////////////////////////////////
//#include<stdio.h>
//#include<stdlib.h>
//#define MIN_SUM 0x80000000
//
//int max_sum(int e[], int n, int m)
//{
//       int *curr_best;
//       int *prev_best;
//       int max_sum, i, j;
//
//       curr_best = (int*)malloc(sizeof(int) * (n + 1));
//       prev_best = (int*)calloc(n + 1, sizeof(int));
//
//       *curr_best = 0;
//       e--;
//
//       for(i = 1; i <= m; ++i)
//       {
//              max_sum = MIN_SUM;
//              for(j = i; j <= n; ++j)
//              {
//                     if(curr_best[j - 1] < prev_best[j - 1])
//                            curr_best[j] = prev_best[j - 1] + e[j];
//                     else
//                            curr_best[j] = curr_best[j - 1] + e[j];
//                     prev_best[j - 1] = max_sum;
//                     if(max_sum < curr_best[j])
//                            max_sum = curr_best[j];
//              }
//              prev_best[j - 1] = max_sum;
//       }
//
//       free(prev_best);
//       free(curr_best);
//
//       return max_sum;
//}
//
//int main()
//{
//#ifndef ONLINE_JUDGE
//    freopen("i.txt", "r", stdin);
//    freopen("o.txt", "w", stdout);
//#endif
//       int n, m, i, *data;
//       while(scanf("%d%d", &m, &n) == 2 && n > 0 && m > 0)
//       {
//              data = (int*)malloc(sizeof(int) * n);
//              for(i = 0; i < n; ++i)
//                     scanf("%d", &data[i]);
//              printf("%d\n", max_sum(data, n, m));
//              free(data);
//       }
//       return 0;
//}
