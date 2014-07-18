/* 
 * File:   main.cpp
 * Author: tadvent
 *
 * Created on May 31, 2012, 1:29 AM
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

    int n;
    scanf("%d", &n);
    while(n--){
        int h, m;
        scanf("%d:%d", &h, &m);
        if(m != 0){
            printf("0\n");
            continue;
        }
        h += 12;
        if(h > 24) h -= 24;
        printf("%d\n", h);
    }
    return 0;
}

