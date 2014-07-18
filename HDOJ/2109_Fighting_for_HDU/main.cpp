/*
 * File:   main.cpp
 * Author: tadvent
 *
 * Created on June 13, 2011, 1:22 PM
 */

#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <algorithm>

using namespace std;

int n, a[105], b[105], sc1, sc2;

bool input() {
    if (!(cin >> n) || n <= 0)return false;
    for (int i = 0; i < n; ++i) cin >> a[i];
    for (int i = 0; i < n; ++i) cin >> b[i];
    sc1 = 0;
    sc2 = 0;
    return true;
}

void calc(){
    sort(a, a+n);
    sort(b, b+n);
    int ret = 0;
    for(int i=0; i<n; ++i){
	if(a[i] > b[i]) sc1 += 2;
	else if(a[i] == b[i]) ++sc1, ++sc2;
	else sc2 += 2;
    }
}

/*
 *
 */
int main(int argc, char** argv) {
#ifndef ONLINE_JUDGE
    freopen("i.txt", "r", stdin);
    freopen("o.txt", "w", stdout);
#endif
    while(input()){
	calc();
	cout << sc1 << " vs " << sc2 << '\n';
    }

    return 0;
}
