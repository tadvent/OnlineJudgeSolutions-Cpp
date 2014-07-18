/*
ID: wjl1241
LANG: C++
TASK: tour
 */

#define NDEBUG

#include <cstdlib>
#include <cstdio>
#include <cassert>
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

class Solver {
    vector< vector<int> > graph;
    vector<int> dp;
    int nCity_;

    void initGraph() {
        for (int i = 0; i < graph.size(); ++i) {
            sort(graph[i].begin(), graph[i].end());
            graph[i].erase(unique(graph[i].begin(), graph[i].end()), graph[i].end());
        }
    }

    int sub(int x, int y) {
        return x * nCity_ + y;
    }

    void filldp(int x, int y) {
        assert(x < y);
        int maxCity = 0;
        for (vector<int>::const_iterator i = graph[x].begin();
                i != graph[x].end(); ++i) {
            if (maxCity < dp[sub(*i, y)]) maxCity = dp[sub(*i, y)];
        }
        dp[sub(x, y)] = dp[sub(y, x)] = (maxCity > 0 ? maxCity + 1 : 0);
    }
public:

    void reset(int nCity) { // 0: west most;    n-1: east most
        nCity_ = nCity;
        graph.assign(nCity, vector<int>());
    }

    void addArc(int fr, int to) {
        if (fr < to) {
            graph[fr].push_back(to);
        } else {
            graph[to].push_back(fr);
        }
    }

    int calc() {
        initGraph();
        dp.resize(nCity_ * nCity_);
        dp[sub(nCity_ - 1, nCity_ - 1)] = 1;
        for (int i = nCity_ - 2; i >= 0; --i)
            for (int j = i + 1; j < nCity_; ++j) {
                filldp(i, j);
            }

        int maxCity = 0;
        for (int i = 0; i < graph[0].size(); ++i)
            for (int j = i + 1; j < graph[0].size(); ++j) {
                if (maxCity < dp[sub(graph[0][i], graph[0][j])])
                    maxCity = dp[sub(graph[0][i], graph[0][j])];
            }
        return maxCity + 1;
    }
};

/*
 *
 */
int main() {

    int N, M;
    map<string, int> ct2idx;
    Solver slv;

    freopen("tour.in", "r", stdin);
    freopen("tour.out", "w", stdout);

    cin >> N >> M;
    slv.reset(N);
    for (int i = 0; i < N; ++i) {
        string city;
        cin >> city;
        ct2idx.insert(pair<string, int>(city, i));
    }
    for (int i = 0; i < M; ++i) {
        string ct1, ct2;
        cin >> ct1 >> ct2;
        slv.addArc(ct2idx[ct1], ct2idx[ct2]);
    }

    cout << slv.calc() << endl;

    return 0;
}

