/*
ID: wjl1241
PROG: lgame
LANG: C++
*/
#include<fstream>
#include<vector>
#include<algorithm>
#include<string>
using namespace std;

int strscore(const string &str){
    int s[] = {2,5,4,4,1,6,5,5,1,7,6,3,5,2,3,5,7,2,1,2,4,6,6,7,5,7};
    int score = 0;
    for(size_t i = 0; i<str.length(); ++i)
        score += s[static_cast<int>(str[i] - 'a')];
    return score;
}
struct word{
    string str;
    string sorted;
    int score;
    word(const string &Str, const string &Sorted):str(Str), sorted(Sorted){
        score = strscore(str);
    }
};

typedef pair<string*, string*> strpair;
vector<word> dict;
int maxscore = 0;
vector<strpair> ans;

int main(){
    string instr;
    ifstream fin("lgame.in");
    fin>>instr;
    fin.close();
    sort(instr.begin(), instr.end());

    string inword;
    fin.open("lgame.dict");
    while(fin>>inword && inword != "."){
        string sorted(inword);
        sort(sorted.begin(), sorted.end());
        if(includes(instr.begin(), instr.end(), sorted.begin(), sorted.end()))
            dict.push_back(word(inword, sorted));
    }
    fin.close();

    // search for single word with maxscore
    for(vector<word>::iterator itr = dict.begin(); itr != dict.end(); ++itr){
        if(itr->score > maxscore){
            maxscore = itr->score;
            ans.clear();
        }
        if(itr->score == maxscore){
            ans.push_back(make_pair(&(itr->str), static_cast<string*>(NULL)));
        }

        if(instr.length() - itr->str.length() < 3)continue;
        //search for second word of the pair
        for(vector<word>::iterator itr2 = itr; itr2 != dict.end(); ++itr2){
            string combword;
            int score;
            if((score = itr->score + itr2->score) < maxscore)continue;
            if(itr->str.length() + itr2->str.length() > instr.length())continue;
            merge(itr->sorted.begin(), itr->sorted.end(),
                itr2->sorted.begin(), itr2->sorted.end(), back_inserter(combword));
            if(!includes(instr.begin(), instr.end(), combword.begin(), combword.end()))continue;
            if(score > maxscore){
                maxscore = score;
                ans.clear();
            }
            if(score == maxscore){
                ans.push_back(make_pair(&(itr->str), &(itr2->str)));
            }
        }
    }

    ofstream fout("lgame.out");
    fout<<maxscore<<"\n";
    for(vector<strpair>::iterator itr = ans.begin(); itr != ans.end(); ++itr){
        fout<< *(itr->first);
        if(itr->second != NULL)fout<<" "<< *(itr->second);
        fout<<"\n";
    }
    fout.close();
}

/*
#include<fstream>
#include<vector>
#include<string>
#include<list>
#include<algorithm>
#include<numeric>
#include<map>
using namespace std;

inline int letterscore(const char &ch){
    int s[] = {2,5,4,4,1,6,5,5,1,7,6,3,5,2,3,5,7,2,1,2,4,6,6,7,5,7};
    return s[static_cast<int>(ch - 'a')];
}

int stringscore(const string &str){    // the string should be sorted
    //sort(str.begin(), str.end());

    class letter_add{
    public:
        int operator()(const int &score, const char &ch) const {
            return score + letterscore(ch);
        }
    };

    //return std::accumulate(str.begin(), str.end(), 0, letter_add());
    int score = 0;
    for(size_t i = 0; i < str.length(); ++i)
        score += letterscore(str[i]);
    return score;
}

struct score_string{
    int score;
    list<string *> strs;
    score_string():score(0){}
    void push_back(string *pstr){
        if(score == 0)score = stringscore(*pstr);
        strs.push_back(pstr);
    }
};

vector<string> dict;
map<string, score_string> strtab;
vector<pair<string*, string*> > ans;
int maxscore = 0;

bool tryword(const string &word, map<string, score_string>::iterator prev_itr){
    // if find valid permword return true
    // word should be sorted in advance
    bool ret = false;
    vector<int> perm;
    for(size_t len=word.length(); len>=3; --len){
        perm.assign(word.length()-len, 0);
        perm.insert(perm.end(), len, 1);

        do {
            string permword;
            for(size_t i=0; i<perm.size(); ++i)if(perm[i])
                permword.push_back(word[i]);
            map<string, score_string>::iterator itr;
            if((itr = strtab.find(permword)) == strtab.end()) continue;
            ret = true;

            if(word.length() - permword.length() >= 3){
                string permword2;
                set_difference(word.begin(), word.end(), permword.begin(), permword.end(),
                    back_inserter(permword2));
                if(tryword(permword2, itr))continue;
            }

            // this is the last word can be formed, calculate the score
            int totalscore = itr->second.score;
            if(prev_itr != strtab.end())totalscore += prev_itr->second.score;
            if(totalscore >= maxscore){
                if(totalscore > maxscore){
                    maxscore = totalscore;
                    ans.clear();
                }
                if(prev_itr == strtab.end()){
                    for(list<string*>::iterator litr=itr->second.strs.begin();
                        litr != itr->second.strs.end(); ++litr)
                        ans.push_back(make_pair(*litr,(string*)NULL));
                }
                else {
                    for(list<string*>::iterator litr = prev_itr->second.strs.begin();
                        litr != prev_itr->second.strs.end(); ++litr){
                            for(list<string*>::iterator litr2 = itr->second.strs.begin();
                                litr2 != itr->second.strs.end(); ++litr2)
                                ans.push_back(make_pair(*litr, *litr2));
                    }
                }
            }
        } while (next_permutation(perm.begin(), perm.end()));
    }
    return ret;
}

class pair_less {
public:
    bool operator()(const pair<string*, string*> &p1, const pair<string*, string*> &p2) const {
        return (*(p1.first) < *(p2.first) || (!(*(p2.first) < *(p1.first)) && ((p1.second == NULL && p2.second != NULL) || (p1.second != NULL && p2.second != NULL && *(p1.second) < *(p2.second)))));
    }
};
class pair_exchange {
public:
    void operator()(pair<string*, string*> &p) const {
        if(p.second != NULL && *(p.first) > *(p.second))swap(p.first, p.second);
    }
};

int main(){
    ifstream fin("lgame.dict");
    string word;
    dict.reserve(40000);
    while(fin>>word && word != "."){
        dict.push_back(word);
    }
    fin.close();

    for(vector<string>::iterator itr=dict.begin(); itr!=dict.end(); ++itr){
        word = *itr;
        sort(word.begin(), word.end());
        strtab[word].push_back(&(*itr));
    }

    fin.open("lgame.in");
    fin>>word;
    fin.close();
    sort(word.begin(), word.end());

    tryword(word, strtab.end());
    for_each(ans.begin(), ans.end(), pair_exchange());
    sort(ans.begin(), ans.end(), pair_less());
    ans.erase(unique(ans.begin(), ans.end()), ans.end());

    ofstream fout("lgame.out");
    fout<<maxscore<<"\n";
    for(vector<pair<string*, string*> >::iterator itr = ans.begin();
        itr != ans.end(); ++itr){
            fout<< *(itr->first);
            if(itr->second != NULL)fout<<" "<< *(itr->second);
            fout<<"\n";
    }
    fout.close();
}
*/