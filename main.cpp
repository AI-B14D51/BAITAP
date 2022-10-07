#include <iostream>
#include <fstream>
#include <time.h>
#include <vector>
#include <memory>

using namespace std;

#define MAX 100
#define TRUE 1
#define FALSE 0
#define MAXN 10000000
fstream fin, fout;
int n; // số đỉnh của đồ thị.
int s; //đỉnh đầu.
int t; //đỉnh cuối
char chon;
vector<int> d(MAX, 0);     // mảng đánh dấu khoảng cách.
vector<int> truoc(MAX, 0); // mảng đánh dấu đường đi.
// int Matrix[MAX][MAX];//ma trận trọng số
vector<vector<int>> Matrix(MAX, vector<int>(MAX, 0));
vector<int> chuaxet(MAX, 0); // mảng đánh dấu đỉnh đã được gán nhãn.


struct AllocationMetrics
{
    uint32_t TotalAllocated = 0;
    uint32_t TotalFreed = 0;
    uint32_t CurrentUsage() { return TotalAllocated - TotalFreed; }
};

static AllocationMetrics s_AllocationMetrics;
void *operator new(size_t size)
{
    s_AllocationMetrics.TotalAllocated += size;
    return malloc(size);
}

void operator delete(void *memory, size_t size)
{
    s_AllocationMetrics.TotalFreed += size;
    free(memory);
}

static void PrintMemoryUsage()
{
    fout << "\nMemory Usage: " << s_AllocationMetrics.CurrentUsage() << " bytes\n";
}

void Init()
{
    fin.open("map.txt", ios::in);
    fin >> n >> s >> t;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            Matrix[i][j] = MAXN;
    while (!fin.eof())
    {
        int u, v, w;
        fin >> u >> v >> w;
        Matrix[u][v] = w;
        Matrix[v][u] = w;
    }
    fin.close();
}

void ResultBFS()
{
    fout.open("ketqua.txt", ios::out | ios::trunc);
    fout << "BFS result:\n";
    fout << t << "<--"; 
    int i = truoc[t];
    while (i != s)
    {
        fout << i << "<--"; // in ra kết quả dưới dạng char.
        i = truoc[i];
    }
    fout << s; 
    fout << endl
         << "Dmin : " << d[t];
}

void BFS()
{
    int u, minp;
    // khởi tạo nhãn tạm thời cho các đỉnh.
    for (int v = 0; v < n; v++)
    {
        d[v] = Matrix[s][v];
        truoc[v] = s;
        chuaxet[v] = FALSE;
    }
    truoc[s] = 0;
    d[s] = 0;
    chuaxet[s] = TRUE;
    while (!chuaxet[t])
    {
        minp = MAXN;
        // tìm đỉnh u sao cho d[u] là nhỏ nhất
        for (int v = 0; v < n; v++)
        {
            if ((!chuaxet[v]) && (minp > d[v]))
            {
                u = v;
                minp = d[v];
            }
        }
        chuaxet[u] = TRUE; // u la dinh co nhan tam thoi nho nhat
        if (!chuaxet[t])
        {
            // gán nhãn lại cho các đỉnh.
            for (int v = 0; v < n; v++)
            {
                if ((!chuaxet[v]) && (d[u] + Matrix[u][v] < d[v]))
                {
                    d[v] = d[u] + Matrix[u][v];
                    truoc[v] = u;
                }
            }
        }
    }
}

int main()
{
    clock_t start = clock();
    Init();
    BFS();
    ResultBFS();
    clock_t end = clock();
    double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
    fout << "\n"
         << "Execution time: " << time_taken * 1000 << " miliseconds";
    PrintMemoryUsage();
    fout.close();
    return 0;
}