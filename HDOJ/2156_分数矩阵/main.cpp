/*
 * File:   main.cpp
 * Author: tadvent
 *
 * Created on March 12, 2012, 1:19 AM
 */

#include <cstdlib>
#include <cstdio>

using namespace std;

double ans[50001] = {0.0, 1.0};

void calc(){
    double line = 1.0;
    for(int i=2; i<=50000; ++i){
        line += (double)2/i;
        ans[i] = ans[i-1] + line;
    }
}

/*
 *
 */
int main(int argc, char** argv) {
    freopen("i.txt", "r", stdin);
    freopen("o.txt", "w", stdout);
    calc();
    int n;
    while(scanf("%d", &n) != EOF && n != 0){
        printf("%.2f\n", ans[n]);
    }

    return 0;
}

