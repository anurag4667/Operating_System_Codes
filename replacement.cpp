#include<bits/stdc++.h>

using namespace std;

int fifo(vector<int> &x, int n){
vector<int> allo(n,-1);

int front = 0;
int pagefaults = 0;

for(int i = 0; i < x.size(); i++){
	bool found = false;
	for(int j = 0; j < n; j++){
		if(allo[j] == x[i]) found = true;
	}

	if(found) continue;
	
	allo[front] = x[i];
	front = (front + 1)%n;
	pagefaults++;


}

return pagefaults;

}


int main(){
vector<int> x = {
	1,2,3,4,2,1,5,6,2,1,2,3,7,6,3
};

cout << "fifo 3 : "<< fifo(x,3) << endl;
cout << "fifo 4 : " << fifo(x,4) << endl;
cout << "fifo 5 : " << fifo(x,5) << endl;
}
