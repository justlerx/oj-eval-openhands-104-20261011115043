#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <utility>

using namespace std;

const int dx[] = {-1, 1, 0, 0};
const int dy[] = {0, 0, -1, 1};

vector<vector<int>> bfs(int start_x, int start_y, const vector<vector<int>>& grid, int n, int m) {
    vector<vector<int>> dist(m, vector<int>(n, INT_MAX));
    queue<pair<int, int>> q;
    
    dist[start_x][start_y] = 0;
    q.push({start_x, start_y});
    
    while (!q.empty()) {
        auto [x, y] = q.front();
        q.pop();
        
        for (int dir = 0; dir < 4; dir++) {
            int nx = x + dx[dir];
            int ny = y + dy[dir];
            
            if (nx >= 0 && nx < m && ny >= 0 && ny < n && 
                grid[nx][ny] != 1 && dist[nx][ny] == INT_MAX) {
                dist[nx][ny] = dist[x][y] + 1;
                q.push({nx, ny});
            }
        }
    }
    
    return dist;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, m;
    cin >> n >> m;
    
    vector<vector<int>> grid(m, vector<int>(n));
    vector<pair<int, int>> umbrellas;
    pair<int, int> start, home;
    
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            cin >> grid[i][j];
            if (grid[i][j] == 2) {
                start = {i, j};
            } else if (grid[i][j] == 3) {
                home = {i, j};
            } else if (grid[i][j] == 4) {
                umbrellas.push_back({i, j});
            }
        }
    }
    
    // BFS from start
    auto dist_from_start = bfs(start.first, start.second, grid, n, m);
    
    // BFS from home
    auto dist_from_home = bfs(home.first, home.second, grid, n, m);
    
    int min_distance = INT_MAX;
    
    // Check all umbrella shops
    for (auto [ux, uy] : umbrellas) {
        if (dist_from_start[ux][uy] != INT_MAX && dist_from_home[ux][uy] != INT_MAX) {
            int total_dist = dist_from_start[ux][uy] + dist_from_home[ux][uy];
            min_distance = min(min_distance, total_dist);
        }
    }
    
    if (min_distance == INT_MAX) {
        cout << -1 << endl;
    } else {
        cout << min_distance << endl;
    }
    
    return 0;
}