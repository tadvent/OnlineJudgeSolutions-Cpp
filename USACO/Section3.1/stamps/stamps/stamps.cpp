/*
ID: wjl1241
PROG: stamps
LANG: C++
*/

#include<fstream>
#include<vector>
#include<algorithm>
using namespace std;

vector<long> values;
vector<long> use;

int main(){
    ifstream fin("stamps.in");
    ofstream fout("stamps.out");
    int k,n;
    fin>>k>>n;
    values.resize(n);
    for(int i=0;i<n;++i)fin>>values[i];
    sort(values.begin(),values.end());

    int amount=0;
    use.push_back(0);

    while(use.back()<=k){
        long newcnt=500;
        ++amount;
        for(vector<long>::iterator itr=values.begin();itr!=values.end();++itr){
            if( (*itr)<=amount ){
                newcnt = min( use[amount-(*itr)]+1, newcnt );
            }
            else break;
        }
        use.push_back(newcnt);
    }

    fout<<amount-1<<endl;

    return 0;
}