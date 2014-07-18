//#include<cstdio>
//#include<cmath>
//
//double p(int m, int n){
//    int tmp = n;
//    double rst = 0.0, a = 1.0;
//    for(int i=0; i<m; ++i){
//        if(tmp){
//            rst *= 0.5;
//            a *= 0.5;
//            --tmp;
//        }
//        rst += a;
//        a *= 0.5 * double(i+n)/(i+1);
//    }
//    return rst * pow(0.5, tmp);
//}
//
//int main(){
//#ifndef ONLINE_JUDGE
//    freopen("i.txt", "r", stdin);
//    freopen("o.txt", "w", stdout);
//#endif
//    int hp1, hp2, ap1, ap2;
//    while(scanf("%d%d%d%d", &hp1, &hp2, &ap1, &ap2) != EOF){
//        hp1 = (hp1+ap2-1)/ap2;
//        hp2 = (hp2+ap1-1)/ap1;
//        printf("%.4f\n", p(hp1, hp2)*100.0);
//    }
//}

// 公式也推导出来了，精度也照顾到了，所有能想到的测试数据都试过了
// 仍然 WA... 无语

/*
设两人分别可经受的次数为 m, n，则
p(m,n) = a[m]*p(m,0) + a[m-1]*p(m-1,0) + ... + a[1]p(1,0)
       = a[m] + a[m-1] + a[m-2] + ... + a[1]        ( p(k,0) == 1.0 )
    其中 a[k] = C[(m-k)+(n-1), (n-1)] * 0.5^(m-k+n)
相邻项之间有递推关系，因此可由 O(m) 时间求得 p(m,n)
尤其注意 double 的精度问题。
*/

// G++ 提交 AC
// C++ WA，看来 double 精度不够，而 C++ 对 long double 支持不足
#include<cstdio>
#include<cmath>

double p(int m, int n){
    int tmp = n;
    long double rst = 0.0, a = 1.0;
    for(int i=0; i<m; ++i){
        if(tmp){
            rst *= 0.5;
            a *= 0.5;
            --tmp;
        }
        rst += a; // double 的 rst 有可能超范围
        a *= 0.5 * (long double)(i+n)/(i+1);
    }
    return rst * pow(0.5l, (long double)tmp);
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("i.txt", "r", stdin);
    freopen("o.txt", "w", stdout);
#endif
    int hp1, hp2, ap1, ap2;
    while(scanf("%d%d%d%d", &hp1, &hp2, &ap1, &ap2) != EOF){
        hp1 = (hp1+ap2-1)/ap2;
        hp2 = (hp2+ap1-1)/ap1;
        printf("%.4f\n", p(hp1, hp2)*100.0);
    }
}

// 改进余地：计算当中随时注意结果的范围不要超界
