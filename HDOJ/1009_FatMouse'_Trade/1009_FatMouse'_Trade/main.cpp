#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

struct Room{
    unsigned java, food;
    double ratio;
    Room(unsigned JavaBean, unsigned CatFood):
        java(JavaBean), food(CatFood),
        ratio(double(JavaBean)/CatFood){}
};

vector<Room> rooms;
vector<unsigned> idxs;

inline bool lower(unsigned idx1, unsigned idx2){
    return rooms[idx1].ratio < rooms[idx2].ratio;
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("i.txt", "r", stdin);
    freopen("o.txt", "w", stdout);
#endif
    int pounds, n;
    cout.setf(ios::fixed);
    cout.precision(3);
    while(cin>>pounds>>n && pounds>=0 && n>=0){
        rooms.clear(); idxs.clear();
        double sumjava = 0.0;
        for(int i=0; i<n; ++i){
            unsigned java, food;
            cin>>java>>food;
            rooms.push_back(Room(java, food));
            idxs.push_back(i);
        }
        sort(idxs.begin(), idxs.end(), lower);
        while(!idxs.empty()){
            if((unsigned)pounds >= rooms[idxs.back()].food){
                pounds -= rooms[idxs.back()].food;
                sumjava += rooms[idxs.back()].java;
                idxs.pop_back();
            } else {
                sumjava += pounds * rooms[idxs.back()].ratio;
                break;
            }
        }
        cout << sumjava << '\n';
    }
}
