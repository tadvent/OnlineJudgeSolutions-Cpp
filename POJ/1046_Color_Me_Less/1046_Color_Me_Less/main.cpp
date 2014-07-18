// POJ 1046 Color Me Less

#include<fstream>
#include<iostream>
#include<numeric>
#include<algorithm>
#include<vector>
using namespace std;

const int N = 16;
const vector<int> terminator(3, -1);

struct diff_sqr : public std::binary_function<int, int, int> {
    int operator()(int left, int right) const {
        int diff = left - right;
        return diff * diff;
    }
};
struct color_diff : public std::binary_function<vector<int>&, vector<int>&, int>{
    int operator()(const vector<int> &left, const vector<int> &right) const {
        return std::inner_product(left.begin(), left.end(), right.begin(), 0, plus<int>(), diff_sqr());
    }
};
class color_nearer : public std::binary_function<vector<int>&, vector<int>&, bool>{
    const vector<int> &color;
public:
    color_nearer(const vector<int> &c):color(c){}
    bool operator()(const vector<int> &left, const vector<int> &right) const {
        return color_diff()(left, color) < color_diff()(right, color);
    }
};

int main(){
    ifstream cin("1046_in.txt");
    ofstream cout("1046_out.txt");

    vector< vector<int> > samples(N, vector<int>(3));
    vector<int> now(3);

    for(int i=0; i<N; ++i)
        cin>>samples[i][0]>>samples[i][1]>>samples[i][2];

    cin>>now[0]>>now[1]>>now[2];
    while(now != terminator){
        vector< vector<int> >::iterator min_itr =
            min_element(samples.begin(), samples.end(), color_nearer(now));
        cout<<'('<<now[0]<<','<<now[1]<<','<<now[2]<<") maps to (";
        cout<<(*min_itr)[0]<<','<<(*min_itr)[1]<<','<<(*min_itr)[2]<<")\n";
        cin>>now[0]>>now[1]>>now[2];
    }
}
