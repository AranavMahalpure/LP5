#include <iostream>
#include <vector>
#include <stack>
#include <omp.h>
using namespace std;

const int MAX = 100000;
vector<int> graph[MAX];
bool visited[MAX];

void dfs(int node) {
    stack<int> s;
    s.push(node);
    while (!s.empty()) {
        int curr = s.top(); s.pop();
        if (!visited[curr]) {
            visited[curr] = true;
            cout << curr << " ";
            for (int i = graph[curr].size() - 1; i >= 0; i--) {
                if (!visited[graph[curr][i]])
                    s.push(graph[curr][i]);
            }
        }
    }
}

int main() {
    int n, m, start;
    cin >> n >> m >> start;
    for (int i = 0; i < m; i++) {
        int u, v; cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    #pragma omp parallel for
    for (int i = 0; i < n; i++) visited[i] = false;

    dfs(start);
    return 0;
}