#include<cstdio>
#include<algorithm>

int main(){
    int P, m, n, r;
    scanf("%d", &P);
    while(P--){
        scanf("%d%d", &m, &n);
        if(m<n)std::swap(m,n);
        while(n){
            r = m%n;
            m = n;
            n = r;
        }
        if(m == 1)puts("NO");
        else puts("YES");
    }
}
