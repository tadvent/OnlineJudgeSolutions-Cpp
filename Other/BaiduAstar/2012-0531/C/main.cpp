/* 
 * File:   main.cpp
 * Author: tadvent
 *
 * Created on May 31, 2012, 1:21 AM
 */

#include <cstdlib>
#include <cstdio>

using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {
    freopen("i.txt", "r", stdin);
    freopen("o.txt", "w", stdout);

    double sum, pay;
    sum = 0.0;
    for(int i=0; i<12; ++i)
    {
        scanf("%lf", &pay);
        sum += pay;
    }
    printf("$%.2f\n", sum/12);
    return 0;
}

