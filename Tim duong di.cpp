#include<iostream>
#include<fstream>
#include<conio.h>
#include<time.h> 
#define MAX 50
#define VOCUNG 10000000
using namespace std;
int n,m;//so dinh,canh cua do thi
int s;//dinh dau
int t;//dinh cuoi
int G[MAX][MAX];  //ma tran trong so
int d[MAX];  //mang do dai duong di
int truoc[MAX];  //mang danh dau duong di
int chuaxet[MAX];  //xac dinh mot dinh da duoc xet chua; 0: chua xet, 1: da xet
ofstream fOut("ketqua.out"); 

//Nhap du lieu
void Init()
{
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

void Dijkstra(void){
//khoi tao nhan tam thoi cho cac dinh.
	for (int i = 0; i < n; i++){
		d[i] = G[s][i];
		truoc[i] = s;
		chuaxet[i] = 0;
	}
	d[s] = 0;
	truoc[s] = 0;
	chuaxet[s] = 1;
	
//buoc lap
	while (chuaxet[t]!=1){
		int u;
		int minp = VOCUNG;  //tim dinh u sao cho d[u] là nho nhat
		for (int i = 0; i < n; i++){
			if ((chuaxet[i]==0) && (d[i] < minp)){
				u = i;	
				minp = d[i];
   			}
		}
		chuaxet[u] = 1;// u la dinh co nhan tam thoi nho nhat
		//cap nhat lai mang d
		for (int i = 0; i < n; i++){ 
   			if ((chuaxet[i]==0) && (d[u] + G[u][i] < d[i])){
		    	d[i] = d[u] + G[u][i];
   				truoc[i] = u;
   			}
  		}
  	}
}
void Result(void){

	Dijkstra();
	fOut<<"Duong di ngan nhat tu "<<s<<" -> "<<t<< " : "<<endl;
	fOut<<t<<" <- "; //In dinh cuoi
	int i = truoc[t];
	while (i != s){
		fOut<<i<<" <- ";
		i = truoc[i];
	}
	fOut<<s;//in dinh dau 
	fOut<<endl<<"Do dai duong di la : "<< d[t]<<endl;
	
	cout<<"Da thuc hien xong - Luu tai ketqua.out"<<endl;
	
}

int main(void){
	clock_t begin_time = clock(); //ghi lai thoi gian dau

	Init();
	Result();
	
	clock_t end_time = clock(); //ghi lai thoi gian luc sau
	
    cout<<"Thoi gian chay : "<<(float)(end_time-begin_time)/CLOCKS_PER_SEC<<" s"<<endl;
    fOut<<"Thoi gian chay : "<<(float)(end_time-begin_time)/CLOCKS_PER_SEC<<" s"<<endl;
    
 	fOut.close();
	return (0);
}

