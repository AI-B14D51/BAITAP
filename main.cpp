#include<iostream>
#include<fstream>
#include<time.h>
#include<vector>
#include<memory>

using namespace std;

#define MAX 100
#define TRUE 1
#define FALSE  0
#define VOCUNG 10000000
fstream fin, fout;
int n;//số đỉnh của đồ thị.
int s;//đỉnh đầu.
int t;//đỉnh cuối
char chon;
vector<int> truoc(MAX, 0);//mảng đánh dấu đường đi.
vector<int> d(MAX, 0);//mảng đánh dấu khoảng cách.
//int Matrix[MAX][MAX];//ma trận trọng số
vector<vector<int> > Matrix(MAX, vector<int> (MAX, 0));
vector<int> chuaxet(MAX, 0);//mảng đánh dấu đỉnh đã được gán nhãn.

int dMin = 1e8; // đường đi ngắn nhất DFS
vector<bool> visited(MAX, false); // các đỉnh đã ghé thăm DFS
vector<int> mark, res; // Lưu vết đường đi


struct AllocationMetrics{
    uint32_t TotalAllocated = 0;
    uint32_t TotalFreed = 0;

    uint32_t CurrentUsage() { return TotalAllocated - TotalFreed; }
};

static AllocationMetrics s_AllocationMetrics;

void* operator new(size_t size) {
    s_AllocationMetrics.TotalAllocated += size;
    return malloc(size);
}

void operator delete(void* memory, size_t size) {
    s_AllocationMetrics.TotalFreed += size;
    free(memory);
}

static void PrintMemoryUsage(){
    fout << "\nMemory Usage: " << s_AllocationMetrics.CurrentUsage() << " bytes\n";
}


void InitBFS(void){
 fin.open("input.in", ios::in);
 fin >> n >> s >> t;
 for (int i = 0; i < n; i++)
    for(int j = 0; j < n; j++)
        Matrix[i][j] = VOCUNG;
 while(!fin.eof()) {
    int u, v, w;
    fin >> u >> v >> w;
    Matrix[u][v] = w;
    Matrix[v][u] = w;
 }
 fin.close();
}

void ResultBFS(void){
 fout.open("output.out", ios::out | ios::trunc);
 fout << "BFS\n";
 fout<<"Duong di ngan nhat tu "<<s<<" den "<<t<< " la"<<endl;
 fout<<t<<"<=";//in đỉnh cuối dưới dạng char.
 int i = truoc[t];
 while (i != s){
  fout<<i<<"<=";//in ra kết quả dưới dạng char.
  i = truoc[i];
 }
 fout<<s;//in đỉnh đầu dưới dạng char.
 fout<<endl<<"Do dai duong di la : "<< d[t];
}

void BFS(void){
 int u, minp;
 //khởi tạo nhãn tạm thời cho các đỉnh.
 for (int v = 0; v < n; v++){
  d[v] = Matrix[s][v];
  truoc[v] = s;
  chuaxet[v] = FALSE;
 }
 truoc[s] = 0;
 d[s] = 0;
 chuaxet[s] = TRUE;
 //bươc lặp
 while (!chuaxet[t]) {
  minp = VOCUNG;
  //tìm đỉnh u sao cho d[u] là nhỏ nhất
  for (int v = 0; v < n; v++){
   if ((!chuaxet[v]) && (minp > d[v])){
    u = v;
    minp = d[v];
   }
  }
  chuaxet[u] = TRUE;// u la dinh co nhan tam thoi nho nhat
  if (!chuaxet[t]){
   //gán nhãn lại cho các đỉnh.
   for (int v = 0; v < n; v++){
    if ((!chuaxet[v]) && (d[u] + Matrix[u][v] < d[v])){
     d[v] = d[u] + Matrix[u][v];
     truoc[v] = u;
    }
   }
  }
 }
}

void InitDFS() {
 fin.open("input.in", ios::in);
 fin >> n >> s >> t;
 for (int i = 0; i < n; i++)
    for(int j = 0; j < n; j++)
        Matrix[i][j] = 0;
 while(!fin.eof()) {
  int u, v, w;
  fin >> u >> v >> w;
  Matrix[u][v] = w;
  Matrix[v][u] = w;
 }
 fin.close();
}

int sumOfMark() { // Tổng chiều dài đường đi
 int res = 0;
 for (int i = 0; i < (int)mark.size() - 1; i++) {
  res += Matrix[mark[i]][mark[i + 1]];
 }
 return res;
}

void DFS(int u) {
 for (int i = 0; i < n; i++) {
  if(!visited[i] && Matrix[u][i]) {
   mark.push_back(i);
   visited[i] = true;
   if(i == t) {
    if(sumOfMark() < dMin) {
     dMin = sumOfMark();
     res = mark;
    }
    mark.pop_back();
    visited[i] = false;
   } else {
    DFS(i);
    mark.pop_back();
    visited[i] = false;
   }
  }
 }
}

void ResultDFS() {
 fout << "\n\nDFS\n";
 fout<<"Duong di ngan nhat tu "<<s<<" den "<<t<< " la"<<endl;
 for(int i = 0; i < res.size() - 1; i++)
  fout << res[i] << "=>";
 fout << res[res.size() - 1];
 fout<<endl<<"Do dai duong di la : "<< dMin;
}

int main(){
 // BFS
 clock_t start = clock();
 InitBFS();
 BFS();
 ResultBFS();
 clock_t end = clock();
 double time_taken = ((double)(end - start))/CLOCKS_PER_SEC;
 fout << "\n" << "Duration time BFS: " << time_taken * 1000 << " miliseconds";
 PrintMemoryUsage();

 // DFS
 start = clock();
 InitDFS();
 mark.push_back(s);
 visited[s] = true;
 DFS(s);
 ResultDFS();
 end = clock();
 time_taken = ((double)(end - start))/CLOCKS_PER_SEC;
 fout << "\n" << "Duration time DFS: " << time_taken * 1000 << " miliseconds";
 PrintMemoryUsage();
 fout.close();
 return 0;
}
