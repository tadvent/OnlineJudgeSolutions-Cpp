/*
ID: wjl1241
PROG: shuttle
LANG: C++
*/

#include<fstream>
#include<algorithm>
#include<vector>
#include<iterator>
using namespace std;

// use 1..2N+1 to represents the 2N+1 holes
// strip[0] indicates the position of the empty hole
vector<char> strip;
const char W = 'W';
const char B = 'B';
const char E = 'E';

vector<int> steps;

void init(int N){
    strip.reserve(2*(N+1));
    strip.push_back(N+1);
    strip.insert(strip.end(), N, W);
    strip.push_back(E);
    strip.insert(strip.end(), N, B);
}

bool jump_step(char ch){
    // if can't do this operation then return false
    switch(ch){
        case W: // from left to right
            while(strip[0] > 1 && strip[strip[0] - 1] == B /*&& strip[strip[0] - 2] == W*/){
                steps.push_back(strip[0] - 2);
                swap(strip[strip[0] - 2], strip[strip[0]]);
                strip[0] -= 2;
            }
            if(strip[0] > 2 && strip[strip[0] - 2] == B)return false;
            if(strip[0] > 1){
                steps.push_back(strip[0] - 1);
                swap(strip[strip[0]], strip[strip[0] - 1]);
                --strip[0];
            }
            break;
        case B: // from right to left
            while(strip[0] < strip.size() - 1 && strip[strip[0] + 1] == W /*&& strip[strip[0] + 2] == B*/){
                steps.push_back(strip[0] + 2);
                swap(strip[strip[0] + 2], strip[strip[0]]);
                strip[0] += 2;
            }
            if(strip[0] < strip.size() - 2 && strip[strip[0] + 2] == W)return false;
            if(strip[0] < strip.size() - 1){
                steps.push_back(strip[0] + 1);
                swap(strip[strip[0]], strip[strip[0] + 1]);
                ++strip[0];
            }
            break;
    }
    return true;
}
bool step_jump(char ch){
    switch(ch){
        case W:
            if(strip[strip[0] - 1] != W)return false;
            steps.push_back(strip[0] - 1);
            swap(strip[strip[0]], strip[strip[0] - 1]);
            --strip[0];
            while(strip[0] > 2 && strip[strip[0] - 2] == W){
                steps.push_back(strip[0] - 2);
                swap(strip[strip[0]], strip[strip[0] - 2]);
                strip[0] -= 2;
            }
            break;
        case B:
            if(strip[strip[0] + 1] != B)return false;
            steps.push_back(strip[0] + 1);
            swap(strip[strip[0]], strip[strip[0] + 1]);
            ++strip[0];
            while(strip[0] < strip.size() - 2 && strip[strip[0] + 2] == B){
                steps.push_back(strip[0] + 2);
                swap(strip[strip[0]], strip[strip[0] + 2]);
                strip[0] += 2;
            }
            break;
    }
    return true;
}

int main(){
    ifstream fin("shuttle.in");
    int n;
    fin>>n;
    fin.close();

    char ch = W;
    char ch1 = B;
    init(n);
    while(jump_step(ch))swap(ch, ch1);
    while(step_jump(ch))swap(ch, ch1);

    ofstream fout("shuttle.out");
    vector<int>::iterator itr = steps.begin();
    while(distance(itr, steps.end()) > 20){
        copy(itr, itr + 19, ostream_iterator<int>(fout, " "));
        fout<< *(itr + 19)<<"\n";
        itr += 20;
    }
    copy(itr, --steps.end(), ostream_iterator<int>(fout, " "));
    fout<< *(--steps.end())<<"\n";
}
