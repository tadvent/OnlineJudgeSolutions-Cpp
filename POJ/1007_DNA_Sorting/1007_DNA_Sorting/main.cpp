#include<fstream>
#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
using namespace std;
struct DNA{
    string seq;
    int unsortedness;
    void cal(){
        int cnt[4] = {0};
        unsortedness = 0;
        for(string::iterator i=seq.begin(); i!=seq.end(); ++i){
            switch(*i){
                case 'A':
                    unsortedness += cnt[1] + cnt[2] + cnt[3];
                    //++cnt[0];
                    break;
                case 'C':
                    unsortedness += cnt[2] + cnt[3];
                    ++cnt[1];
                    break;
                case 'G':
                    unsortedness += cnt[3];
                    ++cnt[2];
                    break;
                case 'T':
                    ++cnt[3];
                    break;
            }
        }
    }
};

vector<DNA> vDNAs;
vector<DNA*> pDNAs;

struct DNA_unsort_less{
    bool operator()(const DNA* l, const DNA* r)const{
        return l->unsortedness < r->unsortedness;
    }
};

int main(){
    ifstream cin("i.txt");
    ofstream cout("o.txt");
    int len, n, i=0;
    cin>>len>>n;
    vDNAs.resize(n);
    pDNAs.reserve(n);

    while(n--){
        cin>>vDNAs[i].seq;
        vDNAs[i].cal();
        pDNAs.push_back(&vDNAs[i++]);
    }
    stable_sort(pDNAs.begin(), pDNAs.end(), DNA_unsort_less());
    for(vector<DNA*>::iterator i=pDNAs.begin(); i!=pDNAs.end(); ++i)
        cout<< (*i)->seq <<'\n';
}