#include<bits/stdc++.h>
using namespace std;
int n;
int a[100];//luu cau hinh tam thoi
int b[100][100];
int c[100]={0};
int sodinhdadi=1;
vector <int> kq;
int chieudai;
ifstream input ("C:\\Users\\ACER\\Desktop\\input.txt");
ofstream output("D://CTDL//output.txt");
void Try(int i,int i2){
	for(int j=0;j<n;j++){
		if(c[j]==0&&j!=i&&chieudai<10000){
			a[sodinhdadi]=j;
			chieudai+=b[i][j];
			c[j]=1;
			sodinhdadi++;
			if(j!=i2){
				Try(j,i2);
					
			}
			else{
				//chieudai+=b[j][i2];
				kq.push_back(chieudai);
				//chieudai-=b[j][i2];
				//a[sodinhdadi]=i2;
				for(int ii=sodinhdadi;ii<=n;ii++){
					a[ii]=-1;
				}
				for(int ii=0;ii<=n;ii++){
					kq.push_back(a[ii]);
					}
				}
			chieudai-=b[i][j];
			sodinhdadi--;	
			c[j]=0;		
			}	
		}
	}
int main(){
	clock_t begin = clock();
	input>>n;
	int t,s;
	int socanh;
	input>>socanh>>s>>t;

	for(int i=1;i<=socanh;i++){
    	int x,y;
    	input>>x;
    	input>>y;
    	input>>b[x][y];	
		b[y][x]=b[x][y];	
//		cout<<x<<" "<<y<<" "<<b[x][y]<<endl;
		}
	for(int i =0;i<n;i++){
		for(int j=0;j<n;j++){
			if(b[i][j]<1){
				b[i][j]=10000;
				}
		//	cout<<b[i][j]<<" ";
		}
	//	cout<<endl;
	}
	a[0]=0;
	c[0]=1;
	Try(0,12);
//	for(int i=0;i<kq.size();i++){
//		cout<<kq[i]<<" ";
//	}	cout<<endl;
	int min=10000;
	for(int i=0;i<kq.size();i=i+n+2){
		//cout<<kq[i]<<" ";
		if(kq[i]<min){
			min=kq[i];
			}		
		}		
	for(int i=0;i<kq.size();i=i+n+2){
		if(kq[i]==min){
			cout<<"do dai: "<<min<<endl<<"duong di: ";
			int ii=i+1;
			while(kq[ii]>=0){
				cout<<kq[ii]<<" ";
				ii=ii+1;
				}
				cout<<endl;
//			for(int ii=i+1;ii<=i+6;ii++){
//				cout<<kq[ii]<<" ";
//				}
			}
		}
	clock_t end = clock(); 
    cout<<"Time run: "<<(float)(end-begin)/CLOCKS_PER_SEC<<" s"<<endl;
	}	
