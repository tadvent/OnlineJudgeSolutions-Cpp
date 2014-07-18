#include<cstdio>
#include<cstdlib>

int dsum(int num, int base){
    int s = 0;
    div_t d;
    d.quot = num;
    while(d.quot){
        d = div(d.quot, base);
        s += d.rem;
    }
    return s;
}

bool isValid(int num){
    int s = dsum(num, 10);
    if(s != dsum(num, 12) || s != dsum(num, 16))return false;
    return true;
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("o.txt", "w", stdout);
#endif
    for(int n=1000; n<10000; ++n)
        if(isValid(n))printf("%d\n", n);
}
