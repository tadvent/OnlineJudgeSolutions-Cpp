#include<cstdio>
#include<cstdlib>
#include<cmath>

inline double total(double n, int &idx){
    double ans = n*(n+1)*((2*n+1)/3+1)/4;
    idx = static_cast<int>(floor(log(ans)/log(10.0) + 1e-8) + 0.5);
    return ans/pow(10.0, double(idx));
}

int main(){
    int n, idx;
    while(scanf("%d", &n) != EOF && n){
        double real = total(n, idx);
        printf("%.2fE%d\n", real, idx);
    }

    system("pause");
}
