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
�����������ǱȽϸ��ӵ�
�� p(k) ��ʾ speakless ������ k ����ʱ��ʤ�ĸ��ʣ�����Ȼ
p(n) = 1.0 // ���ܹ��� n ����
p(0) = 0.0
���е��ƹ�ʽ��
p(m) = pw*(m+1) + pd*p(m) + pl*p(m-1) ..................(i)
���� pw (pwin) ��ʾÿ������ speakless ��ʤ�ĸ���
       pd (pdraw) ��ʾÿ������ speakless ƽ�ֵĸ���
       pl (plose) ��ʾÿ������ speakless ʧ�ܵĸ���
       ��Ȼ�� pw + pd + pl = 1.0

Ϊ���ɵ��ƹ�ʽ(i)��� p(k)������ƹ�ʽ��дΪ
p(m+1) - p(m) == x*[p(m) - p(m-1)]
����ʽ
���� (i) �ɽ�� x = pl / pw

���ǣ�
p(1) - p(0) = 1   * [p(1) - p(0)]
p(2) - p(1) = x   * [p(1) - p(0)]
p(3) - p(2) = x^2 * [p(1) - p(0)]
...
p(n) - p(n-1) = x^(n-1) * [p(1) - p(0)]
���� p(n) = 1.0, p(0) = 0.0 ���룬�ɽ��
p(k) = (1.0 - x^k) / (1.0 - x^n)

����ٿ��� p1, p2 Ϊ�㣬�� pw == pl ������������ɡ�
/*
