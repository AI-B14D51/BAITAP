#include<iostream>
#include<vector>
#include<queue>
#include<stack>
#include<time.h>
#include <fstream>
using namespace std;

	std::ifstream fileInput("C:\\Users\\DELL\\OneDrive\\Desktop\\dfs\\in1.txt");
	std::ofstream fileOutput("C:\\Users\\DELL\\OneDrive\\Desktop\\dfs\\out1.txt");
	
//add the edge in graph
void edge(vector<int>adj[],int u,int v)
{
	adj[u].push_back(v);
}
//function for bfs traversal
void bfs(int s,vector<int>adj[],bool visit[])
{
	queue<int>q;//queue in STL
	q.push(s);
	visit[s]=true;
	while(!q.empty())
	{
		int u=q.front();
		fileOutput<<u<<" ";
    	cout<<u<<" ";
    	q.pop();
//loop for traverse
    for(int i=0;i<adj[u].size();i++)
	{
    	if(!visit[adj[u][i]])
		{
        	q.push(adj[u][i]);
        	visit[adj[u][i]]=true;
    	}
    }
  }
}
//function for dfs traversal
void dfs(int s,vector<int>adj[],bool visit[])
{
	stack<int>stk;//stack in STL
	stk.push(s);
	visit[s]=true;
	while(!stk.empty())
	{
		int u=stk.top();
		fileOutput<<u<<" ";
		cout<<u<<" ";
		stk.pop();
//loop for traverse
    for(int i=0;i<adj[u].size();i++)
	{
    	if(!visit[adj[u][i]])
		{
        	stk.push(adj[u][i]);
        	visit[adj[u][i]]=true;
    	}
    }
  }
}
//main function
int main()
{
	int n;
	//cout<<"nhap so dinh n"<<endl;
	//cin>>n;
	fileInput>>n;
	int k;
	fileInput >> k;
	int x[k], y[k];
	
	vector<int>adj[n];//vector of array to store the graph
	bool visit[n];//array to check visit or not of a node
	//initially all node are unvisited
  
  	for (int i=0; i<k; i++ )
	{
		fileInput>>x[i]>>y[i];
		edge(adj,x[i],y[i]);
	}
  
	for(int i=0;i<n;i++)
	{
		visit[i]=false;
	}
	clock_t start, end;
	double time_use;
	//input for edges
  
//	edge(adj,0,2);edge(adj,16,17);
//	edge(adj,0,1);edge(adj,14,15);
//	edge(adj,0,3);edge(adj,15,18);
//	edge(adj,1,4);edge(adj,18,19);
//	edge(adj,2,4);
//	edge(adj,3,5);
//	edge(adj,5,7);
//	edge(adj,2,6);
//	edge(adj,2,8);
//	edge(adj,7,10);
//	edge(adj,10,11);
//	edge(adj,8,11);
//	edge(adj,11,12);
//	edge(adj,8,12);
//	edge(adj,6,9);
//	edge(adj,12,9);
//	edge(adj,9,13);
//	edge(adj,9,14);
//	edge(adj,14,16);
	cout<<"BFS traversal is"<<"  ";
	//call bfs funtion
	start = clock();
	bfs(0,adj,visit);//1 is a starting point
	end = clock();
	fileOutput<<endl;
	cout<<endl;
  
	time_use = (double)(end - start) / CLOCKS_PER_SEC;    //Tính th?i gian s? d?ng
	fileOutput<<"Thoi gian chay bfs "<<time_use<<endl;
    cout<<"Thoi gian chay bfs: "<<time_use<<endl;
	//again initialise all node unvisited for dfs
	for(int i=0;i<20;i++)
	{
    	visit[i]=false;
	}
	
	cout<<"DFS traversal is"<<"  ";
	
	//call dfs function
	start = clock();
	dfs(0,adj,visit);//1 is a starting point
	end = clock();
	fileOutput<<endl;
	cout<<endl;
	time_use = (double)(end - start) / CLOCKS_PER_SEC;    //Tính th?i gian s? d?ng
	fileOutput<<"Thoi gian chay dfs "<<time_use<<endl;
    cout<<"Thoi gian chay dfs: "<<time_use<<endl;
}
