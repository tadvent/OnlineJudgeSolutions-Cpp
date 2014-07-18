/*
 * File:   main.cpp
 * Author: tadvent
 *
 * Created on June 13, 2011, 1:39 PM
 */

#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <functional>
#include <utility>
#include <cstdio>

using namespace std;

int v, n;
pair<int, int> treasure[105];

bool input() {
    if (!(cin >> v >> n) || v <= 0)return false;
    for (int i = 0; i < n; ++i)
        cin >> treasure[i].first >> treasure[i].second;
    return true;
}

int calc() {
    if (v <= 0) return 0;
    sort(treasure, treasure + n, greater<pair<int, int> >());
    int ret = 0;
    for (int i = 0; i < n; ++i) {
        if (treasure[i].second >= v) {
            ret += v * treasure[i].first;
            break;
        } else {
            ret += treasure[i].first * treasure[i].second;
            v -= treasure[i].second;
        }
    }
    return ret;
}

/*
 *
 */
int main(int argc, char** argv) {
#ifndef ONLINE_JUDGE
    freopen("i.txt", "r", stdin);
    freopen("o.txt", "w", stdout);
#endif
    while (input()) {
        cout << calc() << '\n';
    }

    return 0;
}

