#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <time.h>
#include <cstring>
#define max 1000

using namespace std;

fstream fin, fout;
vector<int> graph[max];
bool visited[max];
int n, k = 1, destination = 13;
queue<int> g;

void bfs()
{
    g.push(k);
    visited[k] = true;
    while (!g.empty())
    {
        int u = g.front();
        g.pop();
        for (int i = 0; i < graph[u].size(); i++)
        {
            int v = graph[u][i];
            if (!visited[v])
            {
                visited[v] = true;
                if (visited[destination])
                    return;
                g.push(v);
            }
        }
    }
}

void dfs(int vt)
{
    visited[vt] = true;
    if (visited[destination])
        return;
    for (int i = 0; i < graph[vt].size(); i++)
    {
        int v = graph[vt][i];
        if (!visited[v])
        {
            dfs(v);
        }
    }
}

int main()
{
    fin.open("input.in", ios::in);
    fout.open("output.out", ios::out | ios::trunc);
    fin >> n;
    for (int i = 1; i <= n; i++)
    {
        int x, y, z;
        fin >> x >> y >> z;
        graph[x].push_back(y);
        graph[y].push_back(x);
    }

    clock_t start, end;

    start = clock();
    dfs(1);
    end = clock();

    double time_taken_dfs = double(end - start) / double(CLOCKS_PER_SEC);

    cout << "Time taken by dfs is: " << fixed << time_taken_dfs << setprecision(6);
    cout << " sec" << endl;

    fout << "Time taken by dfs is: " << fixed << time_taken_dfs << setprecision(6);
    fout << " sec" << endl;
    memset(visited, false, sizeof(visited));

    start = clock();
    bfs();
    end = clock();

    double time_taken_bfs = double(end - start) / double(CLOCKS_PER_SEC);
    fout << "Time taken by bfs is: " << fixed << time_taken_bfs << setprecision(6);
    fout << " sec" << endl;
    cout << "Time taken by bfs is: " << fixed << time_taken_bfs << setprecision(6);
    cout << " sec" << endl;
}