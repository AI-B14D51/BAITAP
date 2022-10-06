#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <time.h>
#include <cstring>
#include <memory>
#include <utility>
#define max 1000
#define maxr 9999999
#define fi first
#define se second

using namespace std;
typedef pair<int, int> ii;

fstream fin, fout;
vector<int> graph[max];
int matrix[max][max];
vector<int> mark;
bool visited[max];
int n, k = 1, destination = 13;
vector<int> result;
int length_road = INT32_MAX;
queue<int> g;
int d[max];
int check[max];
vector<ii> graphbfs[max];

void bfs(int root)
{
    priority_queue<ii, vector<ii>, greater<ii> > road;
    for (int i = 0; i <= n; i++)
    {
        d[i] = maxr;
    }
    d[root] = 0;
    road.push(ii(root, 0));
    while (!road.empty())
    {
        ii top = road.top();
        road.pop();
        int u = top.fi;
        if (d[u] != top.se)
            continue;

        for (int i = 0; i < graph[u].size(); i++)
        {
            int v = graphbfs[u][i].fi;
            int uv = graphbfs[u][i].se;
            if (d[v] > d[u] + uv)
            {
                d[v] = d[u] + uv;
                road.push(ii(v, d[v]));
                check[v] = u;
            }
        }
    }
}
int sum_of_mark()
{
    int res = 0;
    for (int i = 0; i < (int)mark.size() - 1; i++)
    {
        res += matrix[mark[i]][mark[i + 1]];
    }
    return res + matrix[mark[mark.size() - 1]][destination];
}
void print_bfs(){
 
 fout << "BFS\n";
 fout << "Path : " << endl;
 fout << destination << " <= ";
 int i = check[destination];
 while (i != 1){
  fout<<i<<" <= ";
  i = check[i];
 }
 fout << "1";
 fout << endl<<"Length : "<< d[13] << endl;
}
void print_result_dfs()
{
    fout << "DFS" << endl;
    fout << "Path : " << endl;
    for (int i = 0; i < result.size(); i++)
        fout << result[i] << " => ";
    fout << destination << endl;
    fout << "Length : " << length_road << endl;
}
void dfs(int vt)
{
    for (int i = 0; i < graph[vt].size(); i++)
    {
        int v = graph[vt][i];
        if (!visited[v])
        {
            visited[v] = true;
            if (v == destination)
            {
                int distance = sum_of_mark();
                if (length_road > distance)
                {
                    length_road = distance;
                    result = mark;
                }
                visited[v] = false;
            }
            else
            {
                mark.push_back(v);
                dfs(v);
                visited[v] = false;
                mark.pop_back();
            }
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
        graphbfs[x].push_back(make_pair(y, z));
        graphbfs[y].push_back(make_pair(x, z));

        matrix[x][y] = z;
        matrix[y][x] = z;
    }

    clock_t start, end;

    start = clock();
    mark.push_back(1);
    visited[1] = true;
    dfs(1);
    print_result_dfs();
    end = clock();

    double time_taken_dfs = double(end - start) / double(CLOCKS_PER_SEC);

    cout << "Time taken by dfs is: " << fixed << time_taken_dfs << setprecision(6);
    cout << " sec" << endl;

    fout << "Time taken by dfs is: " << fixed << time_taken_dfs << setprecision(6);
    fout << " sec" << endl;
    memset(visited, false, sizeof(visited));

    start = clock();
    bfs(1);
    print_bfs();
    end = clock();

    double time_taken_bfs = double(end - start) / double(CLOCKS_PER_SEC);
    fout << "Time taken by bfs is: " << fixed << time_taken_bfs << setprecision(6);
    fout << " sec" << endl;
    cout << "Time taken by bfs is: " << fixed << time_taken_bfs << setprecision(6);
    cout << " sec" << endl;
}