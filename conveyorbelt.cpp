#include <iostream>
#include <vector>
#include <deque>
#include <tuple>
using namespace std;

struct Point {
    int x, y;
    Point(int X, int Y) : x(X), y(Y) {}
};
struct Change {
    int x, y; char type;
    Change(int X, int Y, char t) : x(X), y(Y), type(t) {}
};

int dx[4] = {-1, 1, 0, 0};
int dy[4] = {0, 0, -1, 1};
char dir[4] = {'D', 'U', 'R', 'L'};
int size;
vector<vector<char> > grid;
vector<vector<int> > vis;
deque<Point> dq;
int rem;

bool valid(int x, int y) { 
    return x >= 0 && x < size && y >= 0 && y < size;
} 

bool can_exit(int x, int y) {
    return (x == 0 && grid[x][y] == 'U') ||
            (y == 0 && grid[x][y] == 'L') ||
            (x == size-1 && grid[x][y] == 'D') ||
            (y == size-1 && grid[x][y] == 'R');
} 
    
void checkBoundary(int x, int y) {
    if (grid[x][y] == 0) {
        dq.emplace_back(x, y);
        vis[x][y] = 1; rem--; return;
    }
    if (can_exit(x, y)) {
        dq.emplace_back(x, y);
        vis[x][y] = 1; rem--;
    }
}
    
void bfs() {
    while (!dq.empty()) {
        Point current = dq.front();
        dq.pop_front();
        
        for (int d = 0; d < 4; ++d) {
            int nx = current.x + dx[d], ny = current.y + dy[d];
            if (valid(nx, ny) && !vis[nx][ny] && 
                (grid[nx][ny] == dir[d] || grid[nx][ny] == 0)) {
                vis[nx][ny] = 1; rem--; 
                dq.emplace_front(nx, ny); 
            }
        }
    }
}

void checkAdj(int x, int y) {
    for (int d = 0; d < 4; ++d) {
        int nx = x + dx[d], ny = y + dy[d];
        if (valid(nx, ny) && vis[nx][ny]) {
            dq.emplace_back(x, y);
            vis[x][y] = 1; rem--; break;
        }
    }
} 

void processBelt(const Change& change) {
    if (!vis[change.x][change.y]) {
        if ((change.x == 0 && grid[change.x][change.y] != 'U') ||
            (change.y == 0 && grid[change.x][change.y] != 'L') ||
            (change.x == size-1 && grid[change.x][change.y] != 'D') ||
            (change.y == size-1 && grid[change.x][change.y] != 'R')) {
            dq.emplace_back(change.x, change.y);
            vis[change.x][change.y] = 1; rem--;
        } else checkAdj(change.x, change.y);
    }
    grid[change.x][change.y] = 0;
}
    
vector<int> process(const vector<Change>& changes) {
    vector<int> res(changes.size());
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            if (i == 0 || j == 0 || i == size-1 || j == size-1) {
                checkBoundary(i, j);
            }
        }
    }
        
    bfs();
    res[changes.size()-1] = rem;
    for (int i = changes.size()-2; i >= 0; --i) {
        processBelt(changes[i+1]);
        bfs(); res[i] = rem;
    } 
    return res; 
} 

int main() {
    int N, Q;
    cin >> N >> Q;
    
    size = N; 
    grid = vector<vector<char>>(N, vector<char>(N)); 
    vis = vector<vector<int>>(N, vector<int>(N)), 
    rem = N*N; 
    vector<Change> changes;
    
    for (int i = 0; i < Q; i++) { 
        int x, y; char t; 
        cin >> x >> y >> t; 
        grid[x-1][y-1] = t; 
        changes.emplace_back(x-1, y-1, t); 
    } 

    for (int count : process(changes)) 
        cout << count << endl; 
    
    return 0; 
} 