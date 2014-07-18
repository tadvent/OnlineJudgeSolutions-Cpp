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

// ��ʽҲ�Ƶ������ˣ�����Ҳ�չ˵��ˣ��������뵽�Ĳ������ݶ��Թ���
// ��Ȼ WA... ����

/*
�����˷ֱ�ɾ��ܵĴ���Ϊ m, n����
p(m,n) = a[m]*p(m,0) + a[m-1]*p(m-1,0) + ... + a[1]p(1,0)
       = a[m] + a[m-1] + a[m-2] + ... + a[1]        ( p(k,0) == 1.0 )
    ���� a[k] = C[(m-k)+(n-1), (n-1)] * 0.5^(m-k+n)
������֮���е��ƹ�ϵ����˿��� O(m) ʱ����� p(m,n)
����ע�� double �ľ������⡣
*/

// G++ �ύ AC
// C++ WA������ double ���Ȳ������� C++ �� long double ֧�ֲ���
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
        rst += a; // double �� rst �п��ܳ���Χ
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

// �Ľ���أ����㵱����ʱע�����ķ�Χ��Ҫ����
