#include<iostream>
#include<fstream>
#include<conio.h>
#include<time.h>
#include<vector>
#define MAX 100
#define TRUE 1
#define FALSE  0
#define VOCUNG 10000000
using namespace std;

int n,m;//so dinh, so canh
int s;//dinh dau
int t;//dinh cuoi
char chon;
int G[MAX][MAX];  //ma tran trong so
int D[MAX][MAX];  //ma tran trong so DFS
int d[MAX];  //mang do dai duong di
int truoc[MAX];  //mang danh dau duong di
int chuaxet[MAX];  //xac dinh mot dinh da duoc xet chua; 0: chua xet, 1: da xet
int dMin = 10000; // duong di ngan nhat DFS
bool visited[MAX]; // cac dinh da ghe tham DFS
vector<int> mark, res; // Luu vet duong di DFS

ofstream fOut("ketquamain.out"); 

void InitBFS(void){
	
 	ifstream fIn("Rommania.in");  
    fIn >>n>>m>>s>>t;
    int x,y,z;
    for (int i = 1; i <= m; i++){  //chuyen sang ma tran ke 
            fIn >> x >> y >> z;
            G[x][y]=z;
            G[y][x]=z;
        }
    fIn.close();
	for (int i = 0; i < n; i++){//nhap ma tran cua do thi.
		for (int j = 0; j < n; j++){
			if (G[i][j] == 0) G[i][j] = VOCUNG;
		}
	}
}

void ResultBFS(void){
 
	fOut << "BFS\n";
	fOut<<"Duong di ngan nhat tu "<<s<<" den "<<t<< " la"<<endl;
	fOut<<t<<"<=";//in dinh cuoi
 	int i = truoc[t];
 	while (i != s){
 		fOut<<i<<"<=";//in ra ket qua
  		i = truoc[i];
 	}
 	fOut<<s;//in dinh dau
 	fOut<<endl<<"Do dai duong di la : "<< d[t]<<endl;
}

void BFS(void){
	int u, minp;
 	//khoi tao nhan tam thoi cho cac dinh.
 	for (int v = 0; v < n; v++){
  		d[v] = G[s][v];
  		truoc[v] = s;
  		chuaxet[v] = FALSE;
	}
 	truoc[s] = 0;
	d[s] = 0;
	chuaxet[s] = TRUE;
	//buoc lap
 	while (!chuaxet[t]) {
  		minp = VOCUNG;
  		//tim dinh u sao cho d[u] là nho nhat
  		for (int v = 0; v < n; v++){
   			if ((!chuaxet[v]) && (minp > d[v])){
    			u = v;
    			minp = d[v];
   			}
  		}
  		chuaxet[u] = TRUE;// u la dinh co nhan tam thoi nho nhat
  		if (!chuaxet[t]){
   		//gan nhan lai cho cac dinh.
   			for (int v = 0; v < n; v++){
    			if ((!chuaxet[v]) && (d[u] + G[u][v] < d[v])){
    				d[v] = d[u] + G[u][v];
    				truoc[v] = u;
    			}
   			}
  		}
 	}	
}

void InitDFS() {
	ifstream fIn("Rommania.in");  
    fIn >>n>>m>>s>>t;
    int x,y,z;
    
    for (int i = 1; i <= m; i++){  //chuyen sang ma tran ke 
            fIn >> x >> y >> z;
            D[x][y]=z;
            D[y][x]=z;
        }
    fIn.close();
}

int sumOfMark() { // Tong chieu dai duong di
	int res = 0;
 	for (int i = 0; i < mark.size() - 1; i++) {
  		res += D[mark[i]][mark[i + 1]];
 	}
 	return res;
}

void DFS(int u) {
	for (int i = 0; i < n; i++) {
  		if(!visited[i] && D[u][i]) {
   			mark.push_back(i);
   			visited[i] = true;
   			if(i == t) {
    			if(sumOfMark() < dMin) {
    				dMin = sumOfMark();
    				res = mark;
    			}
    			mark.pop_back();
    			visited[i] = false;
   			}
			else {
    			DFS(i);
    			mark.pop_back();
    			visited[i] = false;
  			}
  		}
	}		
}

void ResultDFS() {
	
	fOut << "\n\nDFS\n";
 	fOut<<"Duong di ngan nhat tu "<<s<<" den "<<t<< " la"<<endl;
	for(int i = 0; i < res.size() - 1; i++)
  		fOut << res[i] << "=>";
 		fOut << res[res.size() - 1];
 		fOut<<endl<<"Do dai duong di la : "<< dMin<<endl;
}

int main(){
	// BFS
		clock_t start,end;
 	start = clock();
 	InitBFS();
 	BFS();
 	ResultBFS();
 	end = clock();
 	cout<<"Thoi gian chay BFS: "<<(float)(end-start)/CLOCKS_PER_SEC<<" s"<<endl;
    fOut<<"Thoi gian chay BFS: "<<(float)(end-start)/CLOCKS_PER_SEC<<" s"<<endl;
    
 	// DFS
 	start = clock();
 	InitDFS();
 	mark.push_back(s);
	visited[s] = true;
	DFS(s);
	ResultDFS();
	end = clock();
	cout<<"Thoi gian chay DFS: "<<(float)(end-start)/CLOCKS_PER_SEC<<" s"<<endl;
    fOut<<"Thoi gian chay DFS: "<<(float)(end-start)/CLOCKS_PER_SEC<<" s"<<endl;
 	fOut.close();
 	cout<<"Da thuc hien xong";
 	return 0;
}
