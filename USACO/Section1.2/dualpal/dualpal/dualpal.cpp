/*
ID: wjl1241
PROG: dualpal
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
        nums.clear();
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
    bool is_dualpal(){
        bool pal=false;
        for(int i=2;i<=10;i++){
            setbase(i);
            if(is_pal()){
                if(pal)return true;
                pal=true;
            }
        }
        return false;
    }
};

int main(){
    ifstream fin("dualpal.in");
    ofstream fout("dualpal.out");

    int n,s;
    fin>>n>>s;
    int i=s+1;
    while(n>0){
        BaseNum tmp(i);
        if(tmp.is_dualpal()){
            fout<<i<<endl;
            n--;
        }
        i++;
    }

    return 0;
}