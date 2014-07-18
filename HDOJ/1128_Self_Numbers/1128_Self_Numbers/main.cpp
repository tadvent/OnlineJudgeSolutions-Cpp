#include<cstdio>
#include<cstdlib>

int notself[100] = {0};

int d(int n){
    div_t t;
    t.quot = n;
    while(t.quot){
        t = div(t.quot, 10);
        n += t.rem;
    }
    return n;
}

void calcself(int max){
    for(int num = 1; num <= max; ++num){
        int idx = num%100;
        if(!notself[idx]){
            fprintf(stdout, "%d\n", num);
        } else {
            notself[idx] = 0;
        }
        notself[d(num)%100] = 1;
    }
}

int main(){
    calcself(1000000);
}
