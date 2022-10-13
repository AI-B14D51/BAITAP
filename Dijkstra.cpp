#include<iostream>
#include<fstream>
#include<conio.h>
#include<time.h> 
#define MAX 50
#define VOCUNG 10000000
using namespace std;
int n,m;// n: đỉnh, m: cạnh
int s;// đỉnh đầu
int t;// đỉnh cuối
int G[MAX][MAX];  //ma trận trọng số
int d[MAX];  // mảng tổng quãng đường đi
int truoc[MAX];  // mảng đánh dấu đường đi
int chuaxet[MAX];  // xác định đỉnh xét (0 và 1)
ofstream fOut("file.out"); 

//Nhập dữ liệu
void Init()
{
	ifstream fIn("file.in");  
    fIn >>n>>m>>s>>t;
    int x,y,z;
    for (int i = 1; i <= m; i++){  //Chuyển sang ma trận kề
            fIn >> x >> y >> z;
            G[x][y]=z;
            G[y][x]=z;
        }
    fIn.close();
	for (int i = 0; i < n; i++){//Nhập ma trận của đồ thị
		for (int j = 0; j < n; j++){
			if (G[i][j] == 0) G[i][j] = VOCUNG;
		}
	}
}

void Dijkstra(void){
//Khởi tạo nhãn tạm thời cho các đỉnh
	for (int i = 0; i < n; i++){
		d[i] = G[s][i];
		truoc[i] = s;
		chuaxet[i] = 0;
	}
	d[s] = 0;
	truoc[s] = 0;
	chuaxet[s] = 1;
	
//Bước lặp
	while (chuaxet[t]!=1){
		int u;
		int minp = VOCUNG;  // Tìm đỉnh u sao cho d[u] min
		for (int i = 0; i < n; i++){
			if ((chuaxet[i]==0) && (d[i] < minp)){
				u = i;	
				minp = d[i];
   			}
		}
		chuaxet[u] = 1;// u la đỉnh có nhãn tạm thời min
		//cập nhật lại mảng D
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
	fOut<<"Đường đi ngắn nhất từ "<<s<<" -> "<<t<< " : "<<endl;
	fOut<<t<<" <- "; //Đây là đỉnh cuối
	int i = truoc[t];
	while (i != s){
		fOut<<i<<" <- ";
		i = truoc[i];
	}
	fOut<<s;//In đỉnh đầu
	fOut<<endl<<"Độ dài đường đi là : "<< d[t]<<endl;
	
}

int main(void){
	clock_t begin_time = clock(); //Ghi lại thời gian đầu

	Init();
	Result();
	
	clock_t end_time = clock(); //Ghi lại thời gian lúc sau
	
    cout<<"Thoi gian chay : "<<(float)(end_time-begin_time)/CLOCKS_PER_SEC<<" s"<<endl;
    fOut<<"Thoi gian chay : "<<(float)(end_time-begin_time)/CLOCKS_PER_SEC<<" s"<<endl;
    
 	fOut.close();
	return (0);
}