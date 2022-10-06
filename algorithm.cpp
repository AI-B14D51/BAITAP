#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <time.h>
#include <cstring>
#include <memory>
#define max 1000

using namespace std;

fstream fin, fout;
vector<int> graph[max];
int matrix[max][max];
vector<int> mark;
bool visited[max];
int n, k = 1, destination = 13;
vector<int> result;
int length_road = INT32_MAX;
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
int sum_of_mark()
{
    int res = 0;
    for (int i = 0; i < (int)mark.size() - 1; i++)
    {
        res += matrix[mark[i]][mark[i + 1]];
    }
    return res;
}

void print_result_dfs()
{
    fout << "DFS" << endl;
    fout << "Path : " << endl
         << "1 => ";
    for (int i = 0; i < result.size(); i++)
        fout << result[i] << " => ";
    fout << destination << endl;
    fout << "Length : " << length_road + matrix[1][result[0]] + matrix[result[result.size() - 1]][destination] << endl;
}
void dfs(int vt)
{
    visited[vt] = true;

    for (int i = 0; i < graph[vt].size(); i++)
    {
        int v = graph[vt][i];
        if (!visited[v])
        {

            if (v == destination)
            {
                int distance = sum_of_mark();
                if (length_road > distance)
                {
                    length_road = distance;
                    result = mark;
                }
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
        matrix[x][y] = z;
        matrix[y][x] = z;
    }

    clock_t start, end;

    start = clock();
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
    bfs();
    end = clock();

    double time_taken_bfs = double(end - start) / double(CLOCKS_PER_SEC);
    fout << "Time taken by bfs is: " << fixed << time_taken_bfs << setprecision(6);
    fout << " sec" << endl;
    cout << "Time taken by bfs is: " << fixed << time_taken_bfs << setprecision(6);
    cout << " sec" << endl;
}