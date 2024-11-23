#include<bits/stdc++.h>

using namespace std;

void first(vector<int> space,vector<int> process){


	for(int i = 0; i < 5; i++){
		if(process[i]){
		bool allocated = false;
		for(int j = 0; j < 5; j++){
			if(space[j] >= process[i]){
			cout << "process " << i << " will go to space " << j << endl;
			space[j] -= process[i];
			process[i] = 0;
			allocated = true;
			break;
			}
		}
		if(!allocated)
			cout << "process " << i << " have to wait" << endl;
		}
	}





}

void worst(){}

void best(){}


int main(){

vector<int> spaces = {20,40,80,200,100};

vector<int> process = {10,50,40,100,180};



cout << "first fit" << endl;
first(spaces , process);
cout << "worst fit" << endl;
worst();

cout << "best fit" << endl;
best();

}
