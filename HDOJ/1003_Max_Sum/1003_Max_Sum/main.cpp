#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

struct maxsum{
    maxsum():idx(0), max(-1000000000), maxbeg(0), maxend(0),
        lastmax(-1), lastmaxbeg(0){}
    void operator()(int num){
        ++idx;
        if(lastmax >= 0){
            lastmax += num;
        } else {
            lastmax = num;
            lastmaxbeg = idx;
        }
        if(lastmax > max){
            max = lastmax;
            maxbeg = lastmaxbeg;
            maxend = idx;
        }
    }
    ostream& output(ostream& os) const {
        os << max << ' ' << maxbeg << ' ' << maxend;
        return os;
    }
private:
    int idx;
    int max, maxbeg, maxend;
    int lastmax, lastmaxbeg;
};

inline ostream& operator<<(ostream& os, const maxsum &ms){
    return ms.output(os);
}

int main(){
    freopen("i.txt", "r", stdin);
    freopen("o.txt", "w", stdout);
    int nCase;
    vector<int> nums;

    bool first = true;
    cin >> nCase;
    for(int iCase = 1; iCase <= nCase; ++iCase){
        int N, num;
        cin >> N;
        nums.clear();
        nums.reserve(N);
        while(N--){
            cin >> num;
            nums.push_back(num);
        }
        if(first)
            first = false;
        else cout << '\n';
        cout << "Case " << iCase << ":\n"
            << for_each(nums.begin(), nums.end(), maxsum())
            << '\n';
    }
}
