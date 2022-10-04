#include<bits/stdc++.h>
using namespace std;
ifstream input("C:\\Users\\ACER\\Desktop\\input.txt");
int n,socanh;//so dinh,so canh
int s,t;//dinh dau va cuoi
int a[10000][10000];//ma tran ke
int truoc[10000];//danh dau diem truoc diem xet la diem nao
int d[10000];//danh dau khoang cach
int xet[10000]={0};
bool kiemtra(){int kt=0;
	for(int i=0;i<n;i++){
		if(xet[i]==0){kt=1;}
		}
	if(kt==0){
		return true;
	}		
	else{return false;
	}	
	}
void duyet(){
	int u,minp;//khai bao dinh dang xet va gia tri nho nhat tam thoi
	
	while (xet[t]==0) {
		minp = 10000000;
  //tìm d?nh u sao cho d[u] là nh? nh?t
		for (int v = 0; v < n; v++){
			if ((xet[v]==0) && (minp > d[v])){
    			u = v;
    			minp = d[v];
			}
  		}
  		xet[u] = 1;// u la dinh co nhan tam thoi nho nhat
  		if (xet[t]==0){
    	//gán nhãn l?i cho các d?nh.
   			for (int v = 0; v < n; v++){
    			if ((xet[v]==0) && (d[u] + a[u][v] < d[v])){
     				d[v] = d[u] + a[u][v];
     				truoc[v] = u;
    				}
   				}
  			}

 		}
   cout<<"chieu dai "<<minp<<endl;
	}
int main(){
	clock_t begin = clock();
	input>>n>>socanh>>s>>t;
	for (int i = 1; i <= socanh; i++){
		int x,y,z;
		input>>x>>y>>z;

		a[y][x]=z;
		a[x][y]=z;
		
 		}
 		for (int i = 0; i < n; i++){
		for (int j = 0; j < n; j++){
			if(a[i][j]<1){
				a[i][j]=10000;
			}
  	 		
  			}
 		}
 	for(int i=0;i<n;i++){
 		truoc[i]=s;
 		d[i]=a[s][i];
		}
	truoc[s]=0;
	d[s]=0;
	xet[s]=true;
	duyet()	;
	cout<<"duong di ";
	while(t!=s){
		cout<<t<<" ";
		t=truoc[t];
		}
		cout<<t<<endl;
	clock_t end = clock(); 
    cout<<"Time run: "<<(float)(end-begin)/CLOCKS_PER_SEC<<" s"<<endl;
	}	
