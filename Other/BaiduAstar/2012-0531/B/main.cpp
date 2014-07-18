/* 
 * File:   main.cpp
 * Author: tadvent
 *
 * Created on May 31, 2012, 1:10 AM
 */

#include <cstdlib>
#include <cstdio>

using namespace std;

int k, sum;

void input()
{
    scanf("%d", &k);
    sum = 0;
    for(int i=0; i<k; ++i)
    {
        int m;
        scanf("%d", &m);
        sum += m;
    }
}

int calc()
{
    return sum - k + 1;
}

/*
 * 
 */
int main(int argc, char** argv) {
    freopen("i.txt", "r", stdin);
    freopen("o.txt", "w", stdout);

    int n;
    scanf("%d", &n);
    while(n--){
        input();
        printf("%d\n", calc());
    }

    return 0;
}

