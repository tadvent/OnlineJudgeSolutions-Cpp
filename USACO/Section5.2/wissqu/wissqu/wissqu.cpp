/*
ID: wjl1241
LANG: C++
TASK: wissqu
*/

#include<cstdlib>
#include<fstream>
#include<iterator>
#include<algorithm>
using namespace std;

class farm{
    int cnt, cowat[16], cowleft[5];
    bool nochange[16];
    unsigned long long ajtcnt[5];
    const unsigned long long mask, maskl, maskr;
    pair<int, int> putorder[16];
    int dfscow[16], dfspos[16];

    void addcow(int cowidx, int posidx){
        switch(posidx){
            /*
                0  1  2  3
                4  5  6  7
                8  9 10 11
               12 13 14 15 
            */
            case 0:
            case 4:
                ajtcnt[cowidx] += maskl >> (5 - posidx) * 4;
                break;
            case 3:
                ajtcnt[cowidx] += maskr >> (5 - posidx) * 4;
                break;
            case 1:
            case 2:
                ajtcnt[cowidx] += mask >> (5 - posidx) * 4;
                break;
            case 5:
            case 6:
            case 9:
            case 10:
            case 13:
            case 14:
                ajtcnt[cowidx] += mask << (posidx - 5) * 4;
                break;
            case 8:
            case 12:
                ajtcnt[cowidx] += maskl << (posidx - 5) * 4;
                break;
            case 7:
            case 11:
            case 15:
                ajtcnt[cowidx] += maskr << (posidx - 5) * 4;
                break;
        }
        cowat[posidx] = cowidx;
    }
    int replace(int newcow, int posidx){
        int oldcow = cowat[posidx];
        unsigned long long m;
        switch(posidx){
            case 0:
            case 4:
                m = maskl >> (5 - posidx) * 4;
                ajtcnt[newcow] += m;
                ajtcnt[oldcow] -= m;
                break;
            case 3:
                m = maskr >> (5 - posidx) * 4;
                ajtcnt[newcow] += m;
                ajtcnt[oldcow] -= m;
                break;
            case 1:
            case 2:
                m = mask >> (5 - posidx) * 4;
                ajtcnt[newcow] += m;
                ajtcnt[oldcow] -= m;
                break;
            case 5:
            case 6:
            case 9:
            case 10:
            case 13:
            case 14:
                m = mask << (posidx - 5) * 4;
                ajtcnt[newcow] += m;
                ajtcnt[oldcow] -= m;
                break;
            case 8:
            case 12:
                m = maskl << (posidx - 5) * 4;
                ajtcnt[newcow] += m;
                ajtcnt[oldcow] -= m;
                break;
            case 7:
            case 11:
            case 15:
                m = maskr << (posidx - 5) * 4;
                ajtcnt[newcow] += m;
                ajtcnt[oldcow] -= m;
                break;
        }
        cowat[posidx] = newcow;
        return oldcow;
    }
    bool putable(int cowidx, int posidx) const {
        return !((ajtcnt[cowidx] >> posidx*4) & 0xF);
    }
    void dfs(int idx){
        int oldcow;
        if(idx == 16){
            if(!(cnt++)){
                for(int i = 0; i < 16; ++i)
                    putorder[i] = make_pair(dfscow[i], dfspos[i]);
            }
            return;
        }
        int &cow(dfscow[idx]), &pos(dfspos[idx]);
        for(cow = 0; cow < 5; ++cow)if(cowleft[cow]){
            --cowleft[cow];
            for(pos = 0; pos < 16; ++pos)if(nochange[pos] && putable(cow, pos)){
                nochange[pos] = false;
                oldcow = replace(cow, pos);
                dfs(idx + 1);
                replace(oldcow, pos);
                nochange[pos] = true;
            }
            ++cowleft[cow];
        }
    }
public:
    template<class Iter>
    farm(Iter beg, Iter end): cnt(0), mask (0x011101110111ULL),
        maskl(0x011001100110ULL), maskr(0x001100110011ULL){
        fill_n(ajtcnt, 5, 0);
        fill_n(cowleft, 5, 3);
        fill_n(nochange, 16, true);
        for(int i=0; beg != end; ++beg, ++i)
            addcow(*beg - 'A', i);
    }
    void calput(void){
        int oldcow, &pos(dfspos[0]);
        dfscow[0] = 3;
        for(pos = 0; pos < 16; ++pos)if(putable(3, pos)){
            nochange[pos] = false;
            oldcow = replace(3, pos);
            dfs(1);
            replace(oldcow, pos);
            nochange[pos] = true;
        }
    }
    ostream& output(ostream& os){
        for(int i=0; i<16; ++i){
            div_t pos = div(putorder[i].second, 4);
            os << char(putorder[i].first + 'A') << ' '
                << pos.quot + 1 << ' ' << pos.rem + 1 << '\n';
        }
        os << cnt << '\n';
        return os;
    }
};

