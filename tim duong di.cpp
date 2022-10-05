#include<bits/stdc++.h>
using namespace std;

int n,socanh,start,finish;
int n1,socanh1,s1,t1;
int a[1000][1000];
int a1[1000][1000];
int truoc[1000];
int d[1000];
int xet[1000]={0};

int checked=1;
vector <int> kq;
int chieudai=0;
int tmp[1000];

void BFS()
{
	int u,min;
	
	while (xet[finish]==0) 
	{
		min = 10000000;
		for (int v = 0; v < n; v++)
		{
			if ((xet[v]==0) && (min > d[v]))
			{
    			u = v;
    			min = d[v];
			}
  		}
  		xet[u] = 1;
  		if (xet[finish]==0)
		{
   			for (int v = 0; v < n; v++)
			{
    			if ((xet[v]==0) && (d[u] + a[u][v] < d[v]))
				{
     				d[v] = d[u] + a[u][v];
     				truoc[v] = u;
    			}
   			}
  		}

 	}
   cout<<"Do dai duong di: "<<min<<endl;
}

void DFS(int i,int i2)
{
	for(int j=0;j<n;j++)
	{
		if(xet[j]==0&&j!=i&&chieudai<10000)
		{
			tmp[checked]=j;
			chieudai+=a[i][j];
			xet[j]=1;
			checked++;
			if(j!=i2)
			{
				DFS(j,i2);
			}
			else
			{
				kq.push_back(chieudai);
				for(int ii=checked;ii<=n;ii++)
				{
					tmp[ii]=-1;
				}
				for(int ii=0;ii<=n;ii++)
				{
					kq.push_back(tmp[ii]);
				}
			}
			chieudai-=a[i][j];
			checked--;	
			xet[j]=0;		
		}	
	}
}

void XuLyBFS(){
	clock_t begin = clock();
 		for(int i=0;i<n;i++)
		{
 			truoc[i]=start;
 			d[i]=a[start][i];
		}
		truoc[start]=0;
		d[start]=0;
		xet[start]=true;
		BFS()	;
		cout<<"Duong di ";
		while(finish!=start)
		{
			cout<<finish<<" -> ";
			finish=truoc[finish];
		}
	cout<<finish<<endl;
	clock_t end = clock(); 
    cout<<"Thoi gian BFS: "<<(float)(end-begin)/CLOCKS_PER_SEC<<" s"<<endl;
 		
}
void XuLyDFS(){
	 clock_t beginDFS = clock();
    
    tmp[0]=0;
	xet[0]=1;
	DFS(start,finish);
	
	int min=10000;
	for(int i=0;i<kq.size();i=i+n+2)
	{

		if(kq[i]<min)
		{
			min=kq[i];
		}		
	}		
	for(int i=0;i<kq.size();i=i+n+2)
	{
		if(kq[i]==min)
		{
			cout<<"Do dai duong di "<<min<<endl<<"Duong di: ";
			int ii=i+1;
			while(kq[ii]>=0)
			{
				cout<<kq[ii]<<" -> ";
				ii=ii+1;
			}
				cout<<endl;
		}
	}
	clock_t endDFS = clock(); 
    cout<<"Thoi gian DFS: "<<(float)(endDFS-beginDFS)/CLOCKS_PER_SEC<<" s"<<endl;

}
int main(){
	ifstream input("input.txt");
	input>>n>>socanh>>start>>finish;
		for (int i = 1; i <= socanh; i++)
		{
			int x,y,z;
			input>>x>>y>>z;
			a[y][x]=z;
			a[x][y]=z;
		
 		}
 		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
			{
				if(a[i][j]<1)
				{
					a[i][j]=10000;
				}
  	 		
  			}
 		}
    cout << "Hay chon menu sau:" << endl;
    cout << "Nhap 1: Tim duong di ngan nhat dung BFS" << endl;
    cout << "Nhap 2: Tim duong di ngan nhat dung DFS" << endl;
    cout << "Nhap 0: de thoat khoi ung dung" << endl;
 
    int control;
    cin >> control;
 
    switch (control){
        case 1:
            cout << "Tim duong di ngan nhat dung BFS" << endl;
           	XuLyBFS();
            break;
        case 2:
            cout << "Tim duong di ngan nhat bang DFS" << endl;
            XuLyDFS();
            break;
        default :
            cout << "Ban chon thoat khoi chuong trinh" << endl;
    }
 		
 		
   
}	
