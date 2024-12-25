#include <iostream> 
#include <algorithm> 
#include <vector> 
#include <queue> 
#include <map> 
#include <unordered_map> 
using namespace std; 
#define ll long long 

void solve(const vector<ll>& nums) { 
    ll k = (nums.size()-1)/2; 
    ll n = nums.size(); 
    ll totalSum = 0; 
    for (int i = 0; i < n; i++) totalSum += nums[i]; 
    vector<ll> pref(k+1), suff(k+1); 
    for (ll i = 1; i <= k && i <= nums.size(); i++) 
        pref[i] = pref[i-1] + nums[i-1]; 
    
    for (ll i = 1; i <= k && i <= nums.size(); i++) 
        suff[i] = suff[i-1] + nums[nums.size()-i]; 

    ll max_sum = 0; 
    for (int i = 0; i <= k; i++) { 
        if (i > n || (k-i) > n) continue; 
        max_sum = max(max_sum, pref[i] + suff[k-i]); 
        
    } 
    //cout << totalSum-max_sum << " " << max_sum << endl; 
} 

int main() { 
    ll T; cin >> T; 
    for (ll t = 0; t < T; t++) { 
        ll N; cin >> N; 
        vector<ll> a(N); 
        for (int i = 0; i < N; i++) cin >> a[i]; 
        solve(a); 
    } 
} 