#ifndef ROTATOR
#define ROTATOR

#include<vector>
#include<iostream>
#include<string>
using namespace std;

template<typename bitype>
class rotator{
	vector<vector<bitype> > container;
	vector<int> ptr;
	int jinwei;
public:
	rotator():jinwei(0){};
	bool turn(int bit=-1,int num=1){
        if(bit<0)bit=container.size()-1;
		jinwei=num;
		int i=bit;
		for(;i>=0;i--){
			int temp=ptr[i]+jinwei;
			jinwei=temp/container[i].size();
			ptr[i]=temp%container[i].size();
            if(jinwei==0)break;
		}
		if(i<0)return false;
		return true;
	}
	bool set(int bit,int num=0){
		if(bit<0||bit>=container.size())
			return false;
		if(num<=0||num>=container.size())
			return false;
		ptr[bit]=num;
		return true;
	}
	bool reset(int num=0){
		for(int i=0;i<container.size();i++)
			if(!set(i,num))return false;
		return true;
	}
	bool push_back(vector<bitype> bitver){
		if(bitver.size()==0)return false;
		container.push_back(bitver);
		ptr.push_back(0);
		return true;
	}
    friend ostream& operator<<(ostream& os,const rotator<bitype> &obj){
        for(int i=0;i<obj.container.size();i++){
            os<<obj.container[i][obj.ptr[i]];
        }
        return os;
    }
    string strout(void){
        string out;
        for(int i=0;i<container.size();i++){
            out.push_back(container[i][ptr[i]]);
        }
        return out;
    }
};

#endif