/*
 * File:   main.cpp
 * Author: tadvent
 *
 * Created on April 25, 2012, 2:23 PM
 */

#include <cstdlib>
#include <cstring>
#include <cstdio>

using namespace std;

int n, sum;
int prices2idx[1005];
int prices[2005];

void input(){
    scanf("%d", &sum);
    scanf("%d", &n);
    bool replace = false;
    for(int i=1; i<=n; ++i){
        scanf("%d", &prices[i]);
        if(prices2idx[prices[i]] == 0){
            prices2idx[prices[i]] = i;
        } else if(prices[i] * 2 == sum) {
            if(!replace){
                replace = true;
                prices2idx[prices[i]] = i;
            }
        }
    }
}

void output(){
    for(int i=1; i<=n; ++i){
        int j = ((sum - prices[i] > 0)? prices2idx[sum - prices[i]]: 0);
        if(j > 0 && i != j){
            printf(" %d %d\n", i, j);
            break;
        }
    }
}

void init(){
    n = sum = 0;
    memset(prices2idx, 0, sizeof(prices2idx));
    memset(prices, 0, sizeof(prices));
}

/*
 *
 */
int main(int argc, char** argv) {
    freopen("A-large-practice.in", "r", stdin);
    freopen("o.txt", "w", stdout);

    int c = 0;
    scanf("%d", &c);
    for(int i=1; i<=c; ++i){
        init();
        input();
        printf("Case #%d:", i);
        output();
    }

    return 0;
}

