#include<bits/stdc++.h>

using namespace std;


int pagetable[8];


int main(){
	int pages = 8;
	int frames = 4;
	int page_size = 1024;
	for(int i = 0; i < 8; i++){
		pagetable[i] = (i < 4) ? i : -1; 
	}


	while(true){
	int logicaladdr;
	cin >> logicaladdr;

	int pageno = logicaladdr/page_size;
	int offset = logicaladdr%page_size;

	if(pageno > page_size) {
	cout << "exceed page size limit" << endl;
	}
	else if(pagetable[pageno] == -1 ){
	cout << "page fault" << endl;
	
	}
	else {
	cout << "phycial address : " << pagetable[pageno]*page_size + offset << endl;  
	
	}
	
	}

}