int main(){
    ifstream fin("wissqu.in");
    farm wissqu((istream_iterator<char>(fin)), istream_iterator<char>());
    fin.close();
    ofstream fout("wissqu.out");
    wissqu.calput();
    wissqu.output(fout);
    fout.close();
}

//////////////////////////////////////////////////////

//#ifdef _DEBUG
//#include<iostream>
//#include<algorithm>
//#include<functional>
//#endif
//
//#include<cstdlib>
//#include<fstream>
//#include<iterator>
//using namespace std;
//
//class farm{
//    int cnt, cowat[16], cowleft[5];
//    bool nochange[16];
//    unsigned long long ajtcnt[5];
//    const unsigned long long mask, maskl, maskr;
//
//    void addcow(int cowidx, int posidx){
//        switch(posidx){
//            /*
//                0  1  2  3
//                4  5  6  7
//                8  9 10 11
//               12 13 14 15 
//            */
//            case 0:
//            case 4:
//                ajtcnt[cowidx] += maskl >> (5 - posidx) * 4;
//                break;
//            case 3:
//                ajtcnt[cowidx] += maskr >> (5 - posidx) * 4;
//                break;
//            case 1:
//            case 2:
//                ajtcnt[cowidx] += mask >> (5 - posidx) * 4;
//                break;
//            case 5:
//            case 6:
//            case 9:
//            case 10:
//            case 13:
//            case 14:
//                ajtcnt[cowidx] += mask << (posidx - 5) * 4;
//                break;
//            case 8:
//            case 12:
//                ajtcnt[cowidx] += maskl << (posidx - 5) * 4;
//                break;
//            case 7:
//            case 11:
//            case 15:
//                ajtcnt[cowidx] += maskr << (posidx - 5) * 4;
//                break;
//        }
//        cowat[posidx] = cowidx;
//    }
//    int replace(int newcow, int posidx){
//        int oldcow = cowat[posidx];
//        unsigned long long m;
//        switch(posidx){
//            /*
//                0  1  2  3
//                4  5  6  7
//                8  9 10 11
//               12 13 14 15 
//            */
//            case 0:
//            case 4:
//                m = maskl >> (5 - posidx) * 4;
//                ajtcnt[newcow] += m;
//                ajtcnt[oldcow] -= m;
//                break;
//            case 3:
//                m = maskr >> (5 - posidx) * 4;
//                ajtcnt[newcow] += m;
//                ajtcnt[oldcow] -= m;
//                break;
//            case 1:
//            case 2:
//                m = mask >> (5 - posidx) * 4;
//                ajtcnt[newcow] += m;
//                ajtcnt[oldcow] -= m;
//                break;
//            case 5:
//            case 6:
//            case 9:
//            case 10:
//            case 13:
//            case 14:
//                m = mask << (posidx - 5) * 4;
//                ajtcnt[newcow] += m;
//                ajtcnt[oldcow] -= m;
//                break;
//            case 8:
//            case 12:
//                m = maskl << (posidx - 5) * 4;
//                ajtcnt[newcow] += m;
//                ajtcnt[oldcow] -= m;
//                break;
//            case 7:
//            case 11:
//            case 15:
//                m = maskr << (posidx - 5) * 4;
//                ajtcnt[newcow] += m;
//                ajtcnt[oldcow] -= m;
//                break;
//        }
//        cowat[posidx] = newcow;
//        return oldcow;
//    }
//    bool putable(int cowidx, int posidx) const {
//        return !((ajtcnt[cowidx] >> posidx*4) & 0xF);
//    }
//    bool outdfs(pair<int, int> putorder[], int idx){
//        int oldcow;
//        bool flag = false;
//        if(idx == 16)return true;
//        for(int cow = 0; cow < 5; ++cow)if(cowleft[cow]){
//            --cowleft[cow];
//            for(int pos = 0; pos < 16; ++pos)if(nochange[pos] && putable(cow, pos)){
//                nochange[pos] = false;
//                oldcow = replace(cow, pos);
//                flag = outdfs(putorder, idx + 1);
//                replace(oldcow, pos);
//                nochange[pos] = true;
//                if(flag){
//                    putorder[idx] = make_pair(cow, pos);
//                    break;
//                }
//            }
//            ++cowleft[cow];
//            if(flag)return true;
//        }
//        return false;
//    }
//    void cntdfs(int idx){
//        int oldcow;
//        if(idx == 16){
//            ++cnt;
//            return;
//        }
//        for(int cow = 0; cow < 5; ++cow)if(cowleft[cow]){
//            --cowleft[cow];
//            for(int pos = 0; pos < 16; ++pos)if(nochange[pos] && putable(cow, pos)){
//                nochange[pos] = false;
//                oldcow = replace(cow, pos);
//                cntdfs(idx + 1);
//                replace(oldcow, pos);
//                nochange[pos] = true;
//            }
//            ++cowleft[cow];
//        }
//    }
//public:
//    template<class Iter>
//    farm(Iter beg, Iter end):
//    cnt(0),
//    mask (0x0000011101110111ULL),
//    maskl(0x0000011001100110ULL),
//    maskr(0x0000001100110011ULL){
//        for(int i=0; i<5; ++i){
//            ajtcnt[i] = 0;
//            cowleft[i] = 3;
//        }
//        for(int i=0; i<16; ++i)nochange[i] = true;
//        for(int i=0; beg != end; ++beg, ++i){
//            addcow(*beg - 'A', i);
//        }
//    }
//    ostream& output(ostream& os){
//        int oldcow;
//        bool flag = false;
//        pair<int, int> putorder[16];
//        for(int i=0; i<16; ++i)if(putable(3, i)){  // try to put 'D'
//            nochange[i] = false;
//            oldcow = replace(3, i);
//            flag = outdfs(putorder, 1);
//            replace(oldcow, i);
//            nochange[i] = true;
//            if(flag){
//                putorder[0] = make_pair(3, i);
//                break;
//            }
//        }
//        for(int i=0; i<16; ++i){
//            div_t pos = div(putorder[i].second, 4);
//            os << char(putorder[i].first + 'A') << ' '
//                << pos.quot + 1 << ' ' << pos.rem + 1 << '\n';
//        }
//        return os;
//    }
//    int count(void){
//        int oldcow;
//        cnt = 0;
//        for(int i=0; i<16; ++i)if(putable(3, i)){
//            nochange[i] = false;
//            oldcow = replace(3, i);
//            cntdfs(1);
//            replace(oldcow, i);
//            nochange[i] = true;
//        }
//        return cnt;
//    }
//#ifdef _DEBUG
//    ostream& debugout(ostream& os){
//        os << "cowleft: ";
//        copy(cowleft, cowleft + 5, ostream_iterator<int>(os, " "));
//        os << "\nCows: ";
//        transform(cowat, cowat + 16, ostream_iterator<char>(os),
//            bind2nd(plus<int>(), 'A'));
//        os << endl;
//        return os;
//    }
//#endif
//};
//
//int main(){
//    ifstream fin("wissqu.in");
//    farm wissqu((istream_iterator<char>(fin)), istream_iterator<char>());
//    fin.close();
//
//    ofstream fout("wissqu.out");
//    wissqu.output(fout);
//#ifdef _DEBUG
//    wissqu.debugout(cout);
//    system("pause");
//#endif
//    fout << wissqu.count() << '\n';
//    fout.close();
//}
