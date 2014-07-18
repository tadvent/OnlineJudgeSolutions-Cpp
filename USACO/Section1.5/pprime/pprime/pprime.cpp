/*
ID: wjl1241
PROG: pprime
LANG: C++
*/

#include<fstream>
#include<vector>
#include<math.h>
using namespace std;

std::vector<int>::iterator find_bin(const std::vector<int>::iterator &beg,const std::vector<int>::iterator &end,const int &key){
    std::vector<int>::iterator low=beg;
    std::vector<int>::iterator high=end;
    std::vector<int>::iterator mid;
    while(low<high){
        mid=(high-low)/2+low;
        if(key==(*mid)) return mid;
        else if(key<(*mid)) high=mid;
        else low=mid+1;
    }
    return end;
}

bool isPrime(const int a){
    static std::vector<int> prime(1,3);
    if(a<2)return false;
    if(a==2)return true;
    if(a%2==0)return false;
    if(a<=prime.back()){
        if(find_bin(prime.begin(),prime.end(),a)!=prime.end())return true;
        return false;
    }
    const int
        qa=static_cast<int>(sqrt(static_cast<long double>(a)));
    for(int num=prime.back()+2;qa>prime.back();num+=2){
        if(isPrime(num))prime.push_back(num);
    }
    std::vector<int>::iterator pos=prime.begin();
    for(;pos!=prime.end();++pos){
        if((*pos)>qa)break;
        if(a%(*pos)==0)break;
    }
    if(pos==prime.end())return true;
    if((*pos)>qa)return true;
    return false;
}

int main(){
    ifstream fin("pprime.in");
    ofstream fout("pprime.out");
    int max,min,d1,d2,d3,d4,palindrome;
    vector<int> ans;
    fin>>min>>max;
    if(min>max)swap(min,max);
    //for (d1 = 9; d1 > 0; d1-=2) {	/* only odd; evens aren't so prime */
    //    for (d2 = 9; d2 >= 0; d2--) {
    //        for (d3 = 9; d3 >= 0; d3--) {
    //            for(d4 = 9; d4 >= 0; d4--){
	   //             palindrome = 10000000*d1+1000000*d2+100000*d3+11000*d4+100*d3+10*d2+d1;
    //                if(palindrome<min || palindrome>max)continue;
	   //             if(isPrime(palindrome))ans.push_back(palindrome);
    //            }
	   //     }
    //    }
    //}
    for (d1 = 9; d1 > 0; d1-=2) {	/* only odd; evens aren't so prime */
        for (d2 = 9; d2 >= 0; d2--) {
            for (d3 = 9; d3 >= 0; d3--) {
                for(d4 = 9; d4 >= 0; d4--){
	                palindrome = 1000000*d1+100000*d2+10000*d3+1000*d4+100*d3+10*d2+d1;
                    if(palindrome<min || palindrome>max)continue;
	                if(isPrime(palindrome))ans.push_back(palindrome);
                }
	        }
        }
    }
    //for (d1 = 9; d1 > 0; d1-=2) {	/* only odd; evens aren't so prime */
    //    for (d2 = 9; d2 >= 0; d2--) {
    //        for (d3 = 9; d3 >= 0; d3--) {
    //            palindrome = 100000*d1+10000*d2+1100*d3+10*d2+d1;
    //            if(palindrome<min || palindrome>max)continue;
    //            if(isPrime(palindrome))ans.push_back(palindrome);
	   //     }
    //    }
    //}
    for (d1 = 9; d1 > 0; d1-=2) {	/* only odd; evens aren't so prime */
        for (d2 = 9; d2 >= 0; d2--) {
            for (d3 = 9; d3 >= 0; d3--) {
                palindrome = 10000*d1+1000*d2+100*d3+10*d2+d1;
                if(palindrome<min || palindrome>max)continue;
                if(isPrime(palindrome))ans.push_back(palindrome);
	        }
        }
    }
    //for (d1 = 9; d1 > 0; d1-=2) {	/* only odd; evens aren't so prime */
    //    for (d2 = 9; d2 >= 0; d2--) {
    //        palindrome = 1000*d1+110*d2+d1;
    //        if(palindrome<min || palindrome>max)continue;
    //        if(isPrime(palindrome))ans.push_back(palindrome);
    //    }
    //}
    for (d1 = 9; d1 > 0; d1-=2) {	/* only odd; evens aren't so prime */
        for (d2 = 9; d2 >= 0; d2--) {
            palindrome = 100*d1+10*d2+d1;
            if(palindrome<min || palindrome>max)continue;
            if(isPrime(palindrome))ans.push_back(palindrome);
        }
    }
    if(min<=11 && 11<=max)ans.push_back(11);
    for( d1 = 9; d1 > 4; d1-=2){
        palindrome = d1;
        if(palindrome<min || palindrome>max)continue;
        if(isPrime(palindrome))ans.push_back(palindrome);
    }

    for(int i=static_cast<int>(ans.size()-1);i>=0;--i)fout<<ans[i]<<'\n';

    return 0;
}