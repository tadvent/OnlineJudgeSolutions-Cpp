#include<cstdio>
#include<cmath>

double calc(int n1, int n2, double p1, double p2){
    double pw, pl, x; // pwin, plose
    if(n1 == 0)return 0.0;
    if(n2 == 0)return 1.0;
    pw = p1*(1.0-p2);
    pl = (1.0-p1)*p2;
    if(pw == 0.0)return 0.0;
    if(pl == 0.0)return 1.0;
    x = pl / pw;

    if(fabs(1-x) < 1e-8){ // pw == pl != 0.0
        return double(n1) / (n1+n2);
    } else {
        return (1.0 - pow(x, n1)) / (1.0 - pow(x, n1+n2));
    }
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("i.txt", "r", stdin);
    freopen("o.txt", "w", stdout);
#endif
    int N, M;
    double p, q;
    while(scanf("%d%d%lf%lf", &N, &M, &p, &q) != EOF)
        printf("%.2f\n", calc(N, M, p, q));
}

/*
分析起来还是比较复杂的
设 p(k) 表示 speakless 手中有 k 个糖时获胜的概率，则显然
p(n) = 1.0 // 设总共有 n 个糖
p(0) = 0.0
且有递推公式：
p(m) = pw*(m+1) + pd*p(m) + pl*p(m-1) ..................(i)
其中 pw (pwin) 表示每个问题 speakless 获胜的概率
       pd (pdraw) 表示每个问题 speakless 平局的概率
       pl (plose) 表示每个问题 speakless 失败的概率
       显然有 pw + pd + pl = 1.0

为了由递推公式(i)求解 p(k)，设递推公式可写为
p(m+1) - p(m) == x*[p(m) - p(m-1)]
的形式
对照 (i) 可解得 x = pl / pw

于是：
p(1) - p(0) = 1   * [p(1) - p(0)]
p(2) - p(1) = x   * [p(1) - p(0)]
p(3) - p(2) = x^2 * [p(1) - p(0)]
...
p(n) - p(n-1) = x^(n-1) * [p(1) - p(0)]
又由 p(n) = 1.0, p(0) = 0.0 代入，可解得
p(k) = (1.0 - x^k) / (1.0 - x^n)

最后再考虑 p1, p2 为零，或 pw == pl 的特殊情况即可。
/*
