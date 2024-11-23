#include<bits/stdc++.h>
using namespace std;

vector<int> ans;

bool solve(vector<vector<int>> &allo, vector<vector<int>> &need,vector<int> &avail,int total , vector<int> &vis){
	if(total == 0) return true;


	for(int i = 0; i < 5; i++){
		if(vis[i] == 0){
			bool cando = true;
			for(int j = 0; j < 3; j++){
				if(need[i][j] <= avail[j]){
					continue;
				}
				else cando = false;
			}
			if(cando){
			for(int j = 0; j < 3; j++){
				avail[j] += allo[i][j];
			
			}

			ans.push_back(i);
			vis[i] = true;
			total--;
			if (solve(allo, need,avail, total , vis)) return true;
			ans.pop_back();
			vis[i] = false;
			total++;
			for(int j = 0; j < 3; j++){
			
				avail[j] -= allo[i][j];
			}

			}

		}
	
	}

	return false;

}


int main(){
	int n = 5;
	vector<vector<int>> allocated = {
		{0,1,0},{2,0,0},{3,0,2},{2,1,1},{0,0,2}
	
	} ;

	vector<vector<int>> max = {
		{7,5,3},{3,2,2},{9,0,2},{2,2,2},{4,3,3}
	
	};

	vector<int> avail = {3,3,2};

	vector<vector<int>> need;

	for(int i = 0; i < 5; i++){
		vector<int> x;
		for(int j = 0; j < 3; j++){
			x.push_back(max[i][j] - allocated[i][j]);
		
		}

		need.push_back(x);
	
	}
	
	vector<int> vis(n,0);
	bool temp = solve(allocated, need,avail,5,vis);
	
	if( temp) cout << "system is not in deadlock" << endl;
	else cout << "system in deadlock" << endl;
	

	if(temp){
	cout << "A valid sequence is " << endl;
	for (auto i : ans){
		cout << i << " ";
	}
	cout << endl;
	
	}
}


