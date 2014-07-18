/*
ID: wjl1241
PROG: palsquare
LANG: C++
*/

#include<iostream>
#include<fstream>
#include<vector>
using namespace std;

class BaseNum{
    int base;
    int decnum;
    vector<int> nums;
public:
    BaseNum(int innum=0):base(10),decnum(innum){};
    void setbase(int basenum){
        base=basenum;
        int remain=decnum;
        while(remain!=0){
            nums.push_back(remain%base);
            remain/=base;
        }
    }
    bool is_pal(){
        for(int i=0;i<nums.size()/2;i++){
            if(nums[i]!=nums[nums.size()-i-1])return false;
        }
        return true;
    }
    friend ostream& operator<<(ostream& os,const BaseNum& obj){
        for(int i=obj.nums.size()-1;i>=0;i--){
            if(obj.nums[i]<10)os<<static_cast<char>(obj.nums[i]+48);
            else os<<static_cast<char>(obj.nums[i]+55);
        }
        return os;
    }
};

int main(){
    int base;
    ifstream fin("palsquare.in");
    ofstream fout("palsquare.out");
    fin>>base;
    fin.close();

    for(int i=1;i<=300;i++){
        BaseNum square(i*i);
        square.setbase(base);
        if(square.is_pal()){
            BaseNum ori(i);
            ori.setbase(base);
            fout<<ori<<' '<<square<<endl;
        }
    }

    return 0;
}