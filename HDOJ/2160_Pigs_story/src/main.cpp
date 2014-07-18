#include<cstdio>
using namespace std;

long fib[21];

void calc()
{
    fib[0] = 1;
    fib[1] = 1;
    for(int i=2; i<21; ++i)
    {
        fib[i] = fib[i-1] + fib[i-2];
    }
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("i.txt", "r", stdin);
    freopen("o.txt", "w", stdout);
#endif

    calc();
    int n, d;
    scanf("%d", &n);
    while(n--)
    {
        scanf("%d", &d);
        printf("%d\n", fib[d]);
    }

    return 0;
}

