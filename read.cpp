#include<iostream>
#include<fstream>
#include<istream>
#include<vector>
#include<string>
#include <bits/stdc++.h> 
using namespace std;

int main(){
	ifstream input("mnist_test.csv");
	int c=0;
	vector< vector<double> > data;
	vector<string> label;
	int row=0,col=0;
	while(input.good()){
		
		string val;
		getline(input,val);
		if(row!=0){
		stringstream ss(val);
		string inp;
		vector<double> dat_row;
		while(getline(ss,inp,',')){
			dat_row.push_back(stod(inp));
			col++;
		}

        data.push_back(dat_row);
			
		if(col==785){
			col=0;
			row++;
		}
		}
		else{
			row++;
		}
	}
	input.close();
	cout<<"--";
	//cout<<data.size()<<"///";
	for(int i=0;i<data.size();i++){
		for(int j=0;j<data[i].size();j++){
			cout<<data[i][j]<<",";
		}
		cout<<endl<<endl<<endl;
	}
}