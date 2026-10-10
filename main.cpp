#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    if(!(cin >> n >> m)) return 0;
    vector<vector<int>> grid(m, vector<int>(n));
    pair<int,int> start{-1,-1}, home{-1,-1};
    for(int i=0;i<m;++i){
        for(int j=0;j<n;++j){
            cin >> grid[i][j];
            if(grid[i][j]==2) start={i,j};
            else if(grid[i][j]==3) home={i,j};
        }
    }
    // BFS with state: has umbrella (0/1)
    const int INF = -1;
    vector<vector<array<int,2>>> dist(m, vector<array<int,2>>(n, {INF, INF}));
    queue<tuple<int,int,int>> q; // x, y, hasUmbrella
    int sx=start.first, sy=start.second;
    int initUmbrella = (grid[sx][sy]==4) ? 1 : 0;
    dist[sx][sy][initUmbrella]=0;
    q.emplace(sx,sy,initUmbrella);
    int dirs[4][2]={{1,0},{-1,0},{0,1},{0,-1}};
    while(!q.empty()){
        auto [x,y,has]=q.front(); q.pop();
        for(auto &d:dirs){
            int nx=x+d[0], ny=y+d[1];
            if(nx<0||nx>=m||ny<0||ny>=n) continue;
            if(grid[nx][ny]==1) continue; // blocked
            int nhas=has;
            if(grid[nx][ny]==4) nhas=1;
            if(dist[nx][ny][nhas]==INF){
                dist[nx][ny][nhas]=dist[x][y][has]+1;
                q.emplace(nx,ny,nhas);
            }
        }
    }
    int hx=home.first, hy=home.second;
    int answer = dist[hx][hy][1]; // must have visited umbrella
    if(answer==INF) cout << -1 << "\n";
    else cout << answer << "\n";
    return 0;
}
