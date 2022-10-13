#include <stdio.h>
#include <vector>
#include <queue>
#include <iostream>
#include <fstream>
#include<time.h>

	std::ifstream fileInput("C:\\Users\\DELL\\OneDrive\\Desktop\\dfs\\in.txt");
	std::ofstream fileOutput("C:\\Users\\DELL\\OneDrive\\Desktop\\dfs\\out.txt");
	
using namespace std;

const int oo = 100000000;
typedef pair<int, int> ii;

vector<ii> a[2309];
int n, m;

int d[2309];

void dijkstra()
 {
    priority_queue<ii, vector<ii>, greater<ii> > pq;
    for (int i = 1; i <= n; i++)
        d[i] = oo;
    d[1] = 0;
    pq.push(ii(0, 1));

    while (pq.size()) 
	{
        int u = pq.top().second;
        int du = pq.top().first;
        pq.pop();
        if (du != d[u])
            continue;

        for (int i = 0; i < a[u].size(); i++) 
		{
            int v = a[u][i].second;
            int uv = a[u][i].first;
            if (d[v] > du + uv) 
			{
                d[v] = du + uv;
                pq.push(ii(d[v], v));
            }
        }
    }
}

int main() {
	
    int p, q, m, w;
    clock_t start, end;
	double time_use;
	start = clock();
    fileInput>>n>>m;
    //scanf("%d%d", &n, &m);
    while (m--) 
	{
        //scanf("%d%d%d", &p, &q, &w);
        fileInput>>p>>q>>w;
        a[p].push_back(ii(w, q));
        a[q].push_back(ii(w, p));
    }
    //start = clock();
    dijkstra();
    end = clock();
    
    time_use = (double)(end - start) / CLOCKS_PER_SEC;    //Tính th?i gian s? d?ng
	fileOutput<<"Thoi gian chay "<<time_use<<endl;
	cout<<" "<<time_use<<endl;
	
    for (int i = 2; i <= n; i++)
    {
    	//fileOutput<<i<<"d( 1 -> %d ) = %d\n"<<d[i];
    	fileOutput<<"d(1 -> "<<i<<") = "<<d[i]<<endl;
    	printf("d( 1 -> %d ) = %d\n", i, d[i]);
	}
        //printf("d( 1 -> %d ) = %d\n", i, d[i]);
}
