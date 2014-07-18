#include <cstdio>
#include <cmath>

using namespace std;

class solver{
    public:
    void init();
    bool input();
    int calc() const;

    private:
    bool isPrime(const int) const;
    int primes[50000];
    int count;
};

void solver::init()
{
    primes[0] = 2;
    primes[1] = 3;
    int end = int(sqrt(double((1 << 31) -1)) + 0.5) + 100;
    int n, sq, idx = 2;
    for(n=5; n<=end; n+=2)
    {
        int i;
        sq = int(sqrt(double(n)) + 0.1);
        for(i = 1; primes[i] <= sq; ++i)
        {
            if(n % primes[i] == 0) break;
        }
        if(primes[i] > sq)
            primes[idx++] = n;
    }
}

bool solver::input()
{
    int n, m;
    if(scanf("%d", &n) == EOF)
        return false;
    count = 0;
    while(n--)
    {
        scanf("%d", &m);
        if(isPrime(m))
            ++count;
    }
    return true;
}

int solver::calc() const
{
    return count;
}

bool solver::isPrime(int n) const
{
    int sq = int(sqrt(double(n)) + 0.1), i;
    for(i = 0; primes[i] <= sq; ++i)
    {
        if(n % primes[i] == 0) break;
    }
    if(primes[i] > sq)
        return true;
    else
        return false;
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("i.txt", "r", stdin);
    freopen("o.txt", "w", stdout);
#endif
    solver so;
    so.init();
    while(so.input()){
        printf("%d\n", so.calc());
    }
    return 0;
}

