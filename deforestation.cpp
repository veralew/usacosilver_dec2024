#include <iostream> 
#include <algorithm> 
#include <vector> 
#include <queue> 
#include <map> 
#include <set> 
#include <array> 
#include <unordered_map> 
using namespace std; 
#define ll long long 

struct law { 
    // left, right, tree ct 
	int l, r, t; 
	law(int L, int R, int T) : l(L), r(R), t(T) {} 
}; 

// sort on increasing left index then incr. right index 
bool cmp(const law &a, const law &b) { 
    if (a.l != b.l) return a.l < b.l; 
    else return a.r < b.r; 
} 

int main() { 
    int T; cin >> T; 
    for (int t = 0; t < T; t++) { 
        int N, K; cin >> N >> K; 
        vector<int> x(N); 
        for (int i = 0; i < N; i++) cin >> x[i]; 
        sort(x.begin(), x.end()); 

        vector<law> laws; 
        for (int i = 0; i < K; i++) { 
            int l, r, t; cin >> l >> r >> t; 
            // find num trees in area 
            int ct = upper_bound(x.begin(), x.end(), r) - lower_bound(x.begin(), x.end(), l); 
            laws.push_back(law(l, r, ct-t)); 
        } 
        // make it out of bounds (-1e9, 1e9) 
        for (int i = 0; i < N; i++) 
            laws.push_back(law(x[i], 2e9, 0)); 
        sort(laws.begin(), laws.end(), cmp); 

        set<pair<int, int> > s; int ans = 0; 
        for (int i = 0; i < laws.size(); i++) { 
            int l = laws[i].l, r = laws[i].r, t = laws[i].t; 
            // remove all non overlapping (disjoint) 
            pair<int,int> s1 = *s.begin(); 
            //                  ends before start 
            while (!s.empty() && (s1.second) < l) { 
                s.erase(s.begin()); 
                s1 = *s.begin(); 
            } 
            // see if this is one of the ones out of bounds 
            if (r > 1e9) { 
                int mini = 2e9; s1 = *s.begin(); 
                if (!s.empty()) mini = min(mini, s1.first); 
                if (ans+1 <= mini) ans++; 
            } 
            else s.insert(make_pair(t+ans, r)); 
        } 
        cout << ans << endl; 
    } 
} 

/*
1 2 4 6 7 8 10

3
7 1
8 4 10 1 2 6 7
2 9 3
7 2
8 4 10 1 2 6 7
2 9 3
1 10 1
7 2
8 4 10 1 2 6 7 
2 9 3
1 10 4
*/