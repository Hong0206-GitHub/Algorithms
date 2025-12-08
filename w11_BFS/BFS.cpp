#include <bits/stdc++.h>

using namespace std;

// BFS 함수 선언
void BFS(int node);

// BFS에서 필요한 자료형들 선언
vector<vector<int>> graph;
vector<string> color;
vector<int> dist;
vector<int> prenode;

int main(void) {

    // 입출력 고속화
    ios::sync_with_stdio(false), cin.tie(NULL);

    // 강의 자료에 나온 초기값들로 초기화 및 선언
    int N = 7;

    graph.resize(N + 1);
    color.resize(N + 1);
    dist.resize(N + 1);
    prenode.resize(N + 1, -1);

    for (int i = 1; i <= N; i++) color[i] = "white";
    for (int i = 1; i <= N; i++) dist[i] = INT_MAX;

    graph[1].push_back(2);
    graph[1].push_back(5);
    
    graph[2].push_back(1);
    graph[2].push_back(7);
    graph[2].push_back(6);
    graph[2].push_back(3);

    graph[3].push_back(2);
    graph[3].push_back(4);

    graph[4].push_back(5);
    graph[4].push_back(3);

    graph[5].push_back(1);
    graph[5].push_back(7);
    graph[5].push_back(6);
    graph[5].push_back(4);

    graph[6].push_back(2);
    graph[6].push_back(5);

    graph[7].push_back(2);
    graph[7].push_back(5);
    
    // 시작노드 7
    BFS(7);

    // 거리 출력
    for (int i = 1; i <= N; i++) cout << dist[i] << ' ';
    cout << '\n';

    return 0;
}

// BFS 함수
void BFS(int node) {
    // 큐 선언
    queue<int> q;

    // 시작 노드 큐에 삽입 및 갱신
    q.push(node);
    color[node] = "gray";
    dist[node] = 0;
    
    // 큐가 빌 때까지
    while (!q.empty()) {
        // 큐에서 하나 꺼내와서
        int current = q.front();
        q.pop();

        // 꺼내온 노드와 연결된 노드들에 대해
        for (auto &next : graph[current]) {
            // 아직 방문하지 않았다면,
            // 큐에 삽입 후 갱신
            if (color[next] == "white") {
                q.push(next);
                color[next] = "gray";
                dist[next] = dist[current] + 1;
                prenode[next] = current;
            }
        }
        // 완전히 처리가 끝났음을 표시
        color[current] = "black";
    }
}