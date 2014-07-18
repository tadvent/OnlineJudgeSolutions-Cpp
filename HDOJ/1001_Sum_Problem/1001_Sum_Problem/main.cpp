/*
#include<iostream>
#include<vector>
#include<map>
using namespace std;

map<int, int> idxs;
vector< map<int, int>::iterator > cases;

int main(){
    //freopen("i.txt", "r", stdin);
    //freopen("o.txt", "w", stdout);
    int n, sum = 0, i = 0;
    while(cin>>n)
        cases.push_back(idxs.insert(make_pair(n, 0)).first);
    map<int, int>::iterator itr = idxs.begin();
    while(itr != idxs.end()){
        while(i < itr->first)
            sum += ++i;
        itr->second = sum;
        ++itr;
    }
    for(vector< map<int, int>::iterator >::iterator case_itr = cases.begin();
        case_itr != cases.end(); ++case_itr){
            cout << (*case_itr)->second << "\n\n";
    }
}
*/

#include<cstdio>
int main(){
    unsigned n;
    while(scanf("%u", &n) != EOF){
        printf("%u\n\n", (1+n)*n/2);
    }
}
